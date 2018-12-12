#version 330

uniform float time_seconds;
uniform mat4 model_xform;


in vec3 vertex_position;

in vec3 vertex_colour;

out vec3 varying_something;

void main(void)
{
	varying_something = vertex_colour;
	gl_Position = model_xform * vec4(vertex_position, 1.0);
}
