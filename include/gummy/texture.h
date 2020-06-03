#ifndef GUMMY_TEXTURE_H
#define GUMMY_TEXTURE_H

struct gum_texture;

struct gum_texture *
gum_texture_allocate(void);

void
gum_texture_deallocate(struct gum_texture *texture);

int
gum_texture_init_rgb(struct gum_texture *texture, unsigned long width, unsigned long height, const void *data);

int
gum_texture_deinit(struct gum_texture *texture);

/* GUMMY_TEXTURE_H */
#endif
