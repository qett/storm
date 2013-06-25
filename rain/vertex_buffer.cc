#include <GL/glew.h>
#include <GL/gl.h>

#include "glexception.hh"
#include "vertex_buffer.hh"

namespace Rain {

class VertexBuffer::Impl {
public:
	GLenum type;
	GLsizeiptr size;
	const GLvoid *data;
	GLenum usage;
	bool is_bound;
	GLenum id;

	void
	create_vbo();

	void
	destroy_vbo();
};

void
VertexBuffer::Impl::create_vbo()
{
	glGenBuffers(1, &id);

	auto e = glGetError();
	if (GL_NO_ERROR != e)
		throw GLException(e);

	glBindBuffer(type, id);

	e = glGetError();
	if (GL_NO_ERROR != e)
		throw GLException(e);

	glBufferData(type, size, data, usage);

	e = glGetError();
	if (GL_NO_ERROR != e)
		throw GLException(e);
}

void
VertexBuffer::Impl::destroy_vbo()
{
	glDeleteBuffers(1, &id);

	auto e = glGetError();
	if (GL_NO_ERROR != e)
		throw GLException(e);
}

VertexBuffer::VertexBuffer(GLenum type, GLsizeiptr size,
			   const GLvoid *data, GLenum usage) :
pimpl {new Impl {type, size, data, usage, false}}
{
	pimpl->create_vbo();
}

VertexBuffer::~VertexBuffer()
{
	pimpl->destroy_vbo();
}

}
