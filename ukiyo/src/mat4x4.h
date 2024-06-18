#ifndef MAT4X4_H
#define MAT4X4_H


#define mat4x4Begin(x) &x[0][0]


typedef GLfloat mat4x4[4][4];


void mat4x4Zero(mat4x4 mat);
void mat4x4Identity(mat4x4 mat);

void mat4x4Multiplication(mat4x4 mat_in1, mat4x4 mat_in2, mat4x4 mat_out);

void mat4x4Scale(mat4x4 mat, GLfloat x, GLfloat y, GLfloat z);
void mat4x4Translate(mat4x4 mat, GLfloat x, GLfloat y, GLfloat z);
void mat4x4Rotate(mat4x4 mat, GLfloat x, GLfloat y, GLfloat z);

void mat4x4PerspectiveProjection(mat4x4 mat, GLfloat fov, GLfloat attitude, GLfloat near, GLfloat far);
void mat4x4OrthographicProjection(mat4x4 mat, GLfloat fov, GLfloat attitude, GLfloat near, GLfloat far);


#endif // MAT4X4_H
