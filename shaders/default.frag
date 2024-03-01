#version 460 core


in vec3 color_vert_out;
out vec4 color_frag_out;
uniform float multiplier;


void main() {
	color_frag_out = vec4(multiplier * color_vert_out.x, multiplier * color_vert_out.y, multiplier * color_vert_out.z, 1.0f);
}
