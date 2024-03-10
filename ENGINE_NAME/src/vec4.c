#include <GL/glew.h>

#include <math.h>

#include <vec3.h>
#include <vec4.h>


void vec4_addition(vec4 summand1, vec4 summand2, vec4 sum) {
	sum[0] = summand1[0] + summand2[0];
	sum[1] = summand1[1] + summand2[1];
	sum[2] = summand1[2] + summand2[2];
	sum[3] = summand1[3] + summand2[3];
}


void vec4_subtraction(vec4 minuend, vec4 subtrahend, vec4 difference) {
	difference[0] = minuend[0] - subtrahend[0];
	difference[1] = minuend[1] - subtrahend[1];
	difference[2] = minuend[2] - subtrahend[2];
	difference[3] = minuend[3] - subtrahend[3];
}


GLfloat vec4_multiplication(vec4 multiplicanda, vec4 multiplier) {
	return multiplicanda[0] * multiplier[0] + multiplicanda[1] * multiplier[1] + multiplicanda[2] * multiplier[2] + multiplicanda[3] * multiplier[3];
}


void vec4_normalize(vec4 vector) {
	GLfloat length = sqrt(vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2] + vector[3] * vector[3]);
	vector[0] /= length;
	vector[1] /= length;
	vector[2] /= length;
	vector[3] /= length;
}


void vec4_to_vec3(vec4 vector, vec3 vector_result) {
	vector_result[0] = vector[0] / vector[3];
	vector_result[1] = vector[1] / vector[3];
	vector_result[2] = vector[2] / vector[3];
}
