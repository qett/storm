#version 420

layout(location=0) in vec4 in_Position;
layout(location=1) in vec4 in_Color;

out vec4 ex_Color;

uniform float angle;


void
main(void)
{
	/*mat4 rotation = (
		cos(angle),	-sin(angle,	0.0f,	0.0f,
		sin(angle),	cos(angle),	0.0f,	0.0f,
		0.0f,		0.0f,		1.0f,	0.0f,
		0.0f,		0.0f,		0.0f,	1.0f
	);*/

	gl_Position = in_Position;
	ex_Color = in_Color;
}
