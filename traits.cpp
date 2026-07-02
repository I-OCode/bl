#include "bl.hpp"

#define T true
#define F false

#define X(enum_, ...) case e##enum_: return {__VA_ARGS__};

bl::block_name_traits bl::block_name_traits::doit(bl::block_name name) {
	using enum bl::block_name;
	switch (name) {
#include "block_name_db.txt"
	}
}

bl::material_traits bl::material_traits::doit(material mat) {
	using enum bl::material;
	switch (mat) {
#include "material_db.txt"
	}
}

bl::delay_interval_traits
bl::delay_interval_traits::doit(delay_interval interval) {
	using enum bl::delay_interval;
	switch (interval) {
#include "delay_interval_db.txt"
	}
}

bl::timer_interval_traits
bl::timer_interval_traits::doit(timer_interval interval) {
	using enum bl::timer_interval;
	switch (interval) {
#include "timer_interval_db.txt"
	}
}

bl::detection_shape_traits
bl::detection_shape_traits::doit(detection_shape shape) {
	using enum bl::detection_shape;
	switch (shape) {
#include "detection_shape_db.txt"
	}
}

#undef X

bl::block_name bl::decode_block_name(std::string_view v) {
	using enum bl::block_name;
	static std::unordered_map<std::string, bl::block_name> map{
#define X(enum_, name_, enc_, id_, comp_) {enc_, e##enum_},
#include "block_name_db.txt"
#undef X
	};

	return map.at(std::string(v));
}

bl::block_name bl::block_name_from_block_id(std::size_t v) {
	using enum bl::block_name;
	static std::unordered_map<std::size_t, bl::block_name> map{
#define X(enum_, name_, enc_, id_, comp_) {id_, e##enum_},
#include "block_name_db.txt"
#undef X
	};

	return map.at(v);
}

bl::material bl::decode_material(char v) {
	using enum bl::material;
	static std::unordered_map<char, bl::material> map{
#define X(enum_, name_, enc_) {enc_, e##enum_},
#include "material_db.txt"
#undef X
	};

	return map.at(v);
}

bl::delay_interval bl::decode_delay_interval(char v) {
	using enum bl::delay_interval;
	static std::unordered_map<char, bl::delay_interval> map{
#define X(enum_, name_, enc_) {enc_, e##enum_},
#include "delay_interval_db.txt"
#undef X
	};

	return map.at(v);
}

bl::timer_interval bl::decode_timer_interval(char v) {
	using enum bl::timer_interval;
	static std::unordered_map<char, bl::timer_interval> map{
#define X(enum_, name_, enc_) {enc_, e##enum_},
#include "timer_interval_db.txt"
#undef X
	};

	return map.at(v);
}

bl::detection_shape bl::decode_detection_shape(std::size_t v) {
	using enum bl::detection_shape;
	static std::unordered_map<std::size_t, bl::detection_shape> map{
#define X(enum_, name_, enc_) {enc_, e##enum_},
#include "detection_shape_db.txt"
#undef X
	};

	return map.at(v);
}

#undef T
#undef F
