#ifndef INCLUDED_TSCHEME_H
#define INCLUDED_TSCHEME_H

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <limits.h>

#define VERSION "0.1"
#define MAX_TOKEN_LEN 256

typedef enum object_type {
	INTEGER,
	SYMBOL,
	STRING
} object_type;

typedef struct object {
	object_type type;
	union {
		struct integer {
			int value;
		} integer;
		struct symbol {
			const char *name;
		} symbol;
		struct string {
			const char *value;
		} string;
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
object *make_symbol(const char* s);
object *make_string(const char* s);

#endif
