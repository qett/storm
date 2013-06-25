#ifndef STORM_RAIN_PROGRAM_H_
#define STORM_RAIN_PROGRAM_H_

#include <memory>

namespace Rain {

class Shader;

class Program {
public:
	Program(Shader **shaders);
	~Program();
	
	void
	use();

	void
	unuse();
private:
	class Impl;
	std::unique_ptr<Impl> pimpl;

};

}

#endif
