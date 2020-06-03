#include "gummy_internal.h"

void
gum_render_viewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	glViewport(x, y, width, height);
}

void
gum_render_clear(void) {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
}

void
gum_render(struct gum_mesh *mesh, struct gum_program *program) {
	glUseProgram(program->program);
	glBindVertexArray(mesh->vao);

	glDrawElements(GL_TRIANGLES, mesh->count, GL_UNSIGNED_INT, 0);

	glUseProgram(0);
	glBindVertexArray(0);
}

