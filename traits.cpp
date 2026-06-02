#include "bl.hpp"
#include <unordered_map>

template<
	class enum_type, class traits_type, class trait_type,
	class stored_trait_type, trait_type traits_type::* trait_ptr,
	std::unordered_map<enum_type, traits_type> const& db_get_fn()
>
class trait_lookup_db {
public:
	std::unordered_map<stored_trait_type, enum_type> map{};

	trait_lookup_db() {
		for (auto const& [type, trait]: db_get_fn()) {
			this->map[stored_trait_type(trait.*trait_ptr)] = type;
		}
	}
};

#define T true
#define F false
#define X(v, ...) {e##v, {__VA_ARGS__}},

static auto const& get_block_type_db() {
	using enum bl::block_type;
	static std::unordered_map<bl::block_type, bl::block_type_traits> map{
#include "block_type_db.txt"
	};

	return map;
}

static auto const& get_material_db() {
	using enum bl::material;
	static std::unordered_map<bl::material, bl::material_traits> map{
#include "material_db.txt"
	};

	return map;
}

static auto const& get_timer_interval_db() {
	using enum bl::timer_interval;
	static std::unordered_map<bl::timer_interval, bl::timer_interval_traits> map{
#include "timer_interval_db.txt"
	};

	return map;
}

static auto const& get_delay_interval_db() {
	using enum bl::delay_interval;
	static std::unordered_map<bl::delay_interval, bl::delay_interval_traits> map{
#include "delay_interval_db.txt"
	};

	return map;
}

static auto const& get_detection_shape_db() {
	using enum bl::detection_shape;
	static std::unordered_map<bl::detection_shape, bl::detection_shape_traits> map{
#include "detection_shape_db.txt"
	};

	return map;
}

#undef T
#undef F
#undef X

bl::block_type_traits bl::get_block_type_traits(block_type type) {
	return get_block_type_db().at(type);
}

bl::material_traits bl::get_material_traits(material v) {
	return get_material_db().at(v);
}

bl::delay_interval_traits
bl::get_delay_interval_traits(delay_interval interval) {
	return get_delay_interval_db().at(interval);
}

bl::timer_interval_traits
bl::get_timer_interval_traits(timer_interval interval) {
	return get_timer_interval_db().at(interval);
}

bl::detection_shape_traits
bl::get_detection_shape_traits(detection_shape shape) {
	return get_detection_shape_db().at(shape);
}

bl::detection_shape bl::decode_detection_shape(std::size_t v) {
	static trait_lookup_db<
		detection_shape, detection_shape_traits, std::size_t,
		std::size_t, &bl::detection_shape_traits::encoded,
		get_detection_shape_db
	>
		db{};

	return db.map.at(v);
}

bl::block_type bl::block_type_from_encoded_name(std::string_view v) {
	static trait_lookup_db<
		bl::block_type, bl::block_type_traits, std::string_view,
		std::string, &bl::block_type_traits::encoded, get_block_type_db
	>
		db{};

	return db.map.at(std::string(v));
}

bl::block_type bl::block_type_from_block_id(std::size_t v) {
	static trait_lookup_db<
		bl::block_type, bl::block_type_traits, std::size_t, std::size_t,
		&bl::block_type_traits::id, get_block_type_db
	>
		db{};

	return db.map.at(v);
}

bl::material bl::decode_material(char v) {
	static trait_lookup_db<
		bl::material, bl::material_traits, char, char,
		&bl::material_traits::encoded, get_material_db
	>
		db{};

	return db.map.at(v);
}

bl::delay_interval bl::decode_delay_interval(char v) {
	static trait_lookup_db<
		bl::delay_interval, bl::delay_interval_traits, char, char,
		&bl::delay_interval_traits::encoded, get_delay_interval_db
	>
		db{};

	return db.map.at(v);
}

bl::timer_interval bl::decode_timer_interval(char v) {
	static trait_lookup_db<
		bl::timer_interval, bl::timer_interval_traits, char, char,
		&bl::timer_interval_traits::encoded, get_timer_interval_db
	>
		db{};

	return db.map.at(v);
}
