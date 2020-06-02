#ifndef GUMMY_INTERNAL_H
#define GUMMY_INTERNAL_H

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glcorearb.h>

#include <gummy/program.h>
#include <gummy/buffer.h>
#include <gummy/mesh.h>

struct gum_program {
	GLuint program;
};

struct gum_buffer {
	GLuint buffer;
};

struct gum_mesh {
	GLsizei count;
	GLuint vao;
	GLuint ebo;
};

/* GUMMY_INTERNAL_H */
#endif
