#include <GL/glew.h>
#include <GL/gl.h>

#include "glexception.hh"
#include "shader.hh"
#include "program.hh"

namespace Rain {

class Program::Impl {
public:
	GLuint program;
	bool in_use;
	Shader **shaders;

	void
	create_program(Shader **shaders);

	void
	destroy_program();

	void
	use_program();

	void
	unuse_program();
};


void
Program::Impl::create_program(Shader **shaders)
{
	if (nullptr == shaders)
		return;

	this->shaders = shaders;

	program = glCreateProgram();

	auto e = glGetError();
	if (GL_NO_ERROR != e)
		throw GLException(e);

	for (Shader **i = shaders; nullptr != *i; i++) {
		glAttachShader(program, (*i)->get_id());

		e = glGetError();
		if (GL_NO_ERROR != e)
			throw GLException(e);
	}

	glLinkProgram(program);
	e = glGetError();
	if (GL_NO_ERROR != e)
		throw GLException(e);
}

void
Program::Impl::destroy_program()
{
	unuse_program();

	if (nullptr != shaders) {
		for (Shader **i = shaders; *i != nullptr; i++) {
			glDetachShader(program, (*i)->get_id());

			auto e = glGetError();
			if (GL_NO_ERROR != e)
				throw GLException(e);
		}
	}

	glDeleteProgram(program);

	auto e = glGetError();
	if (GL_NO_ERROR != e)
		throw GLException(e);
}

void
Program::Impl::use_program()
{
	if (in_use)
		return;

	glUseProgram(program);

	auto e = glGetError();
	if (GL_NO_ERROR != e)
		throw GLException(e);

	in_use = true;
}

void
Program::Impl::unuse_program()
{
	if (!in_use)
		return;

	glUseProgram(0);

	auto e = glGetError();
	if (GL_NO_ERROR != e)
		throw GLException(e);

	in_use = false;
}

Program::Program(Shader **shaders) : pimpl {new Impl {0, false}}
{
	pimpl->create_program(shaders);
}

Program::~Program()
{
	pimpl->unuse_program();
	pimpl->destroy_program();
}

void
Program::use()
{
	pimpl->use_program();
}

void
Program::unuse()
{
	pimpl->unuse_program();
}

}
