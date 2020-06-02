#ifndef GUMMY_RENDER_H
#define GUMMY_RENDER_H

#include <gummy/program.h>
#include <gummy/mesh.h>

void
gum_render_viewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height);

void
gum_render_clear(void);

void
gum_render_program(struct gum_program *program);

void
gum_render_mesh(struct gum_mesh *mesh);

/* GUMMY_RENDER_H */
#endif
