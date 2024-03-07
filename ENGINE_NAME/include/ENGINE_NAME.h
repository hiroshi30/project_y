#ifndef ENGINE_NAME_H
#define ENGINE_NAME_H


#define DEBUG


#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>


extern GLFWwindow* ENGINE_NAME_window;


int ENGINE_NAME_init(int width, int height, char* title);
void ENGINE_NAME_exit(void);

GLint ENGINE_NAME_get_MAX_VERTEX_ATTRIBS(void);

GLchar* ENGINE_NAME_load_shader(char* path);
GLuint ENGINE_NAME_create_vertex_shader(char* path);
GLuint ENGINE_NAME_create_fragment_shader(char* path);
GLuint ENGINE_NAME_create_shader_program(GLuint vertex_shader, GLuint fragment_shader);

void ENGINE_NAME_load_model(GLuint VAO, GLuint VBO, GLuint EBO, GLfloat* vertices, GLuint sizeof_vertices, GLuint* data, GLuint sizeof_data, GLuint* indices, GLuint sizeof_indices);

GLuint ENGINE_NAME_create_texture(char* path);


#endif // ENGINE_NAME_H
