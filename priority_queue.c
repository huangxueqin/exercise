#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct priority_queue {
	size_t capacity;
	size_t size;
	void *data;
	int (*compar)(void *, void *);
}
