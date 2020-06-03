#include <gummy/render.h>
#include <gummy/program.h>
#include <gummy/buffer.h>
#include <gummy/mesh.h>

#include <unistd.h>

#include <SDL2/SDL.h>

#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480

const char vertex_shader_source[] = "#version 330 core\n"
"in vec3 vertex_position;\n"
"void main() {\n"
"   gl_Position = vec4(vertex_position.x, vertex_position.y, vertex_position.z, 1.0);\n"
"}";

const char fragment_shader_source[] = "#version 330 core\n"
"out vec4 fragment;\n"
"uniform vec4 color;\n"
"void main() {\n"
"   fragment = color;\n"
"}";

float vertices_positions[] = {
	-0.5, -0.5, 0.0,
	 0.5, -0.5, 0.0,
	 0.0,  0.5, 0.0
};

unsigned int indices[] = {
	0, 1, 2
};

float color[] = {
	1.0, 0.0, 1.0, 1.0
};

int
main(int argc, char **argv) {
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_Window *window = SDL_CreateWindow("Gummy Triangle",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 
		SDL_WINDOW_OPENGL);
	SDL_GLContext glcontext = SDL_GL_CreateContext(window);
	int running = 1;

	struct gum_program *program = gum_program_allocate();
	struct gum_buffer *vertices_positions_buffer = gum_buffer_allocate();
	struct gum_mesh *mesh = gum_mesh_allocate();

	gum_program_init_vf(program, vertex_shader_source, fragment_shader_source);
	gum_buffer_init(vertices_positions_buffer, vertices_positions, sizeof(vertices_positions));
	gum_mesh_init(mesh, indices, sizeof(indices));

	gum_program_uniform_vec4(program, "color", color);

	gum_mesh_attribute_vec3(mesh, program, "vertex_position", vertices_positions_buffer);

	gum_render_viewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	while(running != 0) {
		SDL_Event event;
		SDL_Delay(17);

		gum_render_clear();
		gum_render(mesh, program);

		SDL_GL_SwapWindow(window);

		while(SDL_PollEvent(&event)) {
			switch(event.type) {
			case SDL_QUIT:
				running = 0;
				break;
			}
		}
	}

	gum_mesh_deinit(mesh);
	gum_buffer_deinit(vertices_positions_buffer);
	gum_program_deinit(program);

	gum_mesh_deallocate(mesh);
	gum_buffer_deallocate(vertices_positions_buffer);
	gum_program_deallocate(program);

	SDL_GL_DeleteContext(glcontext);  

	return 0;
}

