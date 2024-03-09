#ifndef vec4_h
#define vec4_h


typedef GLfloat vec4[4];


void vec4_addition(vec4 summand1, vec4 summand2, vec4 sum);
void vec4_subtraction(vec4 minuend, vec4 subtrahend, vec4 difference);
GLfloat vec4_multiplication(vec4 multiplicanda, vec4 multiplier);

void vec4_normalize(vec4 vector);

void vec4_to_vec3(vec4 vector, vec3 vector_result);


#endif // vec4_h
