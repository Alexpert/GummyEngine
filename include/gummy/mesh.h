#ifndef GUMMY_MESH_H
#define GUMMY_MESH_H

#include <gummy/program.h>
#include <gummy/buffer.h>

struct gum_mesh;

struct gum_mesh *
gum_mesh_allocate(void);

void
gum_mesh_deallocate(struct gum_mesh *mesh);

int
gum_mesh_init(struct gum_mesh *mesh, unsigned int *indices, unsigned long count);

int
gum_mesh_deinit(struct gum_mesh *mesh);

int
gum_mesh_attribute_vec3(struct gum_mesh *mesh, struct gum_program *program, const char *attribute, struct gum_buffer *buffer);

/* GUMMY_MESH_H */
#endif
