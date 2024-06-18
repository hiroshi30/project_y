#include <stdlib.h>
#include <math.h>

#include <GL/glew.h>


GLfloat random(GLfloat start, GLfloat end) {
	return start + (GLfloat)rand() * (end - start) / (GLfloat)RAND_MAX;
}


GLint randomInt(GLint start, GLint end) {
	return start + rand() * (end - start) / RAND_MAX;
}
