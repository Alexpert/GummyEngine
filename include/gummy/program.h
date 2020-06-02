#ifndef GUMMY_PROGRAM_H
#define GUMMY_PROGRAM_H

struct gum_program;

struct gum_program *
gum_program_allocate(void);

void
gum_program_deallocate(struct gum_program *program);

int
gum_program_init(struct gum_program *program, const char *vertex, const char *fragment);

int
gum_program_deinit(struct gum_program *program);

/* GUMMY_PROGRAM_H */
#endif
