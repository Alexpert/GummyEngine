#ifndef GUMMY_MESH_H
#define GUMMY_MESH_H

#include <stdlib.h>

#include <gummy/program.h>

struct gum_mesh;

struct gum_mesh *
gum_mesh_allocate(void);

void
gum_mesh_deallocate(struct gum_mesh *mesh);

int
gum_mesh_init(struct gum_mesh *mesh, struct gum_program *program,
	float *vertices, size_t vertices_count,
	unsigned int *indices, size_t indices_count);

int
gum_mesh_deinit(struct gum_mesh *mesh);

/* GUMMY_MESH_H */
#endif
