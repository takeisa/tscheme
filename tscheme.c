#include "tscheme.h"

#define VERSION "0.1"

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

object *make_number(const char *s) {
	long int value = strtol(s, NULL, 10);
	if (value > INT_MAX) {
		fatal("overflow: %s", s);
	}
	if (value < INT_MIN) {
		fatal("underflow: %s", s);
	}
	object *obj = alloc_object();
	obj->type = INTEGER;
	obj->integer.value = value;
	return obj;
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
