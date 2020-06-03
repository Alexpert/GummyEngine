#include <gummy/render.h>
#include <gummy/program.h>
#include <gummy/texture.h>
#include <gummy/buffer.h>
#include <gummy/mesh.h>

#include <unistd.h>

#include <SDL2/SDL.h>

#define WINDOW_WIDTH  500
#define WINDOW_HEIGHT 500

const char vertex_shader_source[] = "#version 330 core\n"
"in vec3 vertex_position;\n"
"in vec2 vertex_texture_coordinate;\n"
"out vec2 fragment_texture0_coordinate;\n"
"void main() {\n"
"   gl_Position = vec4(vertex_position.x, vertex_position.y, vertex_position.z, 1.0);\n"
"   fragment_texture0_coordinate = vertex_texture_coordinate;\n"
"}";

const char fragment_shader_source[] = "#version 330 core\n"
"in vec2 fragment_texture0_coordinate;\n"
"out vec4 fragment;\n"
"uniform vec4 color;\n"
"uniform sampler2D texture0;\n"
"void main() {\n"
"   fragment = texture(texture0, fragment_texture0_coordinate) * color;\n"
"}";

unsigned char texture_data[] = {
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\343\235%\343\235%\343\235%\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\261"
  "\064%\261\064%\261\064%\261\064%\261\064%\000\000\000\000\000\000\343\235%\343\235%\343\235"
  "%\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\261\064%\261\064%\261\064%\261\064%\261\064%\261"
  "\064%\261\064%\261\064%\261\064%\343\235%\343\235%\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000jk\004jk\004jk\004\343\235%\343\235%jk\004\343\235%\000\000\000jk\004jk\004jk\004\000\000\000\000"
  "\000\000\000\000\000\000\000\000jk\004\343\235%jk\004\343\235%\343\235%\343\235%jk\004\343\235"
  "%\343\235%jk\004jk\004jk\004\000\000\000\000\000\000\000\000\000\000\000\000jk\004\343\235%jk\004jk\004\343\235"
  "%\343\235%\343\235%jk\004\343\235%\343\235%\343\235%jk\004\000\000\000\000\000\000\000\000\000"
  "\000\000\000jk\004jk\004\343\235%\343\235%\343\235%\343\235%jk\004jk\004jk\004jk\004jk\004\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\343\235%\343\235%\343\235%\343\235"
  "%\343\235%\343\235%\343\235%jk\004\000\000\000\000\000\000\000\000\000\000\000\000jk\004jk\004jk\004jk\004"
  "jk\004\261\064%jk\004jk\004jk\004\261\064%jk\004\000\000\000\000\000\000\000\000\000\000\000\000jk\004jk\004jk\004"
  "jk\004jk\004jk\004jk\004\261\064%jk\004jk\004jk\004\261\064%\000\000\000\000\000\000jk\004\343\235%\343"
  "\235%jk\004jk\004jk\004jk\004jk\004jk\004\261\064%\261\064%\261\064%\261\064%\261\064%\000\000"
  "\000\000\000\000jk\004\343\235%\343\235%\343\235%\000\000\000\261\064%\261\064%jk\004\261\064"
  "%\261\064%\343\235%\261\064%\261\064%\343\235%\261\064%jk\004jk\004\000\000\000\343\235"
  "%\000\000\000jk\004\261\064%\261\064%\261\064%\261\064%\261\064%\261\064%\261\064%\261\064"
  "%\261\064%\261\064%jk\004jk\004\000\000\000\000\000\000jk\004jk\004jk\004\261\064%\261\064%\261\064"
  "%\261\064%\261\064%\261\064%\261\064%\261\064%\261\064%jk\004jk\004\000\000\000jk\004jk\004j"
  "k\004\261\064%\261\064%\261\064%\261\064%\261\064%\261\064%\261\064%\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000jk\004\000\000\000\000\000\000\261\064%\261\064%\261\064%\261\064%\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
};

unsigned long texture_width = 16, texture_height = 16;

float vertices_positions[] = {
	-0.8, -0.8, 0.0,
	 0.8, -0.8, 0.0,
	 0.8,  0.8, 0.0,
	-0.8,  0.8, 0.0,
};

float vertices_texture_coordinates[] = {
	0.0, 1.0,
	1.0, 1.0,
	1.0, 0.0,
	0.0, 0.0,
};

unsigned int indices[] = {
	0, 1, 3, 3, 1, 2
};

/*
float color[] = {
	1.0, 0.0, 1.0, 1.0
};
*/

int
main(int argc, char **argv) {
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_Window *window = SDL_CreateWindow("Epileptic Mario",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 
		SDL_WINDOW_OPENGL);
	SDL_GLContext glcontext = SDL_GL_CreateContext(window);
	int running = 1;

	struct gum_program *program = gum_program_allocate();
	struct gum_texture *texture = gum_texture_allocate();
	struct gum_buffer *vertices_positions_buffer = gum_buffer_allocate(),
		*vertices_texture_coordinates_buffer = gum_buffer_allocate();
	struct gum_mesh *mesh = gum_mesh_allocate();

	gum_program_init_vf(program, vertex_shader_source, fragment_shader_source);
	gum_texture_init_rgb(texture, texture_width, texture_height, texture_data);
	gum_buffer_init(vertices_positions_buffer, vertices_positions, sizeof(vertices_positions));
	gum_buffer_init(vertices_texture_coordinates_buffer, vertices_texture_coordinates, sizeof(vertices_texture_coordinates));
	gum_mesh_init(mesh, indices, sizeof(indices));

	gum_mesh_attribute_vec3(mesh, program, "vertex_position", vertices_positions_buffer);
	gum_mesh_attribute_vec2(mesh, program, "vertex_texture_coordinate", vertices_texture_coordinates_buffer);

	gum_render_viewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	while(running != 0) {
		unsigned int const ticks = SDL_GetTicks();
		float const greyscale = (ticks % 512) / 512.0;
		float const color[] = { greyscale, greyscale, greyscale, 1.0 };

		gum_program_uniform_vec4(program, "color", color);

		gum_render_clear();
		gum_render(mesh, program, &texture, 1);

		SDL_GL_SwapWindow(window);

		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
			case SDL_QUIT:
				running = 0;
				break;
			}
		}

		SDL_Delay(17);
	}

	gum_mesh_deinit(mesh);
	gum_buffer_deinit(vertices_texture_coordinates_buffer);
	gum_buffer_deinit(vertices_positions_buffer);
	gum_texture_deinit(texture);
	gum_program_deinit(program);

	gum_mesh_deallocate(mesh);
	gum_buffer_deallocate(vertices_texture_coordinates_buffer);
	gum_buffer_deallocate(vertices_positions_buffer);
	gum_texture_deallocate(texture);
	gum_program_deallocate(program);

	SDL_GL_DeleteContext(glcontext);  

	return 0;
}

