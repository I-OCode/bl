#include "bl.hpp"
#include "detail.hpp"
#include <format>
#include <limits>
#include <ranges>

class value_stream: public stream {
public:
	std::string parse_str();
	double parse_num();
	std::array<double, 3> parse_units();
};

static std::uint8_t bitrev8(std::uint8_t v) {
	// LUT for reversing the bits of a 4-bit nibble.
	std::array rev4{
		0x0, 0x8, 0x4, 0xC, 0x2, 0xA, 0x6, 0xE, 0x1, 0x9, 0x5, 0xD, 0x3,
		0xB, 0x7, 0xF
	};

	return rev4[v & 0xF] << 4 | rev4[v >> 4];
}

static std::uint16_t bitrev16(std::uint16_t v) {
	return bitrev8(v & 0xFF) << 8 | bitrev8(v >> 8);
}

static std::string str_to_value(std::string const& s) {
	if (s.empty()) {
		// The game uses a backtick in place of the length to represent
		// the empty string.
		return "`";
	}

	// If the length is too long to fit in the BL82 charset then the game
	// uses an alternative format where `|` and `~` are the beginning and
	// ending delimiters, respectively.
	if (s.length() > 82) {
		return '|' + bl::encode_world_id(s.length()) + '~';
	}

	return bl::encode_bl82(s.length() - 1) + s;
}

static std::string num_to_value(double v) {
	return str_to_value(std::format("{}", v));
}

static std::string units_to_value(std::span<double const, 3> v) {
	std::string s{};
	for (auto axis: v) {
		if (axis < 0) { s += '-'; }

		s += bl::encode_units(std::abs(axis));
		s += ',';
	}

	// Remove the trailing `,`, if there was any.
	if (s.back() == ',') { s.pop_back(); }

	return str_to_value(s);
}

std::string value_stream::parse_str() {
	if (this->peek_single() == '`') { return ""; }

	if (this->peek_single() == '|') {
		// Consume the `|`.
		this->read_single();

		stream beg{*this};
		this->read_until("~");

		std::size_t len{bl::decode_world_id({beg.i, this->i})};

		// Consume the `~`.
		this->read_single();

		return std::string(this->read(len).value());
	}

	std::size_t len{bl::decode_bl82(this->read_single().value())};

	// Using increment operator instead of just `+ 1` in the initialization
	// of `len` to avoid that stupid narrowing error.
	++len;

	return std::string(this->read(len).value());
}

double value_stream::parse_num() {
	auto str{this->parse_str()};
	std::string_view view{str};

	double n{};
	auto ec{std::from_chars(view.cbegin(), view.cend(), n).ec};
	if (ec != std::errc()) {
		throw std::invalid_argument(std::make_error_code(ec).message());
	}

	return n;
}

std::array<double, 3> value_stream::parse_units() {
	std::array<double, 3> units{};
	std::size_t axis_idx{};

	while (!this->eof()) {
		auto axis_beg{*this};
		this->read_until(",");

		std::string_view axis{axis_beg.i, this->i};

		// Consume the `,`, if there was any.
		this->read_single();

		if (axis.front() == '-') {
			units[axis_idx++] = bl::decode_units(
				axis | std::views::take(axis.length() - 1)
			);
			units.back() = -units.back();
		} else {
			units[axis_idx++] = bl::decode_units(axis);
		}
	}

	return units;
}

bl::delay_cfg::delay_cfg(std::string_view v) {
	this->interval = decode_delay_interval(v.front());
}

std::string bl::delay_cfg::to_value() const {
	return {get_delay_interval_traits(this->interval).encoded};
}

bl::timer_cfg::timer_cfg(std::string_view v) {
	this->interval = decode_timer_interval(v.front());
}

std::string bl::timer_cfg::to_value() const {
	return {get_timer_interval_traits(this->interval).encoded};
}

std::string bl::text_cfg::to_value() const {
	std::string s{};
	for (char c: this->text) {
		// We cannot have `;` as-is in the value because then it could
		// be confused for a block terminator. The game originally
		// replaced all `;`s with `:`s (colons) in signs, but now the
		// game replaces them with `;`s instead. Confused? Exactly. The
		// game replaces semicolons with Greek question marks. Very
		// cheeky, Tomtom.

		// Normal semicolon here...
		if (c == ';') {
			// ...and Greek question mark here.
			s += ";";
		} else {
			s += c;
		}
	}

	return s;
}

bl::legacy_kill_module_cfg::legacy_kill_module_cfg(std::string_view v) {
	value_stream s{v};
	this->show_range = s.parse_num();
	this->damage = s.parse_num();
	this->range = s.parse_num();
}

std::string bl::legacy_kill_module_cfg::to_value() const {
	return num_to_value(this->show_range)
		+ num_to_value(this->damage)
		+ num_to_value(this->range);
}

bl::dip_switches_cfg::dip_switches_cfg(std::string_view v) {
	this->val = bl::decode_bl71(v.front());
}

std::string bl::dip_switches_cfg::to_value() const {
	return {bl::encode_bl71(this->val)};
}

bl::eeprom_cfg::eeprom_cfg(std::string_view v) {
	stream s{v};
	while (!s.eof()) {
		std::uint8_t decoded_addr{
			bitrev8(decode_world_id(s.read(2).value()))
		};

		std::uint8_t decoded_val{
			bitrev8(decode_world_id(s.read(2).value()))
		};

		this->mem[decoded_addr] = decoded_val;
	}
}

std::string bl::eeprom_cfg::to_value() const {
	std::string out{};

	for (auto [addr, val]: this->mem) {
		std::string encoded_addr{encode_world_id(bitrev8(addr))};
		std::string encoded_val{encode_world_id(bitrev8(val))};

		out.append(2 - encoded_addr.length(), '0');
		out += encoded_addr;
		out.append(2 - encoded_val.length(), '0');
		out += encoded_val;
	}

	return out;
}

bl::block_placer_cfg::block_placer_cfg(std::string_view v) {
	if (v == "Error") {
		this->type = block_type::eErreur;
	} else {
		std::string_view str_id{v | std::views::take(v.length() - 1)};

		std::size_t id{};
		std::from_chars(str_id.cbegin(), str_id.cend(), id);
	}

	this->rot = v.back();
}

std::string bl::block_placer_cfg::to_value() const {
	std::string out{};

	out += this->type == block_type::eErreur
		? "Error"
		: std::format("{}", bl::get_block_type_traits(this->type).id);

	out += this->rot.encode();

	return out;
}

bl::tnt_activator_cfg::tnt_activator_cfg(std::string_view v) {
	value_stream s{v};
	this->show_range = s.parse_num();
	this->range = s.parse_num();
}

std::string bl::tnt_activator_cfg::to_value() const {
	return num_to_value(this->show_range) + num_to_value(this->range);
}

bl::eeprom16_cfg::eeprom16_cfg(std::string_view v) {
	stream s{v};
	while (!s.eof()) {
		std::uint16_t decoded_addr{
			bitrev16(decode_world_id(s.read(3).value()))
		};

		std::uint16_t decoded_val{
			bitrev16(decode_world_id(s.read(3).value()))
		};

		this->mem[decoded_addr] = decoded_val;
	}
}

std::string bl::eeprom16_cfg::to_value() const {
	std::string out{};

	for (auto [addr, val]: this->mem) {
		std::string encoded_addr{encode_world_id(bitrev16(addr))};
		std::string encoded_val{encode_world_id(bitrev16(val))};

		out.append(3 - encoded_addr.length(), '0');
		out += encoded_addr;
		out.append(3 - encoded_val.length(), '0');
		out += encoded_val;
	}

	return out;
}

bl::speaker_cfg::speaker_cfg(std::string_view v) {
	value_stream s{v};
	this->looped = s.parse_num();
	this->sound_id = decode_world_id(s.parse_str());
	this->vol = s.parse_num();
	this->pitch = s.parse_num();
}

std::string bl::speaker_cfg::to_value() const {
	return num_to_value(this->looped)
		+ str_to_value(encode_world_id(this->sound_id))
		+ num_to_value(this->vol)
		+ num_to_value(this->pitch);
}

bl::teleport_module_cfg::teleport_module_cfg(std::string_view v) {
	value_stream s{v};
	this->show_range = s.parse_num();
	std::string offset{s.parse_str()};
	this->range = s.parse_num();

	std::string_view view{offset};
	auto it{view.cbegin()};
	for (auto& item: this->tp_offset) {
		auto r{std::from_chars(it, view.cend(), item)};
		it = r.ptr;
		if (r.ec != std::errc()) {
			item = std::numeric_limits<double>::quiet_NaN();
		}
	}
}

std::string bl::teleport_module_cfg::to_value() const {
	std::string offset{std::format(
		"{} {} {}", this->tp_offset[0], this->tp_offset[1],
		this->tp_offset[2]
	)};

	return num_to_value(this->show_range)
		+ str_to_value(offset)
		+ num_to_value(this->range);
}

bl::legacy_player_detector_cfg::legacy_player_detector_cfg(std::string_view v) {
	value_stream s{v};
	this->show_range = s.parse_num();
	this->activation_perm = s.parse_num();
	this->range = s.parse_num();
}

std::string bl::legacy_player_detector_cfg::to_value() const {
	return num_to_value(this->show_range)
		+ num_to_value(this->activation_perm)
		+ num_to_value(this->range);
}

bl::http_transmitter_cfg::http_transmitter_cfg(std::string_view v) {
	value_stream s{v};
	this->get_requests = s.parse_num();
	this->get_interval = s.parse_num();
	this->headers = s.parse_str();
	this->url = s.parse_str();
}

std::string bl::http_transmitter_cfg::to_value() const {
	return num_to_value(this->get_requests)
		+ num_to_value(this->get_interval)
		+ str_to_value(this->headers)
		+ str_to_value(this->url);
}

bl::legacy_keypad_cfg::legacy_keypad_cfg(std::string_view v) {
	value_stream s{v};
	this->unlock_on_enter_key = s.parse_num();
	this->unlocked_time = s.parse_num();
	this->code_digits = s.parse_str();
	this->show_key_press = s.parse_num();
	this->button_hold_time = s.parse_num();
}

std::string bl::legacy_keypad_cfg::to_value() const {
	return num_to_value(this->unlock_on_enter_key)
		+ num_to_value(this->unlocked_time)
		+ str_to_value(this->code_digits)
		+ num_to_value(this->show_key_press)
		+ num_to_value(this->button_hold_time);
}

bl::precise_randomizer_cfg::precise_randomizer_cfg(std::string_view v) {
	value_stream s{v};
	this->right_percentage = s.parse_num();
}

std::string bl::precise_randomizer_cfg::to_value() const {
	return num_to_value(this->right_percentage);
}

bl::buzzer_cfg::buzzer_cfg(std::string_view v) {
	this->pitch = bl::decode62(v.front());
}

std::string bl::buzzer_cfg::to_value() const {
	return {bl::encode62(this->pitch)};
}

bl::cake_cfg::cake_cfg(std::string_view v) { this->val = decode_world_id(v); }

std::string bl::cake_cfg::to_value() const {
	return encode_world_id(this->val);
}

bl::kill_module_cfg::kill_module_cfg(std::string_view v) {
	value_stream s{v};
	this->show_detection_boundaries = s.parse_num();
	this->kill_when_touched = s.parse_num();
	this->damage = s.parse_num();
	this->detection_size = s.parse_units();
	this->detect_shape = decode_detection_shape(s.parse_num());
	this->shape_orientation = s.parse_units();
	this->shape_offset = s.parse_units();
}

std::string bl::kill_module_cfg::to_value() const {
	return num_to_value(this->show_detection_boundaries)
		+ num_to_value(this->kill_when_touched)
		+ num_to_value(this->damage)
		+ units_to_value(this->detection_size)
		+ num_to_value(
			get_detection_shape_traits(this->detect_shape).encoded
		)
		+ units_to_value(this->shape_orientation)
		+ units_to_value(this->shape_offset);
}

bl::player_detector_cfg::player_detector_cfg(std::string_view v) {
	value_stream s{v};
	this->show_detection_boundaries = s.parse_num();
	this->activation_sel = s.parse_str();
	this->detection_size = s.parse_units();
	this->detect_shape = decode_detection_shape(s.parse_num());
	this->shape_orientation = s.parse_units();
	this->shape_offset = s.parse_units();
}

std::string bl::player_detector_cfg::to_value() const {
	return num_to_value(this->show_detection_boundaries)
		+ str_to_value(this->activation_sel)
		+ units_to_value(this->detection_size)
		+ num_to_value(
			get_detection_shape_traits(this->detect_shape).encoded
		)
		+ units_to_value(this->shape_orientation)
		+ units_to_value(this->shape_offset);
}

// Note: The `Code_Digits` member has to be cleared because later we'll be
// appending to it without destroying its old contents, which is the default
// value of "1234".
bl::keypad_cfg::keypad_cfg(std::string_view v): code_digits{} {
	value_stream s{v};
	this->unlock_on_enter_key = s.parse_num();
	this->unlocked_time = s.parse_num();
	std::string code{s.parse_str()};
	this->show_key_press = s.parse_num();
	this->button_hold_time = s.parse_num();

	auto it{code.cbegin()};
	while (it != code.cend()) {
		auto chunk_beg{it};
		while (it != code.cend() && *it != ':') { ++it; }

		std::string_view chunk{chunk_beg, it};

		// Consume the `:`, if there was any.
		if (*it == ':') { ++it; }

		std::size_t num{bl::decode_world_id(chunk)};
		std::string decoded{std::format("{}", num)};

		// Drop the leading `1` in `decoded` and append it to the code
		// digits. This is only an append, therefore requiring the clear
		// of `Code_Digits` beforehand.
		this->code_digits.append(decoded, 1);
	}
}

std::string bl::keypad_cfg::to_value() const {
	std::string code{};

	for (std::size_t i{}; i < this->code_digits.length(); i += 8) {
		std::string chunk{this->code_digits.substr(i, 8)};
		chunk.insert(chunk.cbegin(), '1');
		std::string_view chunk_view{chunk};
		std::size_t num{};
		std::from_chars(chunk_view.cbegin(), chunk_view.cend(), num);
		code += encode_world_id(num);
		code += ':';
	}

	if (code.back() == ':') { code.pop_back(); }

	return num_to_value(this->unlock_on_enter_key)
		+ num_to_value(this->unlocked_time)
		+ str_to_value(code)
		+ num_to_value(this->show_key_press)
		+ num_to_value(this->button_hold_time);
}
