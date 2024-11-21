#ifndef __STL_INC_COM_H__
#define __STL_INC_COM_H__

void fatal(const char *msg);

/** assert that a predicate p is true */
#define ASSERT(p) { if (!(p)) fatal("assertation "#p " failed"); }

#endif
