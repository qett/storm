#include <cstdlib>
#include <iostream>

#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/glfw.h>

#include "shader.hh"
#include "glexception.hh"
#include "demo_context.hh"

namespace StormDemo {

DemoContext::DemoContext()
{
	width = dwidth;
	height = dheight;
	name = dname;

	glfw_init();
	gl_init();
}

DemoContext::~DemoContext()
{
	glfwCloseWindow();
	glfwTerminate();
}

void
DemoContext::glfw_init()
{
	if (GL_TRUE != glfwInit())
		throw Rain::GLFWException("glfwInit() error\n");

	if (GL_TRUE != glfwOpenWindow(width, height, 8, 8, 
				8, 8, 16, 0, GLFW_WINDOW))
		throw Rain::GLFWException("glfwOpenWindow() error\n");

	glfwSetWindowTitle(name);
	glfwSetWindowSizeCallback(resize);
}

void
DemoContext::gl_init()
{
	auto e = glewInit();

	if (GLEW_OK != e)
		throw Rain::GLEWException(e);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	std::cout << glGetString(GL_VERSION) << std::endl;

	resize(width, height);

}

void
DemoContext::resize(int w, int h)
{
	glViewport(0, 0, w, h);
}

void
DemoContext::loop(void (*render)())
{
	double last_time, cur_time, fps = 0.0;

	last_time = glfwGetTime();

	while (!glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED)) {
		render();
		glfwSwapBuffers();

		cur_time = glfwGetTime();

		if (cur_time - last_time < 1.0) {
			fps += 1.0;
		} else {
			last_time = cur_time;
			std::cout << fps << " FPS\n";
			fps = 0.0;
		}
	}
}

}
