#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 light_position;

out vec3 _position;
out vec3 _normal;
out vec3 _light_position;

void main() {
	gl_Position = projection * view * model * vec4(position, 1.0f);
	_position = vec3(view * model * vec4(position, 1.0f));
	_normal = mat3(transpose(inverse(view * model))) * normal;
	_light_position = vec3(view * vec4(light_position, 1.0f));
}
