#version 460 core


layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color_vert_in;
out vec3 color_vert_out;


void main() {
	gl_Position = vec4(position, 1.0);
	color_vert_out = color_vert_in;
}
