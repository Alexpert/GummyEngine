#ifndef GUMMY_BUFFER_H
#define GUMMY_BUFFER_H

struct gum_buffer;

struct gum_buffer *
gum_buffer_allocate(void);

void
gum_buffer_deallocate(struct gum_buffer *buffer);

int
gum_buffer_init(struct gum_buffer *buffer, const void *elements, unsigned long size);

int
gum_buffer_deinit(struct gum_buffer *buffer);

/* GUMMY_BUFFER_H */
#endif
