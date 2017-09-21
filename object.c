#include "tscheme.h"

object *NIL;

object *make_null() {
	object *obj = alloc_object();
	obj->type = T_NULL;
	return obj;
}

object *make_number(const char *s) {
	long int value = strtol(s, NULL, 10/*base*/);
	if (value > INT_MAX) {
		fatal("overflow: %s", s);
	}
	if (value < INT_MIN) {
		fatal("underflow: %s", s);
	}
	object *obj = alloc_object();
	obj->type = T_INTEGER;
	obj->integer.value = value;
	return obj;
}

object *make_symbol(const char *s) {
	object *obj = alloc_object();
	obj->type = T_SYMBOL;
	obj->symbol.name = strdup(s);
	return obj;
}

object *make_string(const char *s) {
	object *obj = alloc_object();
	obj->type = T_STRING;
	obj->string.value = strdup(s);
	return obj;
}

void print_integer(object *obj) {
	assert(obj->type == T_INTEGER);
	printf("%d", obj->integer.value);
}

void print_symbol(object *obj) {
	assert(obj->type == T_SYMBOL);
	printf("%s", obj->symbol.name);
}

void print_string(object *obj) {
	assert(obj->type == T_STRING);
	printf("\"%s\"", obj->string.value);
}

void print_null(object *obj) {
	assert(obj->type == T_NULL);
	printf("()");
}

// TODO use stream?
void print(object *obj) {
	assert(obj != NULL);
	switch (obj->type) {
	case T_INTEGER:
		print_integer(obj);
		break;
	case T_SYMBOL:
		print_symbol(obj);
		break;
	case T_STRING:
		print_string(obj);
		break;
	case T_NULL:
		print_null(obj);
		break;
	default:
		INTERNAL_ERROR("unsupport object type: type=%d", obj->type)
	}
}

void init_objects() {
	NIL = make_null();
}
