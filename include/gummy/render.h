#ifndef GUMMY_RENDER_H
#define GUMMY_RENDER_H

#include <gummy/program.h>
#include <gummy/texture.h>
#include <gummy/mesh.h>

void
gum_render_viewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height);

void
gum_render_clear(void);

void
gum_render(struct gum_mesh *mesh, struct gum_program *program, struct gum_texture **textures, unsigned int count);

/* GUMMY_RENDER_H */
#endif
