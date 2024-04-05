#ifndef SHADER_H
#define SHADER_H


GLuint shader_create_vertex(char* path);
GLuint shader_create_fragment(char* path);
GLuint shader_create_shader_program(GLuint vertex_shader, GLuint fragment_shader);


#endif // SHADER_H
