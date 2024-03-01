#ifndef ENGINE_H
#define ENGINE_H


#include <GL/glew.h>

#include <GLFW/glfw3.h>


extern GLFWwindow* window;


int engine_init(int width, int height, char* title);
void engine_exit(void);
GLchar* load_shader(char* path);
GLuint create_vertex_shader(char* path);
GLuint create_fragment_shader(char* path);
GLuint create_shader_program(GLuint vertex_shader, GLuint fragment_shader);


#endif // ENGINE_H
