#version 460 core

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

in vec3 _position;
in vec3 _normal;
in vec3 _light_position;

uniform vec3 object_color;
uniform vec3 light_color;
uniform Material material;

out vec4 color;

void main() {
	float ambient_coefficient = 0.1f;
	vec3 ambient = ambient_coefficient * light_color;

	vec3 normal = normalize(_normal);
	vec3 light_direction = normalize(_light_position - _position);
	float diffuse_coefficient = max(dot(normal, light_direction), 0.0f);
	vec3 diffuse = diffuse_coefficient * light_color;

	float specular_coefficient = 0.5f;
	vec3 camera_direction = normalize(-_position);
	vec3 reflection_direction = reflect(-light_direction, normal);
	float spec = pow(max(dot(camera_direction, reflection_direction), 0.0f), 32);
	vec3 specular = specular_coefficient * spec * light_color;

	color = vec4((ambient + diffuse + specular) * object_color, 1.0f);
}
