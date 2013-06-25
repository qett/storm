#ifndef STORM_RAIN_EXCEPTION_H_
#define STORM_RAIN_EXCEPTION_H_

#include <exception>

#include <GL/glew.h>
#include <GL/glu.h>

namespace Rain {

class GLFWException : public std::exception {
public:
	GLFWException(const char *error)
	{
		this->error = error;
	}

	virtual const char *what() const throw()
	{
		return error;
	}
private:
	const char *error;
};

class GLEWException : public std::exception {
public:
	GLEWException(GLenum e)
	{
		this->error = (const char *)glewGetErrorString(e);
	}

	virtual const char *what() const throw()
	{
		return error;
	}
private:
	const char *error;
};

class GLException : public std::exception {
public:
	GLException(GLenum e)
	{
		this->error = (const char *)gluErrorString(e);
	}

	virtual const char *what() const throw()
	{
		return error;
	}
private:
	const char *error;
};

class GLSLException : public std::exception {
public:
	GLSLException(const char *error)
	{
		this->error = error;
	}

	virtual const char *what() const throw()
	{
		return error;
	}
private:
	const char *error;
};
}

#endif
