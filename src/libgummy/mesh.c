#include "gummy_internal.h"

#include <stdlib.h>

struct gum_mesh *
gum_mesh_allocate(void) {
	return malloc(sizeof(struct gum_mesh));
}

void
gum_mesh_deallocate(struct gum_mesh *mesh) {
	free(mesh);
}

int
gum_mesh_init(struct gum_mesh *mesh, struct gum_program *program,
	float *vertices, size_t vertices_count,
	unsigned int *indices, size_t indices_count) {

	mesh->glcount = indices_count;

	glGenVertexArrays(1, &mesh->glvao);
	glGenBuffers(1, &mesh->glvbo);
	glGenBuffers(1, &mesh->glebo);

	glBindVertexArray(mesh->glvao);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->glebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_count * sizeof(*indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->glvbo);
	glBufferData(GL_ARRAY_BUFFER, vertices_count * sizeof(*vertices), vertices, GL_STATIC_DRAW);

	GLuint const vertex_position_index = glGetAttribLocation(program->glprogram, "vertex_position");
	GLint const vertex_position_size = (GLint)(vertices_count / indices_count);
	glVertexAttribPointer(vertex_position_index, vertex_position_size,
		GL_FLOAT, GL_FALSE, vertex_position_size * sizeof(*vertices), 0);
	glEnableVertexAttribArray(vertex_position_index);

	glBindVertexArray(0); 

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); 
	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	return 0;
}

int
gum_mesh_deinit(struct gum_mesh *mesh) {

	glDeleteVertexArrays(1, &mesh->glvao);
	glDeleteBuffers(1, &mesh->glvbo);
	glDeleteBuffers(1, &mesh->glebo);

	return 0;
}

