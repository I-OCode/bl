#include "bl.hpp"
#include <algorithm>
#include <mutex>
#include <stdexcept>

bl::vec3::vec3(std::span<char const, 4> v) {
	int a{bl::decode_bl64(v[0])};
	int b{bl::decode_bl64(v[1])};
	int c{bl::decode_bl64(v[2])};
	int d{bl::decode_bl64(v[3])};

	this->x = 64 * (b % 4) + a;
	this->y = 16 * (c % 16) + b / 4;
	this->z = 4 * d + c / 16;
}

std::array<char, 4> bl::vec3::encode() const {
	return {bl::encode_bl64(this->x % 64),
		bl::encode_bl64(this->x / 64 + this->y * 4 % 64),
		bl::encode_bl64(this->y / 16 + this->z * 16 % 64),
		bl::encode_bl64(this->z / 4)};
}

bl::rotation::rotation(char v) {
	auto decoded{bl::decode_bl64(v)};

	this->z = decoded / 16 % 4;
	this->y = (decoded / 4 - this->z * 4) % 4;
	this->x = (decoded - this->y * 4 - this->z * 16) % 4;
}

char bl::rotation::encode() const {
	return bl::encode_bl64(this->x + this->y * 4 + this->z * 16);
}

bl::unique_id bl::unique_id::create() {
	auto max{std::numeric_limits<std::uint_least64_t>::max()};

	static std::uint_least64_t a{};
	static std::uint_least64_t b{};
	static std::uint_least64_t c{};
	static std::uint_least64_t d{};
	static std::mutex mtx{};

	bl::unique_id id{};

	{
		std::lock_guard<std::mutex> lk{mtx};
		if ((id._a = a++) == max) {
			if ((id._b = b++) == max) {
				if ((id._c = c++) == max) {
					if ((id._d = d++) == max) {
						// If you somehow manage to
						// overflow four 64-bit
						// counters, you get rewarded
						// with 42. That's it.
						throw 42;
					}
				}
			}
		}
	}

	return id;
}

std::string bl::encode_world_id(std::size_t v) {
	std::string s{};

	do {
		auto r{v % 71};
		v /= 71;
		s += encode_bl71(r);
	} while (v != 0);

	std::ranges::reverse(s);
	return s;
}

std::size_t bl::decode_world_id(std::string_view v) {
	std::size_t r{};
	for (auto c: v) {
		r *= 71;
		r += decode_bl71(c);
	}

	return r;
}

std::string bl::encode_units(std::size_t v) {
	std::string s{};

	do {
		auto r{v % 75};
		v /= 75;
		s += encode_bl75(r);
	} while (v != 0);

	std::ranges::reverse(s);
	return s;
}

std::size_t bl::decode_units(std::string_view v) {
	std::size_t r{};
	for (auto c: v) {
		r *= 75;
		r += decode_bl75(c);
	}

	return r;
}

char bl::encode62(std::uint8_t v) {
	if (v >= 0 && v <= 9) {
		return '0' + v;
	} else if (v >= 10 && v <= 35) {
		return 'a' + (v - 10);
	} else if (v >= 36 && v <= 61) {
		return 'A' + (v - 36);
	}

	throw std::out_of_range("'v' not in [0, 61]");
}

char bl::encode_bl64(std::uint8_t v) {
	if (v >= 0 && v <= 25) {
		return 'A' + v;
	} else if (v >= 26 && v <= 51) {
		return 'a' + (v - 26);
	} else if (v >= 52 && v <= 61) {
		return '0' + (v - 52);
	} else if (v >= 62 && v <= 63) {
		return '#' + (v - 62);
	}

	throw std::out_of_range("'v' not in [0, 63]");
}

char bl::encode_bl71(std::uint8_t v) {
	if (v >= 0 && v <= 61) {
		return encode62(v);
	} else if (v >= 62 && v <= 70) {
		return "!@$%?&<()"[v - 62];
	}

	throw std::out_of_range("'v' not in [0, 70]");
}

char bl::encode_bl75(std::uint8_t v) {
	if (v >= 0 && v <= 25) {
		return 'a' + v;
	} else if (v >= 26 && v <= 51) {
		return 'A' + (v - 26);
	} else if (v >= 52 && v <= 74) {
		return "!@#$%?&<>()+_*{}[]~`'\"|"[v - 52];
	}

	throw std::out_of_range("'v' not in [0, 74]");
}

char bl::encode_bl82(std::uint8_t v) {
	if (v >= 0 && v <= 61) {
		return encode62(v);
	} else if (v >= 62 && v <= 81) {
		// Notice how there are two `!`s here.
		return "!@$%?&#<()*+-/:,!._="[v - 62];
	}

	throw std::out_of_range("'v' not in [0, 81]");
}

std::uint8_t bl::decode62(char v) {
	if (v >= '0' && v <= '9') {
		return v - '0';
	} else if (v >= 'a' && v <= 'z') {
		return (v - 'a') + 10;
	} else if (v >= 'A' && v <= 'Z') {
		return (v - 'A') + 36;
	}

	throw std::out_of_range("'v' not in [0-9a-zA-Z]");
}

std::uint8_t bl::decode_bl64(char v) {
	if (v >= 'A' && v <= 'Z') {
		return v - 'A';
	} else if (v >= 'a' && v <= 'z') {
		return (v - 'a') + 26;
	} else if (v >= '0' && v <= '9') {
		return (v - '0') + 52;
	} else if (v >= '#' && v <= '$') {
		return (v - '#') + 62;
	}

	throw std::out_of_range("'v' not in [A-Za-z0-9#$]");
}

std::uint8_t bl::decode_bl71(char v) {
	switch (v) {
	case '!': return 62;
	case '@': return 63;
	case '$': return 64;
	case '%': return 65;
	case '?': return 66;
	case '&': return 67;
	case '<': return 68;
	case '(': return 69;
	case ')': return 70;
	default: try { return decode62(v);
		} catch (...) {}
	}

	throw std::out_of_range("'v' not in [0-9a-zA-Z!@$%?&<()]");
}

std::uint8_t bl::decode_bl75(char v) {
	switch (v) {
	case '!': return 52;
	case '@': return 53;
	case '#': return 54;
	case '$': return 55;
	case '%': return 56;
	case '?': return 57;
	case '&': return 58;
	case '<': return 59;
	case '>': return 60;
	case '(': return 61;
	case ')': return 62;
	case '+': return 63;
	case '_': return 64;
	case '*': return 65;
	case '{': return 66;
	case '}': return 67;
	case '[': return 68;
	case ']': return 69;
	case '~': return 70;
	case '`': return 71;
	case '\'': return 72;
	case '"': return 73;
	case '|': return 74;
	default:
		if (v >= 'a' && v <= 'z') {
			return v - 'a';
		} else if (v >= 'A' && v <= 'Z') {
			return (v - 'A') + 26;
		}
	}

	throw std::out_of_range("'v' not in []a-zA-Z!@#$%?&<>()+_*{}[~`'\"|]");
}

std::uint8_t bl::decode_bl82(char v) {
	switch (v) {
	// The game decodes `!` to 78 and not 62.
	// case '!': return 62;
	case '@': return 63;
	case '$': return 64;
	case '%': return 65;
	case '?': return 66;
	case '&': return 67;
	case '#': return 68;
	case '<': return 69;
	case '(': return 70;
	case ')': return 71;
	case '*': return 72;
	case '+': return 73;
	case '-': return 74;
	case '/': return 75;
	case ':': return 76;
	case ',': return 77;
	case '!': return 78;
	case '.': return 79;
	case '_': return 80;
	case '=': return 81;
	default: try { return decode62(v);
		} catch (...) {}
	}

	throw std::out_of_range("'v' not in [0-9a-zA-Z@$%?&#<()*+-/:,!._=]");
}
