#ifndef MAT4X4_H
#define MAT4X4_H


#define mat4x4_begin(x) &x[0][0]
#define mat4x4_identity {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}
#define mat4x4_zero {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}


typedef GLfloat mat4x4[4][4];


void mat4x4_make_zero(mat4x4 output);
void mat4x4_make_identity(mat4x4 output);

void mat4x4_multiplication(mat4x4 multiplier1, mat4x4 multiplier2, mat4x4 output);
void mat4x4_scale(mat4x4 output, GLfloat x, GLfloat y, GLfloat z);
void mat4x4_translate(mat4x4 output, GLfloat x, GLfloat y, GLfloat z);
void mat4x4_rotate(mat4x4 output, GLfloat x, GLfloat y, GLfloat z);
void mat4x4_transpose(mat4x4 output);

void mat4x4_perspective_projection(mat4x4 output, GLfloat fov, GLfloat attitude, GLfloat near, GLfloat far);
void mat4x4_orthographic_projection(mat4x4 output, GLfloat fov, GLfloat attitude, GLfloat near, GLfloat far);


#endif // MAT4X4_H
