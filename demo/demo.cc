#include <iostream>
#include <exception>

#include <GL/glew.h>
#include <GL/gl.h>

#include "shader.hh"
#include "program.hh"

#include "demo_context.hh"
#include "render.hh"

int
main(int argc, char *argv[])
{
	StormDemo::DemoContext *c;
	Rain::Program *program;

	try {
		c = new StormDemo::DemoContext();

		Rain::Shader *shaders[] = {
			new Rain::Shader("shaders/1/vertex.glsl", 
							GL_VERTEX_SHADER),
			new Rain::Shader("shaders/1/fragment.glsl", 
							GL_FRAGMENT_SHADER),
			nullptr
		};		

		StormDemo::create_vbos();

		program = new Rain::Program(shaders);

		program->use();

		c->loop(StormDemo::render);
	
		delete shaders[0];
		delete shaders[1];

	} catch (std::exception& e) {
		std::cerr << e.what();
	}

	delete program;
	StormDemo::destroy_vbos();
	delete c;

	return 0;
}
