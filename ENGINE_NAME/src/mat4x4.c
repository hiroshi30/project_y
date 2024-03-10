#include <GL/glew.h>

#include <math.h>

#include <constants.h>
#include <vec3.h>
#include <mat4x4.h>


void mat4x4_make_zero_matrix(mat4x4 output) {
	output[0][0] = 0.0f;
	output[0][1] = 0.0f;
	output[0][2] = 0.0f;
	output[0][3] = 0.0f;

	output[1][0] = 0.0f;
	output[1][1] = 0.0f;
	output[1][2] = 0.0f;
	output[1][3] = 0.0f;

	output[2][0] = 0.0f;
	output[2][1] = 0.0f;
	output[2][2] = 0.0f;
	output[2][3] = 0.0f;

	output[3][0] = 0.0f;
	output[3][1] = 0.0f;
	output[3][2] = 0.0f;
	output[3][3] = 0.0f;
}


void mat4x4_make_identity_matrix(mat4x4 output) {
	output[0][0] = 1.0f;
	output[0][1] = 0.0f;
	output[0][2] = 0.0f;
	output[0][3] = 0.0f;

	output[1][0] = 0.0f;
	output[1][1] = 1.0f;
	output[1][2] = 0.0f;
	output[1][3] = 0.0f;

	output[2][0] = 0.0f;
	output[2][1] = 0.0f;
	output[2][2] = 1.0f;
	output[2][3] = 0.0f;

	output[3][0] = 0.0f;
	output[3][1] = 0.0f;
	output[3][2] = 0.0f;
	output[3][3] = 1.0f;
}


void mat4x4_multiplication(mat4x4 multiplier1, mat4x4 multiplier2, mat4x4 output) {
	mat4x4 temp = zero_mat4x4;
	for (int x = 0; x < 4; ++x) {
		for (int y = 0; y < 4; ++y) {
			for (int i = 0; i < 4; ++i) {
				temp[y][x] += multiplier1[y][i] * multiplier2[i][x];
			}
		}
	}
	for (int x = 0; x < 4; ++x) {
		for (int y = 0; y < 4; ++y) {
			output[y][x] = temp[y][x];
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

	mat4x4_multiplication(output, rotate_x, output);

	mat4x4 rotate_y = identity_mat4x4;
	rotate_y[0][0] = cos(y);
	rotate_y[0][2] = sin(y);
	rotate_y[2][0] = -sin(y);
	rotate_y[2][2] = cos(y);

	mat4x4_multiplication(output, rotate_y, output);

	mat4x4 rotate_z = identity_mat4x4;
	rotate_z[0][0] = cos(z);
	rotate_z[0][1] = -sin(z);
	rotate_z[1][0] = sin(z);
	rotate_z[1][1] = cos(z);

	mat4x4_multiplication(output, rotate_z, output);
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


void mat4x4_perspective_projection(mat4x4 output, GLfloat fov, GLfloat attitude, GLfloat near, GLfloat far) {
	mat4x4_make_zero_matrix(output);
	
	fov *= degrees_to_radians;

	output[0][0] = 1 / tan(fov / 2);
	output[1][1] = attitude / tan(fov / 2);
	output[2][2] = -(far + near) / (far - near);
	output[2][3] = -2 * far * near / (far - near);
	output[3][2] = -1;
}


void mat4x4_perspective_projection2(mat4x4 output, GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far) {
	mat4x4_make_zero_matrix(output);
	
	output[0][0] = 2 * near / (right - left);
	output[0][2] = (right + left) / (right - left);
	output[1][1] = 2 * near / (top - bottom);
	output[1][2] = (top + bottom) / (top - bottom);
	output[2][2] = -(far + near) / (far - near);
	output[2][3] = -2 * far * near / (far - near);
	output[3][2] = -1;
}


void mat4x4_orthographic_projection(mat4x4 output, GLfloat fov, GLfloat attitude, GLfloat near, GLfloat far) {
	mat4x4_make_zero_matrix(output);
	
	fov *= degrees_to_radians;

	output[0][0] = near / tan(fov / 2);
	output[1][1] = attitude * near / tan(fov / 2);
	output[2][2] = -2 / (far - near);
	output[2][3] = -(far + near) / (far - near);
	output[3][3] = 1;
}


void mat4x4_orthographic_projection2(mat4x4 output, GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far) {
	mat4x4_make_zero_matrix(output);
	
	output[0][0] = 2 / (right - left);
	output[0][3] = -(right + left) / (right - left);
	output[1][1] = 2 / (top - bottom);
	output[1][3] = -(top + bottom) / (top - bottom);
	output[2][2] = -2 / (far - near);
	output[2][3] = -(far + near) / (far - near);
	output[3][3] = 1;
}


void mat4x4_look_at(mat4x4 output, vec3 camera_position, vec3 camera_target, vec3 world_up) {
    vec3 camera_direction;
    vec3_subtraction(camera_position, camera_target, camera_direction);
    vec3_normalize(camera_direction);

    vec3 camera_right;
    vec3_cross(world_up, camera_direction, camera_right);
    vec3_normalize(camera_right);

    vec3 camera_up;
    vec3_cross(camera_direction, camera_right, camera_up);

    mat4x4_make_identity_matrix(output);
    output[0][0] = camera_right[0];
    output[0][1] = camera_right[1];
    output[0][2] = camera_right[2];

    output[1][0] = camera_up[0];
    output[1][1] = camera_up[1];
    output[1][2] = camera_up[2];

    output[2][0] = camera_direction[0];
    output[2][1] = camera_direction[1];
    output[2][2] = camera_direction[2];

    mat4x4 temp = identity_mat4x4;
    temp[0][3] = -camera_position[0];
    temp[1][3] = -camera_position[1];
    temp[2][3] = -camera_position[2];

    mat4x4_multiplication(output, temp, output);
}
