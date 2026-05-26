#include "bl.hpp"
#include <format>
#include <limits>
#include <ranges>

static constexpr std::array rev4{
	0x0, 0x8, 0x4, 0xC, 0x2, 0xA, 0x6, 0xE, 0x1, 0x9, 0x5, 0xD, 0x3, 0xB,
	0x7, 0xF
};

static std::uint8_t bit_reverse8(std::uint8_t value) {
	return rev4[value & 0xF] << 4 | rev4[value >> 4];
}

static std::uint16_t bit_reverse16(std::uint16_t value) {
	return rev4[value & 0xF] << 12
		| rev4[value >> 4 & 0xF] << 8
		| rev4[value >> 8 & 0xF] << 4
		| rev4[value >> 12 & 0xF];
}

static std::string_view::const_iterator
parse_value_impl(std::string_view::const_iterator& i, std::string_view v) {
	if (i == v.cend()) { return i; }

	if (*i == '`') { return i; }

	std::size_t len{};

	char c{*i++};
	if (c == '|') {
		auto beg{i};
		while (*i != '~') { ++i; }

		len = bl::decode_field_len({beg, i});

		// Consume the `~`.
		++i;
	} else {
		len = bl::decode_bl82(c) + 1;
	}

	auto beg{i};
	i += len;

	if (len == 0 || i > v.cend()) { i = v.cend(); }

	return beg;
}

template<class type>
static void parse_value(
	std::string_view::const_iterator& i, std::string_view v, type& out
) {
	double n{};

	parse_value<double>(i, v, n);
	out = n;
}

template<>
void parse_value<
	std::string
>(std::string_view::const_iterator& i, std::string_view v, std::string& out) {
	auto beg{parse_value_impl(i, v)};
	if (beg == v.cend()) { return; }

	out.assign(beg, i);
}

template<>
void parse_value<double>(
	std::string_view::const_iterator& i, std::string_view v, double& out
) {
	auto beg{parse_value_impl(i, v)};
	if (beg == v.cend()) { return; }

	if (std::from_chars(beg, i, out).ec != std::errc()) {
		out = std::numeric_limits<double>::quiet_NaN();
	}
}

template<class first_type, class... rest_types>
static void parse_value(
	std::string_view::const_iterator& i, std::string_view v,
	first_type& first, rest_types&... rest
) {
	parse_value(i, v, first);
	parse_value(i, v, rest...);
}

template<class... types>
static void to_config_impl(std::string_view v, types&... outs) {
	auto i{v.cbegin()};
	parse_value(i, v, outs...);
}

static std::string to_value_impl(std::string const& s) {
	if (s.empty()) {
		// The game uses a backtick in place of the length to represent
		// the empty string.
		return "`";
	}

	// If the length is too long to fit in the BL82 charset then the game
	// uses an alternative format where `|` and `~` are the beginning and
	// ending delimiters, respectively.
	if (s.length() > 82) {
		return '|' + bl::encode_field_len(s.length()) + '~';
	}

	return bl::encode_bl82(s.length() - 1) + s;
}

template<class type>
static std::string to_value_impl(type v) {
	return to_value_impl(std::format("{}", v));
}

template<>
std::string to_value_impl<bool>(bool v) {
	return to_value_impl<unsigned>(v);
}

template<class first_type, class... rest_types>
static std::string
to_value_impl(first_type const& first, rest_types const&... rest) {
	return to_value_impl(first) + to_value_impl(rest...);
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
	to_config_impl(v, this->show_range, this->damage, this->range);
}

std::string bl::legacy_kill_module_cfg::to_value() const {
	return to_value_impl(this->show_range, this->damage, this->range);
}

bl::dip_switches_cfg::dip_switches_cfg(std::string_view v) {
	this->val = bl::decode_bl71(v.front());
}

std::string bl::dip_switches_cfg::to_value() const {
	return {bl::encode_bl71(this->val)};
}

bl::eeprom_cfg::eeprom_cfg(std::string_view v) {
	for (auto i{v.cbegin()}; i < v.cend(); i += 4) {
		std::uint8_t decoded_addr{
			bit_reverse8(decode_world_id({i, i + 2}))
		};

		std::uint8_t decoded_val{
			bit_reverse8(decode_world_id({i + 2, i + 4}))
		};

		this->mem[decoded_addr] = decoded_val;
	}
}

std::string bl::eeprom_cfg::to_value() const {
	std::string out{};

	for (auto item: this->mem) {
		std::string encoded_addr{
			encode_world_id(bit_reverse8(item.first))
		};

		std::string encoded_val{
			encode_world_id(bit_reverse8(item.second))
		};

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
	to_config_impl(v, this->show_range, this->range);
}

std::string bl::tnt_activator_cfg::to_value() const {
	return to_value_impl(this->show_range, this->range);
}

bl::eeprom16_cfg::eeprom16_cfg(std::string_view v) {
	for (auto i{v.cbegin()}; i < v.cend(); i += 6) {
		std::uint16_t decoded_addr{
			bit_reverse16(decode_world_id({i, i + 3}))
		};

		std::uint16_t decoded_val{
			bit_reverse16(decode_world_id({i + 3, i + 6}))
		};

		this->mem[decoded_addr] = decoded_val;
	}
}

std::string bl::eeprom16_cfg::to_value() const {
	std::string out{};

	for (auto item: this->mem) {
		std::string encoded_addr{
			encode_world_id(bit_reverse16(item.first))
		};

		std::string encoded_val{
			encode_world_id(bit_reverse16(item.second))
		};

		out.append(3 - encoded_addr.length(), '0');
		out += encoded_addr;
		out.append(3 - encoded_val.length(), '0');
		out += encoded_val;
	}

	return out;
}

bl::speaker_cfg::speaker_cfg(std::string_view v) {
	std::string sound_id{};
	to_config_impl(v, this->looped, sound_id, this->vol, this->pitch);

	this->sound_id = decode_world_id(sound_id);
}

std::string bl::speaker_cfg::to_value() const {
	return to_value_impl(
		this->looped, encode_world_id(this->sound_id), this->vol,
		this->pitch
	);
}

bl::teleport_module_cfg::teleport_module_cfg(std::string_view v) {
	std::string str_offset{};
	to_config_impl(v, this->show_range, str_offset, this->range);
	std::string_view offset{str_offset};

	auto it{offset.cbegin()};
	for (auto& item: this->tp_offset) {
		auto r{std::from_chars(it, offset.cend(), item)};
		it = r.ptr;
		if (r.ec != std::errc()) {
			item = std::numeric_limits<double>::quiet_NaN();
		}
	}
}

std::string bl::teleport_module_cfg::to_value() const {
	std::string tp_offset{std::format(
		"{} {} {}", this->tp_offset[0], this->tp_offset[1],
		this->tp_offset[2]
	)};

	return to_value_impl(this->show_range, tp_offset, this->range);
}

bl::legacy_player_detector_cfg::legacy_player_detector_cfg(std::string_view v) {
	to_config_impl(v, this->show_range, this->activation_perm, this->range);
}

std::string bl::legacy_player_detector_cfg::to_value() const {
	return to_value_impl(
		this->show_range, this->activation_perm, this->range
	);
}

bl::http_transmitter_cfg::http_transmitter_cfg(std::string_view v) {
	to_config_impl(
		v, this->get_requests, this->get_interval, this->headers,
		this->url
	);
}

std::string bl::http_transmitter_cfg::to_value() const {
	return to_value_impl(
		this->get_requests, this->get_interval, this->headers, this->url
	);
}

bl::legacy_keypad_cfg::legacy_keypad_cfg(std::string_view v) {
	to_config_impl(
		v, this->unlock_on_enter_key, this->unlocked_time,
		this->code_digits, this->show_key_press, this->button_hold_time
	);
}

std::string bl::legacy_keypad_cfg::to_value() const {
	return to_value_impl(
		this->unlock_on_enter_key, this->unlocked_time,
		this->code_digits, this->show_key_press, this->button_hold_time
	);
}

bl::precise_randomizer_cfg::precise_randomizer_cfg(std::string_view v) {
	to_config_impl(v, this->right_percentage);
}

std::string bl::precise_randomizer_cfg::to_value() const {
	return to_value_impl(this->right_percentage);
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

static std::array<double, 3> parse_units(std::string_view v) {
	std::array<double, 3> units{};
	std::size_t axis_idx{};
	auto it{v.cbegin()};

	while (it != v.cend()) {
		auto axis_beg{it};
		while (it != v.cend() && *it != ',') { ++it; }

		std::string_view axis{axis_beg, it};

		// Consume the `,`, if there was any.
		if (*it == ',') { ++it; }

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

static std::string create_units(std::span<double const, 3> v) {
	std::string s{};
	for (auto axis: v) {
		if (axis < 0) { s += '-'; }

		s += bl::encode_units(std::abs(axis));
		s += ',';
	}

	// Remove the trailing `,`, if there was any.
	if (s.back() == ',') { s.pop_back(); }

	return s;
}

bl::kill_module_cfg::kill_module_cfg(std::string_view v) {
	std::size_t shape{};
	std::string size{};
	std::string orientation{};
	std::string offset{};

	to_config_impl(
		v, this->show_detection_boundaries, this->kill_when_touched,
		this->damage, size, shape, orientation, offset
	);

	this->detection_size = parse_units(size);
	this->shape_orientation = parse_units(orientation);
	this->shape_offset = parse_units(offset);
	this->detect_shape = decode_detection_shape(shape);
}

std::string bl::kill_module_cfg::to_value() const {
	return to_value_impl(
		this->show_detection_boundaries, this->kill_when_touched,
		this->damage, create_units(this->detection_size),
		get_detection_shape_traits(this->detect_shape).encoded,
		create_units(this->shape_orientation),
		create_units(this->shape_offset)
	);
}

bl::player_detector_cfg::player_detector_cfg(std::string_view v) {
	std::size_t shape{};
	std::string size{};
	std::string orientation{};
	std::string offset{};

	to_config_impl(
		v, this->show_detection_boundaries, this->activation_sel, size,
		shape, orientation, offset
	);

	this->detection_size = parse_units(size);
	this->shape_orientation = parse_units(orientation);
	this->shape_offset = parse_units(offset);
	this->detect_shape = decode_detection_shape(shape);
}

std::string bl::player_detector_cfg::to_value() const {
	return to_value_impl(
		this->show_detection_boundaries, this->activation_sel,
		create_units(this->detection_size),
		get_detection_shape_traits(this->detect_shape).encoded,
		create_units(this->shape_orientation),
		create_units(this->shape_offset)
	);
}

// Note: The `Code_Digits` member has to be cleared because later we'll be
// appending to it without destroying its old contents, which is the default
// value of "1234".
bl::keypad_cfg::keypad_cfg(std::string_view v): code_digits{} {
	std::string code{};

	to_config_impl(
		v, this->unlock_on_enter_key, this->unlocked_time, code,
		this->show_key_press, this->button_hold_time
	);

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

	return to_value_impl(
		this->unlock_on_enter_key, this->unlocked_time, code,
		this->show_key_press, this->button_hold_time
	);
}
