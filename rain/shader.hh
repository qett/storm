#ifndef STORM_RAIN_SHADER_H_
#define STORM_RAIN_SHADER_H_

#include <memory>

#include <GL/gl.h>

namespace Rain {

class Shader {
public:
	Shader(const char *file, GLenum type);
	Shader(Shader&& other);
	~Shader();
	unsigned int get_id();
private:
	class Impl;
	std::unique_ptr<Impl> pimpl;
};

}

#endif
