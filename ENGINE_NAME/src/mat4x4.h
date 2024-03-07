#ifndef mat4x4_h
#define mat4x4_h


#define pi 3.14159265359
#define degrees_to_radians pi / 180
#define radians_to_degrees 180 / pi

#define begin_mat4x4(x) &x[0][0]
#define identity_mat4x4 {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}
#define zero_mat4x4 {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}


typedef GLfloat mat4x4[4][4];


void mat4x4_multiplication(mat4x4 multiplier1, mat4x4 multiplier2, mat4x4 output);
void mat4x4_scale(mat4x4 output, GLfloat x, GLfloat y, GLfloat z);
void mat4x4_translate(mat4x4 output, GLfloat x, GLfloat y, GLfloat z);
void mat4x4_rotate(mat4x4 output, GLfloat x, GLfloat y, GLfloat z);
void mat4x4_transpose(mat4x4 output);


#endif // mat4x4_h
