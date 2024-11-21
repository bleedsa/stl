#ifndef __STL_INC_STR_H__
#define __STL_INC_STR_H__

#include <stdint.h>
#include <stddef.h>

namespace str {
	struct str {
		using C = uint8_t;
		using S = size_t;

		C *buf;
		S size;
		S i;

		str();
		~str();
		str(const str& x);
		str& operator=(const str& x);

		void resize(S x);
		void push(C x);
		void append(str x);
		char *to_c_str();
	};

	str fmt(uint8_t x);
}

#endif
