#include <math.h>

#include <GL/glew.h>

#include <vec3.h>



void vec3_make(vec3 vec_c, GLfloat x, GLfloat y, GLfloat z) {
	vec_c[0] = x;
	vec_c[1] = y;
	vec_c[2] = z;
}


void vec3_inverse(vec3 vec_a, vec3 vec_c) {
	vec_c[0] = -vec_a[0];
	vec_c[1] = -vec_a[1];
	vec_c[2] = -vec_a[2];
}


void vec3_normalize(vec3 vec_c) {
	GLfloat length = sqrt(vec_c[0] * vec_c[0] + vec_c[1] * vec_c[1] + vec_c[2] * vec_c[2]);
	if (length > 0) {
		vec_c[0] /= length;
		vec_c[1] /= length;
		vec_c[2] /= length;
	}
}


void vec3_addition(vec3 vec_a, vec3 vec_b, vec3 vec_c) {
	vec_c[0] = vec_a[0] + vec_b[0];
	vec_c[1] = vec_a[1] + vec_b[1];
	vec_c[2] = vec_a[2] + vec_b[2];
}


void vec3_subtraction(vec3 vec_a, vec3 vec_b, vec3 vec_c) {
	vec_c[0] = vec_a[0] - vec_b[0];
	vec_c[1] = vec_a[1] - vec_b[1];
	vec_c[2] = vec_a[2] - vec_b[2];
}


void vec3_cross(vec3 vec_a, vec3 vec_b, vec3 vec_c) {
	vec3 temp;
	temp[0] = vec_a[1] * vec_b[2] - vec_a[2] * vec_b[1];
	temp[1] = vec_a[2] * vec_b[0] - vec_a[0] * vec_b[2];
	temp[2] = vec_a[0] * vec_b[1] - vec_a[1] * vec_b[0];
	vec_c[0] = temp[0];
	vec_c[1] = temp[1];
	vec_c[2] = temp[2];
}


GLfloat vec3_dot(vec3 vec_a, vec3 vec_b) {
	return vec_a[0] * vec_b[0] + vec_a[1] * vec_b[1] + vec_a[2] * vec_b[2];
}


void vec3_multiplication_scalar(vec3 vec_a, GLfloat vec_b, vec3 vec_c) {
	vec_c[0] = vec_a[0] * vec_b;
	vec_c[1] = vec_a[1] * vec_b;
	vec_c[2] = vec_a[2] * vec_b;
}
