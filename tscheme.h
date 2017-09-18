#ifndef INCLUDED_TSCHEME_H
#define INCLUDED_TSCHEME_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>
#include <stdarg.h>
#include <limits.h>

#define MAX_TOKEN_LEN 256

typedef enum object_type {
	INTEGER
} object_type;

typedef struct object {
	object_type type;
	union {
		struct integer {
			int value;
		} integer;
	};
} object;

#define INTERNAL_ERROR(message, ...) \
	fprintf(stderr, "Internal error: %s(%d): ", __FILE__, __LINE__); \
	fprintf(stderr, message, ##__VA_ARGS__); \
	fprintf(stderr, "\n"); \
	abort();

void fatal(const char* message, ...);

object *read();

object *make_number(const char* s);

#endif
