#include "tscheme.h"

void fatal(const char* message, ...) {
	va_list args;
	va_start(args, message);
	vfprintf(stderr, message, args);
	fprintf(stderr, "\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
	init_objects();

	printf("tscheme ver" VERSION "\n");
	while (true) {
		printf("> ");
		object *obj = read();
		print(obj);
		printf("\n");
	}
	return 0;
}
