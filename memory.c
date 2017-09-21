#include "tscheme.h"

object *alloc_object() {
	object *obj = malloc(sizeof(object));
	if (obj == NULL) {
		fatal("out of memory error");
	}
	return obj;
}
