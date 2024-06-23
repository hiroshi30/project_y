#include <math.h>

#include <GL/glew.h>

#include "vec3.h"


void vec3_create(vec3 vec, GLfloat x, GLfloat y, GLfloat z) {
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
}


void vec3_zero(vec3 vec) {
	vec[0] = 0;
	vec[1] = 0;
	vec[2] = 0;
}


void vec3_inverse(vec3 vec_in, vec3 vec_out) {
	vec_out[0] = -vec_in[0];
	vec_out[1] = -vec_in[1];
	vec_out[2] = -vec_in[2];
}


GLfloat vec3_length(vec3 vec) {
	return sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
}


void vec3_normalize(vec3 vec) {
	GLfloat length = vec3_length(vec);
	if (length > 0) {
		vec[0] /= length;
		vec[1] /= length;
		vec[2] /= length;
	}
}


void vec3_addition(vec3 vec_in1, vec3 vec_in2, vec3 vec_out) {
	vec_out[0] = vec_in1[0] + vec_in2[0];
	vec_out[1] = vec_in1[1] + vec_in2[1];
	vec_out[2] = vec_in1[2] + vec_in2[2];
}


void vec3_subtraction(vec3 vec_in1, vec3 vec_in2, vec3 vec_out) {
	vec_out[0] = vec_in1[0] - vec_in2[0];
	vec_out[1] = vec_in1[1] - vec_in2[1];
	vec_out[2] = vec_in1[2] - vec_in2[2];
}


void vec3_cross(vec3 vec_in1, vec3 vec_in2, vec3 vec_out) {
	vec3 temp;
	temp[0] = vec_in1[1] * vec_in2[2] - vec_in1[2] * vec_in2[1];
	temp[1] = vec_in1[2] * vec_in2[0] - vec_in1[0] * vec_in2[2];
	temp[2] = vec_in1[0] * vec_in2[1] - vec_in1[1] * vec_in2[0];
	vec_out[0] = temp[0];
	vec_out[1] = temp[1];
	vec_out[2] = temp[2];
}


GLfloat vec3_dot(vec3 vec1, vec3 vec2) {
	return vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2];
}


void vec3_scalarMultiplication(vec3 vec_in1, GLfloat scalar, vec3 vec_out) {
	vec_out[0] = vec_in1[0] * scalar;
	vec_out[1] = vec_in1[1] * scalar;
	vec_out[2] = vec_in1[2] * scalar;
}
