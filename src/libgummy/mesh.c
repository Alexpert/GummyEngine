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
gum_mesh_init(struct gum_mesh *mesh, unsigned int *indices, unsigned long count) {

	mesh->count = count;

	glGenVertexArrays(1, &mesh->vao);
	glGenBuffers(1, &mesh->ebo);

	glBindVertexArray(mesh->vao);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(*indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0); 

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); 

	return 0;
}

int
gum_mesh_deinit(struct gum_mesh *mesh) {

	glDeleteVertexArrays(1, &mesh->vao);
	glDeleteBuffers(1, &mesh->ebo);

	return 0;
}

int
gum_mesh_attribute_vec3(struct gum_mesh *mesh, struct gum_program *program, const char *attribute, struct gum_buffer *buffer) {
	GLuint const index = glGetAttribLocation(program->program, attribute);

	glBindVertexArray(mesh->vao);
	glBindBuffer(GL_ARRAY_BUFFER, buffer->buffer);

	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(index);

	glBindVertexArray(0); 
	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	return 0;
}

