#ifndef vec3_h
#define vec3_h


typedef GLfloat vec3[3];


void vec3_addition(vec3 summand1, vec3 summand2, vec3 sum);
void vec3_subtraction(vec3 minuend, vec3 subtrahend, vec3 difference);
GLfloat vec3_multiplication(vec3 multiplicanda, vec3 multiplier);

void vec3_normalize(vec3 vector);

void vec3_cross(vec3 vector1, vec3 vector2, vec3 vector_result);

#endif // vec3_h
