#include <com.h>

#include <stdlib.h>
#include <stdio.h>

void fatal(const char *msg) {
	fprintf(stderr, "fatal error: %s\n", msg);
	exit(-1);
}
