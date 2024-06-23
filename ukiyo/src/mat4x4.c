#include <math.h>

#include <GL/glew.h>

#include "constants.h"
#include "mat4x4.h"


void mat4x4_zero(mat4x4 mat) {
	mat[0][0] = 0;
	mat[0][1] = 0;
	mat[0][2] = 0;
	mat[0][3] = 0;

	mat[1][0] = 0;
	mat[1][1] = 0;
	mat[1][2] = 0;
	mat[1][3] = 0;

	mat[2][0] = 0;
	mat[2][1] = 0;
	mat[2][2] = 0;
	mat[2][3] = 0;

	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 0;
}


void mat4x4_identity(mat4x4 mat) {
	mat[0][0] = 1;
	mat[0][1] = 0;
	mat[0][2] = 0;
	mat[0][3] = 0;

	mat[1][0] = 0;
	mat[1][1] = 1;
	mat[1][2] = 0;
	mat[1][3] = 0;

	mat[2][0] = 0;
	mat[2][1] = 0;
	mat[2][2] = 1;
	mat[2][3] = 0;

	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;
}


void mat4x4_multiplication(mat4x4 mat_in1, mat4x4 mat_in2, mat4x4 mat_out) {
	mat4x4 temp;
	mat4x4_zero(temp);
	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 4; ++x) {
			for (int i = 0; i < 4; ++i) {
				temp[y][x] += mat_in1[y][i] * mat_in2[i][x];
			}
		}
	}
	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 4; ++x) {
			mat_out[y][x] = temp[y][x];
		}
	}
}


void mat4x4_scale(mat4x4 mat, GLfloat x, GLfloat y, GLfloat z) {
	// mat4x4 temp;
	// mat4x4_identity(temp);
	// temp[0][0] = x;
	// temp[1][1] = y;
	// temp[2][2] = z;
	// mat4x4_multiplication(mat, temp, mat);

	mat[0][0] *= x;
	mat[1][0] *= x;
	mat[2][0] *= x;
	mat[3][0] *= x;
	
	mat[0][1] *= y;
	mat[1][1] *= y;
	mat[2][1] *= y;
	mat[3][1] *= y;
	
	mat[0][2] *= z;
	mat[1][2] *= z;
	mat[2][2] *= z;
	mat[3][2] *= z;
}


void mat4x4_translate(mat4x4 mat, GLfloat x, GLfloat y, GLfloat z) {
	// mat4x4 temp;
	// mat4x4_identity(temp);
	// temp[0][3] = x;
	// temp[1][3] = y;
	// temp[2][3] = z;
	// mat4x4_multiplication(mat, temp, mat);

	mat[0][3] += mat[0][0] * x + mat[0][1] * y + mat[0][2] * z;
	mat[1][3] += mat[1][0] * x + mat[1][1] * y + mat[1][2] * z;
	mat[2][3] += mat[2][0] * x + mat[2][1] * y + mat[2][2] * z;
	mat[3][3] += mat[3][0] * x + mat[3][1] * y + mat[3][2] * z;
}


void mat4x4_rotate(mat4x4 mat, GLfloat x, GLfloat y, GLfloat z) {
	x *= DEGREES_TO_RADIANS;
	y *= DEGREES_TO_RADIANS;
	z *= DEGREES_TO_RADIANS;

	mat4x4 rotate_x;
	mat4x4_identity(rotate_x);
	rotate_x[1][1] = cos(x);
	rotate_x[1][2] = -sin(x);
	rotate_x[2][1] = sin(x);
	rotate_x[2][2] = cos(x);

	mat4x4_multiplication(mat, rotate_x, mat);

	mat4x4 rotate_y;
	mat4x4_identity(rotate_y);
	rotate_y[0][0] = cos(y);
	rotate_y[0][2] = sin(y);
	rotate_y[2][0] = -sin(y);
	rotate_y[2][2] = cos(y);

	mat4x4_multiplication(mat, rotate_y, mat);

	mat4x4 rotate_z;
	mat4x4_identity(rotate_z);
	rotate_z[0][0] = cos(z);
	rotate_z[0][1] = -sin(z);
	rotate_z[1][0] = sin(z);
	rotate_z[1][1] = cos(z);

	mat4x4_multiplication(mat, rotate_z, mat);
}


void mat4x4_perspectiveProjection(mat4x4 mat, GLfloat fov, GLfloat attitude, GLfloat near, GLfloat far) {
	mat4x4_zero(mat);
	
	fov *= DEGREES_TO_RADIANS;

	mat[0][0] = 1 / tan(fov / 2);
	mat[1][1] = attitude / tan(fov / 2);
	mat[2][2] = -(far + near) / (far - near);
	mat[2][3] = -2 * far * near / (far - near);
	mat[3][2] = -1;
}


void mat4x4_orthographicProjection(mat4x4 mat, GLfloat fov, GLfloat attitude, GLfloat near, GLfloat far) {
	mat4x4_zero(mat);
	
	fov *= DEGREES_TO_RADIANS;

	mat[0][0] = near / tan(fov / 2);
	mat[1][1] = attitude * near / tan(fov / 2);
	mat[2][2] = -2 / (far - near);
	mat[2][3] = -(far + near) / (far - near);
	mat[3][3] = 1;
}
