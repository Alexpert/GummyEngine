#include "gummy_internal.h"

#include <stdio.h>
#include <stdlib.h>

#define GUM_PROGRAM_SHADER_INFO_LOG_SIZE 512

static int
gum_program_shader_init(GLuint *shaderp, GLenum type, const char *source) {
	GLuint shader = glCreateShader(type);
	GLint status;

	*shaderp = shader;

	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if(status == 0) {
		GLchar info[GUM_PROGRAM_SHADER_INFO_LOG_SIZE];

		glGetShaderInfoLog(shader, sizeof(info), NULL, info);

		fprintf(stderr, "Unable to compile shader: %s", info);
		return -1;
	}

	return 0;
}

static int
gum_program_shader_deinit(GLuint *shaderp) {
	glDeleteShader(*shaderp);

	return 0;
}

struct gum_program *
gum_program_allocate(void) {
	return malloc(sizeof(struct gum_program));
}

void
gum_program_deallocate(struct gum_program *program) {
	free(program);
}

int
gum_program_init_vf(struct gum_program *program, const char *vertex, const char *fragment) {
	GLuint glvertex, glfragment;
	int status = 0;

	program->program = glCreateProgram();
	status |= gum_program_shader_init(&glvertex, GL_VERTEX_SHADER, vertex);
	status |= gum_program_shader_init(&glfragment, GL_FRAGMENT_SHADER, fragment);
	glAttachShader(program->program, glvertex);
	glAttachShader(program->program, glfragment);
	glLinkProgram(program->program);

	gum_program_shader_deinit(&glvertex);
	gum_program_shader_deinit(&glfragment);

	return status;
}

int
gum_program_deinit(struct gum_program *program) {
	glDeleteProgram(program->program);

	return 0;
}

