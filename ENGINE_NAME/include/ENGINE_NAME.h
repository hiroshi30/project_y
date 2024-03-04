#ifndef ENGINE_NAME_H
#define ENGINE_NAME_H


#include <GL/glew.h>

#include <GLFW/glfw3.h>


extern GLFWwindow* ENGINE_NAMEWindow;


int ENGINE_NAMEInit(int width, int height, char* title);
void ENGINE_NAMEExit(void);

GLint ENGINE_NAMEGetMAX_VERTEX_ATTRIBS(void);

GLchar* ENGINE_NAMELoadShader(char* path);
GLuint ENGINE_NAMECreateVertexShader(char* path);
GLuint ENGINE_NAMECreateFragmentShader(char* path);
GLuint ENGINE_NAMECreateShaderProgram(GLuint vertex_shader, GLuint fragment_shader);

void ENGINE_NAMELoadModel(GLuint VAO, GLuint VBO, GLuint EBO, GLfloat* vertices, GLuint sizeof_vertices, GLuint* data, GLuint sizeof_data, GLuint* indices, GLuint sizeof_indices);

GLuint ENGINE_NAMECreateTexture(char* path);


#endif // ENGINE_NAME_H
