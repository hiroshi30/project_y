#version 460 core


layout (location = 0) in vec3 position;
layout (location = 1) in vec3 colorVI;
layout (location = 2) in vec2 texture_coordsVI;

out vec3 colorVO;
out vec2 texture_coordsVO;


void main() {
	gl_Position = vec4(position, 1.0f);
	colorVO = colorVI;
	texture_coordsVO = texture_coordsVI;
}
