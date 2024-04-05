#include <stdlib.h>
#include <math.h>

#include <GL/glew.h>


GLfloat random(GLfloat start, GLfloat end) {
	return start + (GLfloat)rand() / (GLfloat)RAND_MAX * (end - start);
}


GLint random_int(GLint start, GLint end) {
	return start + rand() * (end - start) / RAND_MAX;
}
