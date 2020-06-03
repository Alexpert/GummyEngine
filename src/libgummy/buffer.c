#include "gummy_internal.h"

#include <stdlib.h>

struct gum_buffer *
gum_buffer_allocate(void) {
	return malloc(sizeof(struct gum_buffer));
}

void
gum_buffer_deallocate(struct gum_buffer *buffer) {
	free(buffer);
}

int
gum_buffer_init(struct gum_buffer *buffer, const void *elements, unsigned long size) {

	glGenBuffers(1, &buffer->buffer);

	glBindBuffer(GL_ARRAY_BUFFER, buffer->buffer);
	glBufferData(GL_ARRAY_BUFFER, size, elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return 0;
}

int
gum_buffer_deinit(struct gum_buffer *buffer) {

	glDeleteBuffers(1, &buffer->buffer);

	return 0;
}

