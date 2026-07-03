#pragma once

#include <optional>
#include <string_view>

// Simple function to check if a character is one of the given characters in
// `set`.
inline bool is_one_of(std::optional<char> c, std::string_view set) noexcept {
	for (auto x: set) {
		if (c == x) { return true; }
	}

	return false;
}

// Stream-like/stream-based string parser.
class stream {
public:
	std::string_view s{};
	std::string_view::const_iterator i{};

	stream(std::string_view s_): s{s_}, i{s_.cbegin()} {}

	std::size_t chars_left() const noexcept {
		return this->s.cend() - this->i;
	}

	bool could_read(std::size_t n) const noexcept {
		return this->chars_left() >= n;
	}

	bool eof() const noexcept { return !this->could_read(1); }

	std::optional<char> peek_single() const noexcept {
		if (eof()) { return {}; }

		return *this->i;
	}

	std::optional<std::string_view> read(std::size_t n) noexcept {
		if (!this->could_read(n)) { return {}; }

		std::string_view str{this->i, n};
		this->i += n;

		return str;
	}

	template<std::size_t n>
	std::optional<std::array<char, n>> read() noexcept {
		if (!this->could_read(n)) { return {}; }

		std::array<char, n> str{};
		std::copy(this->i, this->i + n, str.begin());
		this->i += n;

		return str;
	}

	std::optional<char> read_single() noexcept {
		auto c{this->peek_single()};
		if (c.has_value()) { ++this->i; }

		return c;
	}

	std::string_view read_until(std::string_view set) noexcept {
		auto beg{this->i};
		while (!this->eof()
			&& !is_one_of(this->peek_single().value(), set)) {
			this->read_single();
		}

		return {beg, this->i};
	}
};
