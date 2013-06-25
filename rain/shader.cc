#include <fstream>
#include <iostream>

#include <GL/glew.h>
#include <GL/gl.h>

#include "glexception.hh"
#include "shader.hh"

namespace Rain {

class Shader::Impl {
public:
	GLenum type;
	char *source;
	GLuint id;
	
	~Impl();

	void
	load_source(const char *fn);

	void
	create_shader();

	void
	check_glsl_errors();
};

Shader::Impl::~Impl()
{
	glDeleteShader(id);
	delete []source;
}

Shader::~Shader()
{
}

void
Shader::Impl::load_source(const char *fn)
{
	std::ifstream f(fn, std::ios::in | std::ios::ate);
	
	auto length = f.tellg();
	f.seekg(0, std::ios::beg);
	
	source = new char[(unsigned int)length + 1];
	f.read(source, length);
	source[length] = 0;

	f.close();
}

void
Shader::Impl::check_glsl_errors()
{
	GLint compiled;

	glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);

	if (GL_FALSE == compiled) {
		GLint length = 0;

		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		
		if (length) {
			GLchar *log = new char[length];

			glGetShaderInfoLog(id, length, NULL, log);

			log[length - 1] = 0;

			throw GLSLException(log);

			delete []log;
		}
	}
}

void
Shader::Impl::create_shader(void)
{
	id = glCreateShader(type);
	glShaderSource(id, 1, ((const char**)(&source)), nullptr);
	glCompileShader(id);

	check_glsl_errors();

	auto e = glGetError();
	if (GL_NO_ERROR != e)
		throw GLException(e);
}

Shader::Shader(const char *fn, GLenum type) : pimpl {new Impl {type, nullptr}}
{
	pimpl->load_source(fn);
	pimpl->create_shader();
}

Shader::Shader(Shader&& other)
{
	pimpl = std::move(other.pimpl);
}

unsigned int
Shader::get_id()
{
	return pimpl->id;
}

};
