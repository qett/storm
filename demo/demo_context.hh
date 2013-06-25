#ifndef STORM_DEMO_CONTEXT_H_
#define STORM_DEMO_CONTEXT_H_

#include <GL/glfw.h>

#include "context.hh"
#include "shader.hh"

namespace StormDemo {

class DemoContext : Rain::Context {
public:
	DemoContext();
	DemoContext(Rain::Shader **shaders);
	~DemoContext();
	void
	loop(void (*render)());

	void
	attach_shaders(Rain::Shader **shaders);
private:
	constexpr static const int dwidth = 1000, dheight = 600;
	constexpr static const int gl_major_v = 4, gl_minor_v = 2;
	constexpr static const char *const dname = "Storm Demo Context";

	void
	glfw_init();

	void
	gl_init();

	void
	create_program();

	void
	destroy_program();

	void
	display();

	static void GLFWCALL
	resize(int w, int h);
};

}

#endif
