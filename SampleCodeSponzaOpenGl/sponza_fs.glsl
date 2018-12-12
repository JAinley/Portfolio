#version 330

uniform float time_seconds;

in vec3 varying_something;

uniform vec3 uniform_shader;

out vec4 fragment_colour;

void main(void)
{
	fragment_colour = vec4(uniform_shader * varying_something, 1.0);
}
