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

/* -------------------- */
/* object */

typedef enum object_type {
	T_INTEGER,
	T_SYMBOL,
	T_STRING,
	T_NULL
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

object *make_number(const char* s);
object *make_symbol(const char* s);
object *make_string(const char* s);

void print(object *obj);

void init_objects();

extern object *NIL;

/* -------------------- */
/* memory */

object *alloc_object();


/* -------------------- */
/* reader */

object *read();

/* -------------------- */
/* utility */

#define INTERNAL_ERROR(message, ...) \
	fprintf(stderr, "Internal error: %s:%d: ", __FILE__, __LINE__); \
	fprintf(stderr, message, ##__VA_ARGS__); \
	fprintf(stderr, "\n"); \
	abort();

void fatal(const char* message, ...);

#endif
