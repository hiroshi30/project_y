#include <GL/glew.h>

#include <math.h>

#include <vec3.h>


void vec3_make(vec3 vector, GLfloat x, GLfloat y, GLfloat z) {
	vector[0] = x;
	vector[1] = y;
	vector[2] = z;
}


void vec3_addition(vec3 summand1, vec3 summand2, vec3 sum) {
	sum[0] = summand1[0] + summand2[0];
	sum[1] = summand1[1] + summand2[1];
	sum[2] = summand1[2] + summand2[2];
}


void vec3_subtraction(vec3 minuend, vec3 subtrahend, vec3 difference) {
	difference[0] = minuend[0] - subtrahend[0];
	difference[1] = minuend[1] - subtrahend[1];
	difference[2] = minuend[2] - subtrahend[2];
}


GLfloat vec3_multiplication(vec3 multiplicanda, vec3 multiplier) {
	return multiplicanda[0] * multiplier[0] + multiplicanda[1] * multiplier[1] + multiplicanda[2] * multiplier[2];
}


void vec3_normalize(vec3 vector) {
	GLfloat length = sqrt(vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2]);
	vector[0] /= length;
	vector[1] /= length;
	vector[2] /= length;
}


void vec3_cross(vec3 vector1, vec3 vector2, vec3 vector_result) {
	vec3 temp;
	temp[0] = vector1[1] * vector2[2] - vector1[2] * vector2[1];
	temp[1] = vector1[2] * vector2[0] - vector1[0] * vector2[2];
	temp[2] = vector1[0] * vector2[1] - vector1[1] * vector2[0];
	vector_result[0] = temp[0];
	vector_result[1] = temp[1];
	vector_result[2] = temp[2];
}


void vec3_multiplication_scalar(vec3 multiplicanda, GLfloat multiplier, vec3 product) {
	product[0] = multiplicanda[0] * multiplier;
	product[1] = multiplicanda[1] * multiplier;
	product[2] = multiplicanda[2] * multiplier;
}