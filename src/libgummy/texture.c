#include "gummy_internal.h"

#include <stdlib.h>

struct gum_texture *
gum_texture_allocate(void) {
	return malloc(sizeof(struct gum_texture));
}

void
gum_texture_deallocate(struct gum_texture *texture) {
	free(texture);
}

int
gum_texture_init_rgb(struct gum_texture *texture, unsigned long width, unsigned long height, const void *data) {

	glGenTextures(1, &texture->texture);
	glBindTexture(GL_TEXTURE_2D, texture->texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	return 0;
}

int
gum_texture_deinit(struct gum_texture *texture) {

	glDeleteTextures(1, &texture->texture);

	return 0;
}

