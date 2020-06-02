#include "gummy_internal.h"

void
gum_render_viewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	glViewport(x, y, width, height);
}

void
gum_render_program(struct gum_program *program) {
	glUseProgram(program->glprogram);
}

void
gum_render_clear(void) {
	glClearColor(0.2, 0.3, 0.3, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void
gum_render_mesh(struct gum_mesh *mesh) {
	glBindVertexArray(mesh->glvao);
	glDrawElements(GL_TRIANGLES, mesh->glcount, GL_UNSIGNED_INT, 0);
}

