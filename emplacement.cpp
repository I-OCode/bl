#include "bl.hpp"
#include "detail.hpp"
#include <algorithm>
#include <ranges>
#include <vector>

// Same as `bl::block_wire` except that world IDs are used to represent the
// blocks instead of unique IDs, since the game uses world IDs for wires.
class pending_wire {
public:
	std::size_t from_blk{};
	std::size_t to_blk{};
	char from_con{};
	char to_con{};
};

static auto gen_world_ids(bl::emplacement const* em) {
	// World IDs don't *have* to begin at 1.
	std::size_t world_id{};

	std::unordered_map<bl::unique_id, std::size_t> world_ids{};
	for (auto const& item: em->blks) { world_ids[item.first] = world_id++; }

	return world_ids;
}

bl::emplacement::emplacement(std::string_view src) {
	stream main{src};
	std::unordered_map<std::size_t, unique_id> ids{};
	std::vector<pending_wire> pending_wires{};

	while (!main.eof()) {
		stream blk_beg{main};
		main.read_until(";");

		// Subsection of the `main` stream containing the current block.
		stream blk{
			{blk_beg.i, main.i}
		};

		// Munch the `;`, if there was any.
		main.read_single();

		std::array<char, 3> encoded_name{blk.read_single().value()};
		if (is_one_of(encoded_name[0], "#%")) {
			encoded_name[1] = blk.read_single().value();
		}

		stream encoded_beg{blk};
		blk.read_until("/=>^");

		// Subsection of the `blk` stream containing the encoded name,
		// position, rotation, color, and material.
		stream encoded{
			{encoded_beg.i, blk.i}
		};

		block info{};
		info.type = block_type_from_encoded_name(encoded_name.data());
		info.pos = encoded.read<4>().value();

		// Let's say that we have a block `G$BwfA3`, where the rotation
		// and material were specified but the color was not. Well,
		// then...

		// ...the encoded rotation would be read successfully because
		// `A3` is left in the stream, which is enough to read the `A`
		// and decode it into a rotation. This results in the default
		// rotation (`A`) being used, which is correct. Then...
		info.rot = encoded.read_single().value_or(rotation().encode());

		// ...the encoded color could not be read because only `3` is
		// left in the `encoded` stream, which is not enough for a
		// complete encoded color. This results in a default color being
		// used instead, which is correct. Then...
		info.color = encoded.read<4>().value_or(vec3(255).encode());

		auto default_encoded_mat{
			get_material_traits(material::eDefault).encoded
		};

		// ...the encoded material would be read successfuly because `3`
		// is enough to decode it into a material. This results in the
		// material corresponding to `3` (Diamond Plate) being used,
		// which is correct. Success.
		info.mat = decode_material(
			encoded.read_single().value_or(default_encoded_mat)
		);

		bool slash_found{};
		if (blk.peek_single() == '/') { slash_found = true; }

		bool val_end_sep_found{};
		stream value_beg{blk};
		stream value_cur{blk};
		// This effectively sets the `blk` stream to be positioned
		// at the last `=`, `>`, or `^` in the current block. However if
		// a value separator was found, `>` is ignored.
		for (;;) {
			auto look_for{slash_found ? "=^" : "=>^"};
			if (is_one_of(value_cur.peek_single(), look_for)) {
				blk = value_cur;
				val_end_sep_found = true;
			}

			if (value_cur.eof()) { break; }

			value_cur.read_single();
		}

		// If a `=` or `^` wasn't found, then we just use the end of the
		// block.
		if (!val_end_sep_found) { blk = value_cur; }

		stream value{
			{value_beg.i, blk.i}
		};

		pending_wire pending1{};

		// Values.
		if (value.peek_single() == '/') {
			// Consume the `/`.
			value.read_single();

			while (!value.eof()) {
				char c{value.read_single().value()};
				// Value escape.
				if (
					c == '/'
					&& is_one_of(value.peek_single(), "=^")
				) {
					c = value.read_single().value();
				}

				info.value += c;
			}
		}

		if (blk.eof()) {
			// Move on if there's nothing left in this block.
			ids[pending1.to_blk] = this->place(info);
			continue;
		}

		// Otherwise we deal with world IDs and wires.

		info.activated = blk.peek_single() == '>';
		if (is_one_of(blk.peek_single(), "=>")) {
			// Consume the `=` or `>`.
			blk.read_single();
			pending1.to_blk = decode_world_id(blk.read_until(""));
			ids[pending1.to_blk] = this->place(info);
			continue;
		}

		// Consume the `^` (since `=` and `>` have been ruled out).
		blk.read_single();

		// First destination connector.
		pending1.to_con = blk.read_single().value();

		// World ID.
		pending1.to_blk = bl::decode_world_id(blk.read_until("_-"));

		bool to_self1{blk.peek_single() == '-'};
		// Consume the `_` or `-`.
		blk.read_single();

		pending1.from_con = blk.read_single().value();

		pending1.from_blk = {
			to_self1 ? pending1.to_blk
				 : bl::decode_world_id(blk.read_until(".*"))
		};

		pending_wires.push_back(pending1);

		// The final stretch.
		while (!blk.eof()) {
			pending_wire pending{};
			bool to_self{blk.peek_single() == '*'};
			// Consume the `.` or `*`.
			blk.read_single();

			pending.to_blk = pending1.to_blk;

			pending.to_con = blk.read_single().value();

			auto from_blk_con{blk.read_until(".*")};

			std::string_view from_blk{
				from_blk_con
				| std::views::take(from_blk_con.length() - 1)
			};

			char from_con{from_blk_con.back()};

			pending.from_blk = to_self
				? pending.to_blk
				: bl::decode_world_id(from_blk);

			pending.from_con = from_con;

			pending_wires.push_back(pending);
		}

		ids[pending1.to_blk] = this->place(info);
	}

	// Now we just need to actually create the pending wires we've
	// accumulated. Wires aren't created immediately after parsing them
	// because they may reference other blocks that haven't been parsed yet.
	for (auto const& wire: pending_wires) {
		this->connect(
			{ids.at(wire.from_blk), ids.at(wire.to_blk),
				wire.from_con, wire.to_con}
		);
	}
}

std::string bl::emplacement::save() const {
	std::vector<block_wire> sorted_wires{};
	sorted_wires.reserve(this->wires.size());

	for (auto const& item: this->wires) {
		sorted_wires.push_back(item.second);
	}

	std::sort(
		sorted_wires.begin(), sorted_wires.end(),
		[](block_wire const& a, block_wire const& b) {
			return a.to_blk < b.to_blk;
		}
	);

	std::unordered_map<unique_id, std::span<block_wire const>> in_wires{};

	std::span<block_wire const> span{
		sorted_wires.cbegin(), sorted_wires.cbegin()
	};

	for (auto const& wire: sorted_wires) {
		if (!span.empty() && wire.to_blk != span.back().to_blk) {
			in_wires[span.back().to_blk] = span;
			span = {span.end(), span.end()};
		}

		span = {span.begin(), span.end() + 1};
	}

	if (!span.empty()) { in_wires[span.back().to_blk] = span; }

	auto world_ids{gen_world_ids(this)};

	std::string out{};

	for (auto const& [id, blk]: this->blks) {
		auto traits{get_block_type_traits(blk.type)};

		// Encoded name.
		out += traits.encoded;

		// Then the position.
		out.append(blk.pos.encode().data(), 4);

		// This is where it gets a little interesting. The rotation must
		// be specified if anything after it (color, material, value,
		// world ID, wires) will be specified.

		if (blk.rot != rotation()
			|| blk.color != vec3(255)
			|| blk.mat != material::eDefault
			|| !blk.value.empty()
			|| traits.component) {
			out += blk.rot.encode();
		}

		// Colors don't have any particular restriction.
		if (blk.color != vec3(255)) {
			out.append(blk.color.encode().data(), 4);
		}

		// Materials have no restrictions either. This means that you
		// can specify the rotation and the material but not the color,
		// and it'll still work.
		if (blk.mat != material::eDefault) {
			out += get_material_traits(blk.mat).encoded;
		}

		if (!blk.value.empty()) {
			// Values begin with a `/`.
			out += '/';
			if (traits.component) {
				out += blk.value;
			} else {
				// Non-component blocks need `=`s and `^`s to be
				// "escaped" using `/`, so to speak.
				for (auto c: blk.value) {
					if (is_one_of(c, "=^")) { out += '/'; }

					out += c;
				}
			}
		}

		if (!traits.component) {
			out += ';';
			continue;
		}

		// Encode any wires if the block is a component.

		// `=` introduces a world ID. `>` is the same but indicates that
		// the block is activated. Finally, `^` introduces wires.

		auto wire_span_it{in_wires.find(id)};
		bool has_wires{wire_span_it != in_wires.cend()};

		std::span<bl::block_wire const> wire_span{};
		if (has_wires) { wire_span = wire_span_it->second; }

		auto wire_it{wire_span.begin()};

		out += blk.activated ? '>' : (has_wires ? '^' : '=');

		// Destination connector.
		if (has_wires) { out += wire_it->to_con; }

		std::size_t cur_world_id{world_ids.at(id)};

		// Destination world ID.
		out += bl::encode_world_id(cur_world_id);

		if (!has_wires) {
			out += ';';
			continue;
		}

		auto from_world_id{world_ids.at(wire_it->from_blk)};
		bool to_self{cur_world_id == from_world_id};

		out += to_self ? '-' : '_';

		// Source connector.
		out += wire_it->from_con;

		// Source world ID. This is omitted if the wire is
		// targetting itself.
		if (!to_self) { out += bl::encode_world_id(from_world_id); }

		++wire_it;

		// Now for the rest of the wires.
		for (; wire_it != wire_span.end(); ++wire_it) {
			auto from_world_id{world_ids.at(wire_it->from_blk)};
			bool to_self{cur_world_id == from_world_id};

			out += to_self ? '*' : '.';

			// Destination connector.
			out += wire_it->to_con;

			// Source world ID. This is omitted if the wire is
			// targetting itself.
			if (!to_self) {
				out += bl::encode_world_id(from_world_id);
			}

			// Source connector.
			out += wire_it->from_con;
		}

		// Block terminator.
		out += ';';
	}

	// Remove the trailing `;`.
	if (!this->blks.empty()) { out.pop_back(); }

	return out;
}
