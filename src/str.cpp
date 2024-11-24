#include <str.h>
#include <com.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

namespace str {
	str::str() {
		i = 0, size = 8;
		buf = (str::C*)malloc(sizeof(str::C) * size);
	}

	str::~str() {
		free(buf);
	}

	str::str(const str& x) {
		i = x.i, size = x.size;
		buf = (str::C*)malloc(sizeof(str::C) * size);
		memcpy(buf, x.buf, sizeof(str::C) * size);
	}

	auto str::operator=(const str& x) -> str& {
		i = x.i, size = x.size;
		buf = (str::C*)malloc(sizeof(str::C) * size);
		memcpy(buf, x.buf, sizeof(str::C) * size);
		return *this;
	}

	auto str::resize(str::S x) -> void {
		ASSERT(x > size);
		size = x;
		buf = (str::C*)realloc(buf, sizeof(str::C) * size);
	}

	auto str::push(str::C x) -> void {
		buf[i++] = x;
		if (i > size) resize(size * 2);
	}

	auto str::append(str x) -> void {
		for (size_t n = 0; n < x.i; n++) {
			push(x.buf[n]);
		}
	}

	auto str::to_c_str() -> char* {
		auto s = (char*)malloc(sizeof(char) * (i + 2));
		memcpy(s, buf, sizeof(char) * i);
		s[i + 1] = '\0';
		return s;
	}

	auto fmt(uint8_t x) -> str {
		auto r = str();

		char *s;
		auto n = asprintf(&s, "%d", x);
		for (int i = 0; i < n; i++) r.push(s[i]);
		free(s);

		return r;
	}
}
