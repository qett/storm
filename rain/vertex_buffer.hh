#ifndef STORM_RAIN_VERTEXBUFFER_H_
#define STORM_RAIN_VERTEXBUFFER_H_

#include <memory>

#include <GL/gl.h>

namespace Rain {

class VertexBuffer {
public:
	VertexBuffer(GLenum type, GLsizeiptr size,
		     const GLvoid *data, GLenum usage);
	~VertexBuffer();
private:
	class Impl;
	std::unique_ptr<Impl> pimpl;
};

}

#endif
