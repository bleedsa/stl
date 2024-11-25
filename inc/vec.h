#ifndef __STL_INC_VEC_H__
#define __STL_INC_VEC_H__

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "com.h"
#include "str.h"

template<typename T>
struct Vec {
	T *buf;
	size_t size;
	size_t i;

	Vec() {
		i = 0;
		size = 8;
		buf = (T*)malloc(sizeof(T) * size);
	}

	Vec(T *b, size_t s, size_t i) {
		buf = (T*)malloc(sizeof(T) * s);
		memcpy(buf, b, sizeof(T) * s);
		size = s;
		this->i = i;
	}

	~Vec() {
		free(buf);
	}

	Vec(const Vec& x) {
		i = x.i, size = x.size;
		buf = (T*)malloc(sizeof(T) * size);
		memcpy(buf, x.buf, sizeof(T) * size);
	}

	Vec& operator=(const Vec& x) {
		i = x.i, size = x.size;
		buf = (T*)malloc(sizeof(T) * size);
		memcpy(buf, x.buf, sizeof(T) * size);
		return *this;
	}

	void resize(size_t s) {
		ASSERT(s > size);
		size = s;
		buf = (T*)realloc(buf, sizeof(T) * size);
	}

	void push(T x) {
		buf[i++] = x;
		if (i > size) resize(size * 2);
	}

	str::str to_str() {
		auto s = str::str();
		s.push('[');

		for (size_t n = 0; n < i; n++) {
			s.append(str::fmt(buf[n]));
			if (n != i - 1) s.push(',');
		}

		s.push(']');
		return s;
	}

	inline size_t len() {
		return i;
	}

	inline T at(size_t idx) {
		return buf[idx];
	}

	Vec<T> at(Vec<size_t> idx) {
		auto r = Vec<T>();
		for (size_t n = 0; n < idx.len(); n++) r.push(at(idx.at(n)));
		return r;
	}

	Vec<T> at(Vec<bool> idx) {
		ASSERT(idx.len() == len());
		auto r = Vec<T>();
		for (size_t n = 0; n < len(); n++) {
			if (idx.at(n)) r.push(at(n));
		}
		return r;
	}

	inline static Vec<T> iota(T n) {
		auto r = Vec<T>();
		for (T i = 0; i < n; i++) r.push(i);
		return r;
	}

	template<typename X>
	Vec<X> each(X (^f)(T)) {
		auto r = Vec<X>();
		for (size_t n = 0; n < len(); n++) r.push(f(at(n)));
		return r;
	}

	Vec<T> operator+(T x) {
		auto r = Vec<T>();
		for (size_t n = 0; n < len(); n++) r.push(x + at(n));
		return r;
	}
};

template<typename T>
bool operator==(const Vec<T>& x, const Vec<T>& y) {
	if (x.i == y.i) {
		for (size_t i = 0; i < x.i; i++) {
			if (x.buf[i] != y.buf[i]) return false;
		}
		return true;
	}
	return false;
}

namespace detail {
    template<typename ...Args>
    constexpr std::size_t va_count(Args&&...) { return sizeof...(Args); }
}
#define ARGC(...) detail::va_count(__VA_ARGS__)

/** make a vector from the arguments */
#define VEC(t, ...) (Vec<t>((t[]){ __VA_ARGS__ }, ARGC(__VA_ARGS__), ARGC(__VA_ARGS__)))

#endif
