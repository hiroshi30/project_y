#define GLEW_STATIC
#include <GL/glew.h>

#include <math.h>

#include <mat4x4.h>


void mat4x4_multiplication(mat4x4 multiplier1, mat4x4 multiplier2, mat4x4 output) {
	GLfloat summ;
	for (int x = 0; x < 4; ++x) {
		for (int y = 0; y < 4; ++y) {
			summ = 0;
			for (int i = 0; i < 4; ++i) {
				summ += multiplier1[y][i] * multiplier2[i][x];
			}
			output[y][x] = summ;
		}
	}
}


void mat4x4_scale(mat4x4 output, GLfloat x, GLfloat y, GLfloat z) {
	mat4x4 scale = identity_mat4x4;
	scale[0][0] = x;
	scale[1][1] = y;
	scale[2][2] = z;

	mat4x4_multiplication(output, scale, output);
}


void mat4x4_translate(mat4x4 output, GLfloat x, GLfloat y, GLfloat z) {
	mat4x4 translate = identity_mat4x4;
	translate[0][3] = x;
	translate[1][3] = y;
	translate[2][3] = z;

	mat4x4_multiplication(output, translate, output);
}


void mat4x4_rotate(mat4x4 output, GLfloat x, GLfloat y, GLfloat z) {
	x *= degrees_to_radians;
	y *= degrees_to_radians;
	z *= degrees_to_radians;

	mat4x4 rotate_x = identity_mat4x4;
	rotate_x[1][1] = cos(x);
	rotate_x[1][2] = -sin(x);
	rotate_x[2][1] = sin(x);
	rotate_x[2][2] = cos(x);

	mat4x4_multiplication(rotate_x, output, output);
}


void mat4x4_transpose(mat4x4 output) {
	GLfloat temp;
	for (int y = 0; y < 3; ++y) {
		for (int x = y + 1; x < 4; ++x) {
			temp = output[y][x];
			output[y][x] = output[x][y];
			output[x][y] = temp;
		}
	}
}
