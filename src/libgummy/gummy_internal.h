#ifndef GUMMY_INTERNAL_H
#define GUMMY_INTERNAL_H

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glcorearb.h>

#include <gummy/program.h>
#include <gummy/mesh.h>

struct gum_program {
	GLuint glprogram;
};

struct gum_mesh {
	GLsizei glcount;
	GLuint glvao;
	GLuint glvbo;
	GLuint glebo;
};

/* GUMMY_INTERNAL_H */
#endif
