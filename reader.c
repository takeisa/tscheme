#include "tscheme.h"

static int get_char(FILE *stream) {
	int c = getc(stream);
	return c;
}

static void unget_char(int c, FILE *stream) {
	ungetc(c, stream);
}

static int peek_char(FILE *stream) {
	int c = get_char(stream);
	unget_char(c, stream);
	return c;
}

static bool delimiter_p(int c) {
	return isspace(c)
		|| c == '(' || c == ')'
		|| c == EOF;
}

static void skip_space(FILE *stream) {
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
static bool string_number_p(const char *s) {
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

static object *read_symbol_or_number(FILE *stream) {
	char s[MAX_TOKEN_LEN + 1];
	int i = 0;
	int c;
	while (!delimiter_p(c = get_char(stream))) {
		s[i++] = c;
		if (i >= MAX_TOKEN_LEN) {
			fatal("token length error");
		}
	}
	s[i] = '\0';
	object *obj;
	if (string_number_p(s)) {
		obj = make_number(s);
	} else {
		obj = make_symbol(s);
	}

	return obj;
}

object *read_string(FILE *stream) {
	// TODO escape
	char s[MAX_TOKEN_LEN + 1];
	int i = 0;

	while (true) {
		int c = get_char(stream);
		if (c == EOF) {
			fatal("string terminate error");
		}
		if (c == '\"') {
			break;
		}
		if (i >= MAX_TOKEN_LEN) {
			fatal("too long string");
		}
		s[i++] = c;
	}
	s[i] = '\0';

	return make_string(s);
}

object *read_list(FILE *stream) {
	skip_space(stream);
	int c = get_char(stream);
	if (c == ')') {
		return NIL;
	}
	INTERNAL_ERROR("can't read list");
}

object *read() {
	FILE *stream = stdin;
	skip_space(stream);

	int c = get_char(stream);
	if (c == '\"') {
		return read_string(stream);
	} else if (c == '(') {
		return read_list(stream);
	} else if (c == ')') {
		fatal("extra close parenthesis");
	}

	unget_char(c, stream);

	return read_symbol_or_number(stream);
}
