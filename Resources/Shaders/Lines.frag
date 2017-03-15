#version 330 core

in vec3 color_;
out vec4 color;


void main()
{
	color = vec4(color_, 1.0);
}