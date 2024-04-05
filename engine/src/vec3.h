#ifndef VEC3_H
#define VEC3_H


typedef GLfloat vec3[3];


void vec3_make(vec3 vec_c, GLfloat x, GLfloat y, GLfloat z);
void vec3_inverse(vec3 vec_a, vec3 vec_c);
void vec3_normalize(vec3 vec_c);

void vec3_addition(vec3 vec_a, vec3 vec_b, vec3 vec_c);
void vec3_subtraction(vec3 vec_a, vec3 vec_b, vec3 vec_c);
void vec3_cross(vec3 vec_a, vec3 vec_b, vec3 vec_c);
GLfloat vec3_dot(vec3 vec_a, vec3 vec_b);

void vec3_multiplication_scalar(vec3 vec_a, GLfloat vec_b, vec3 vec_c);


#endif // VEC3_H
