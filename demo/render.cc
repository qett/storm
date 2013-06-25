#include <iostream>

#include <GL/glew.h>
#include <GL/gl.h>

#include "vertex_buffer.hh"

namespace StormDemo {

GLuint vbo_id, vao_id, cb_id;

Rain::VertexBuffer *vertices, *colors;

void
create_vbos()
{
	GLfloat vertex_data[] = {
		-0.8f,  0.8f, 0.0f, 1.0f,
		 0.8f,  0.8f, 0.0f, 1.0f,
		-0.8f, -0.8f, 0.0f, 1.0f,
		 0.8f, -0.8f, 0.0f, 1.0f
	};

	GLfloat color_data[] = {
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f
	};

	glGenVertexArrays(1, &vao_id);
	glBindVertexArray(vao_id);

	vertices = new Rain::VertexBuffer(GL_ARRAY_BUFFER,
			sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	colors = new Rain::VertexBuffer(GL_ARRAY_BUFFER,
			sizeof(color_data), color_data, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	if (GL_NO_ERROR != glGetError())
		std::cout << "vbo error\n";
}

void
destroy_vbos()
{
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	delete vertices;
	delete colors;

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &vao_id);
}

void
render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

}
