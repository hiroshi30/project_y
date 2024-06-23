#ifndef VEC3_H
#define VEC3_H


typedef GLfloat vec3[3];


void vec3_create(vec3 vec, GLfloat x, GLfloat y, GLfloat z);
void vec3_zero(vec3 vec);

void vec3_inverse(vec3 vec_in, vec3 vec_out);
GLfloat vec3_length(vec3 vec);
void vec3_normalize(vec3 vec);

void vec3_addition(vec3 vec_in1, vec3 vec_in2, vec3 vec_out);
void vec3_subtraction(vec3 vec_in1, vec3 vec_in2, vec3 vec_out);
void vec3_cross(vec3 vec_in1, vec3 vec_in2, vec3 vec_out);
GLfloat vec3_dot(vec3 vec_in1, vec3 vec_in2);

void vec3_scalarMultiplication(vec3 vec_in1, GLfloat scalar, vec3 vec_out);


#endif // VEC3_H
