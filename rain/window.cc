#include <GL/gl.h>
#include <GL/glew.h>

#include "window.hh"
#include "shader.hh"

class Window::impl {
public:
	int width, height;
	GLuint program;
	Shader *shaders;
	
	impl(int w, int h, Shader *s);
	~impl();
};

Window::impl::impl(int w. int h, Shader *s)
{
	width = w;
	height = h;

	if (nullptr == s)
		return;

	program = glCreateProgram();

	for (Shader *i = s ; i++; i != nullptr)
		glAttachShader(program, i->get_id();

	glLinkProgram(program);
	glUseProgram(program);
}





