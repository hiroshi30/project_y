#version 460 core


in vec3 colorVO;
in vec2 texture_coordsVO;

out vec4 colorFO;

uniform sampler2D mytexture;


void main() {
	colorFO = texture(mytexture, texture_coordsVO);
}
