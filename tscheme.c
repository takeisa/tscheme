#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>
#include <stdarg.h>
#include <limits.h>

#define VERSION "0.1"
#define MAX_TOKEN_LEN 256

#define INTERNAL_ERROR(message, ...) \
	fprintf(stderr, "Internal error: %s(%d): ", __FILE__, __LINE__); \
	fprintf(stderr, message, ##__VA_ARGS__);							 \
	fprintf(stderr, "\n"); \
	abort();

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

void fatal(const char* message, ...) {
	va_list args;
	va_start(args, message);
	vfprintf(stderr, message, args);
	fprintf(stderr, "\n");
	exit(EXIT_FAILURE);
}

object *alloc_object() {
	object *obj = malloc(sizeof(object));
	if (obj == NULL) {
		fatal("out of memory error");
	}
	return obj;
}

int get_char(FILE *stream) {
	int c = getc(stream);
	return c;
}

void unget_char(int c, FILE *stream) {
	ungetc(c, stream);
}

int peek_char(FILE *stream) {
	int c = get_char(stream);
	unget_char(c, stream);
	return c;
}

bool delimiter_p(int c) {
	return isspace(c)
		|| c == '(' || c == ')'
		|| c == EOF;
}

void skip_space(FILE *stream) {
	//	printf("> skip_space\n");
	int c;
	c = get_char(stream);
	while (isspace(c)) {
		c = get_char(stream);
	}
	unget_char(c, stdin);
	//	printf("< skip_space\n");
}

// [-+]?[0-9]+
bool string_number_p(const char *s) {
	if (*s == '-' || *s == '+') {
		s++;
	}

	bool got_digit = false;
	while (isdigit(*s)) {
		got_digit = true;
		s++;
	}

	return got_digit && (*s == 0);
}

object *make_number(const char *s) {
	long int value = strtol(s, NULL, 10);
	if (value > INT_MAX) {
		fatal("overflow: %ld", value);
	}
	if (value < INT_MIN) {
		fatal("underflow: %ld", value);
	}
	object *obj = alloc_object();
	obj->type = INTEGER;
	obj->integer.value = value;
	return obj;
}

object *read_symbol_or_number(FILE *stream) {
	printf("> read_symbol_or_number\n");
	char s[MAX_TOKEN_LEN + 1];
	int i = 0;
	int c;
	while (!delimiter_p(c = get_char(stream))) {
		s[i++] = c;
		if (i >= MAX_TOKEN_LEN) {
			fatal("token length error");
		}
	}
	s[i] = 0;
	printf("s=%s\n", s);
	printf("string_number_p=%d\n", string_number_p(s));

	object *obj;
	if (string_number_p(s)) {
		obj = make_number(s);
	} else {
		INTERNAL_ERROR("not support symbol")
	}

	printf("< read_symbol_or_number\n");
	return obj;
}

object *read() {
	FILE *stream = stdin;
	skip_space(stream);

	return read_symbol_or_number(stream);
}

void print_integer(object *obj) {
	assert(obj->type == INTEGER);
	printf("%d", obj->integer.value);
}

void print(object *obj) {
	assert(obj != NULL);
	switch (obj->type) {
	case INTEGER:
		print_integer(obj);
		break;
	default:
		INTERNAL_ERROR("unsupport object type: type")
	}
}

int main(int argc, char *argv[]) {
	printf("tscheme ver" VERSION "\n");
	while (true) {
		printf("> ");
		object *obj = read();
		print(obj);
		printf("\n");
	}
	return 0;
}
