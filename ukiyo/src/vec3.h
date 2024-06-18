#ifndef VEC3_H
#define VEC3_H


typedef GLfloat vec3[3];


void vec3Zero(vec3 vec);
void vec3Make(vec3 vec, GLfloat x, GLfloat y, GLfloat z);
void vec3Inverse(vec3 vec_in, vec3 vec_out);
void vec3Normalize(vec3 vec);

void vec3Addition(vec3 vec_in1, vec3 vec_in2, vec3 vec_out);
void vec3Subtraction(vec3 vec_in1, vec3 vec_in2, vec3 vec_out);
void vec3Cross(vec3 vec_in1, vec3 vec_in2, vec3 vec_out);
GLfloat vec3Dot(vec3 vec_in1, vec3 vec_in2);

void vec3ScalarMultiplication(vec3 vec_in1, GLfloat scalar, vec3 vec_out);


#endif // VEC3_H
