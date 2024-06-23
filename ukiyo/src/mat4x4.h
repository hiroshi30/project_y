#ifndef MAT4X4_H
#define MAT4X4_H


#define mat4x4_begin(x) &x[0][0]


typedef GLfloat mat4x4[4][4];


void mat4x4_zero(mat4x4 mat);
void mat4x4_identity(mat4x4 mat);

void mat4x4_multiplication(mat4x4 mat_in1, mat4x4 mat_in2, mat4x4 mat_out);

void mat4x4_scale(mat4x4 mat, GLfloat x, GLfloat y, GLfloat z);
void mat4x4_translate(mat4x4 mat, GLfloat x, GLfloat y, GLfloat z);
void mat4x4_rotate(mat4x4 mat, GLfloat x, GLfloat y, GLfloat z);

void mat4x4_perspectiveProjection(mat4x4 mat, GLfloat fov, GLfloat attitude, GLfloat near, GLfloat far);
void mat4x4_orthographicProjection(mat4x4 mat, GLfloat fov, GLfloat attitude, GLfloat near, GLfloat far);


#endif // MAT4X4_H
