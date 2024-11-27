#include <vec.h>
#include <functional>
#include <iostream>
#include <stdint.h>

using namespace std;

template<typename T>
struct test_t {
	using F = function<T(void)>;
	string name;
	F fun;
	T exp;

	test_t(string n, T e, F f) {
		name = n;
		fun = f;
		exp = e;
	}

	inline bool test() {
		return fun() == exp;
	}
};

template<typename T, const size_t S>
inline static Vec<T> array_to_vec(T x[S]) {
	return Vec<T>(x, S, S);
}

using ByteVecTest = test_t<Vec<uint8_t>>;
ByteVecTest byte_tests[] = {
	ByteVecTest(
		"3ints",
		array_to_vec<uint8_t, 3>((uint8_t[]){1, 2, 3}),
		[]() {
			auto v = Vec<uint8_t>();
			for (uint8_t i = 1; i < 4; i++) v.push(i);
			return v;
		}
	)
};

using SizeVecTest = test_t<Vec<size_t>>;
SizeVecTest size_tests[] = {
       SizeVecTest(
	       "many at",
		array_to_vec<size_t, 3>((size_t[]){5, 2, 4}),
		[]() {
			auto v = Vec<size_t>();
			for (size_t i = 0; i < 10; i++) v.push(i);

			auto is = Vec<size_t>();
			is.push(5);
			is.push(2);
			is.push(4);

			return v.at(is);
		}
	),
	SizeVecTest(
		"iota",
		array_to_vec<size_t, 5>((size_t[]){0, 1, 2, 3, 4}),
		[]() {
			return Vec<size_t>::iota(5);
		}
	),
	SizeVecTest(
		"VEC macro",
		array_to_vec<size_t, 3>((size_t[]){0, 1, 2}),
		[]() {
			return VEC(size_t, 0, 1, 2);
		}
	),
	SizeVecTest(
		"bool at",
		VEC(size_t, 0, 2, 4, 6),
		[]() {
			#define T true
			#define F false
			return Vec<size_t>::iota(7)
				.at(VEC(bool, T, F, T, F, T, F, T));
			#undef T
			#undef F
		}
	),
	SizeVecTest(
		"each",
		VEC(size_t, 1, 2, 3),
		[]() {
			return Vec<size_t>::iota(3)
				.each<size_t>([](size_t x) -> size_t {
					return x + 1;
				});
		}
	),
	SizeVecTest(
		"add",
		VEC(size_t, 1, 2, 3),
		[]() {
			return Vec<size_t>::iota(3) + 1;
		}
	),
	SizeVecTest(
		"math",
		VEC(size_t, 2, 4, 6),
		[]() {
			return (Vec<size_t>::iota(3) + 1) * 2;
		}
	),
	SizeVecTest(
		"chain",
		VEC(size_t, 2, 3, 4),
		[]() {
			return (Vec<size_t>::iota(3) + 1)
				.each<size_t>([](size_t x) -> size_t {
					return x + 1;
				});
		}
	),
	SizeVecTest(
		"big vec",
		Vec<size_t>::iota(1000000),
		[]() {
			auto v = Vec<size_t>();
			for (size_t i = 0; i < 1000000; i++) v.push(i);
			return v;
		}
	),
	SizeVecTest(
		"sum scan",
		VEC(size_t, 0, 1, 3, 6),
		[]() {
			return Vec<size_t>::iota(4).scan<size_t>([](size_t x, size_t y) { return x + y; });
		}
	),
};

int main() {
	#define TEST(T) { \
		for (auto& x : T) { \
			auto r = x.test(); \
			cout << x.name << ": "; \
			cout << (r ? "success" : "failed") << endl; \
			if (!r) { \
				auto lhs = x.exp.to_str().to_c_str(); \
				cout << "want: " << lhs << endl; \
				free(lhs); \
				auto rhs = x.fun().to_str().to_c_str(); \
				cout << "gave: " << rhs << endl; \
				free(rhs); \
			} \
		} \
	}

	TEST(byte_tests);
	TEST(size_tests);

	return 0;
}
