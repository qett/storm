#ifndef STORM_RAIN_CONTEXT_H_
#define STORM_RAIN_CONTEXT_H_

class Shader;

namespace Rain {

/*
 * Virtual base class for an OpenGL context.
 */
class Context {
public:
protected:
	unsigned int width, height;
	Shader **shaders;
	unsigned int program;
	const char *name;
};

}

#endif
