#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>

#include <engine.h>


GLchar* shader_load(char* path) {
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        return NULL;
    }

    fseek(file, 0L, SEEK_END);
    long int length = ftell(file);
    rewind(file);

    GLchar* shader = memset(malloc(sizeof(GLchar) * (length + 1)), '\0', sizeof(GLchar) * (length + 1));
    fread(shader, sizeof(GLchar), length, file);
    fclose(file);

    return shader;
}


GLuint shader_create_vertex(char* path) {
    const GLchar* vertex_shader_source = shader_load(path);
    if (vertex_shader_source == NULL) {
        #ifdef Debug
            printf("!!! ERROR in engine_create_vertex_shader() !!!\n");
        #endif // Debug
        engine_exit();
        return 1;
    }
    GLuint vertex_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    GLint success;
    GLchar info_log[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        #ifdef Debug
            printf("!!! ERROR in glCompileShader(vertex_shader): %s !!!\n", info_log);
        #endif // Debug
        engine_exit();
        return 1;
    }

    return vertex_shader;
}


GLuint shader_create_fragment(char* path) {
    const GLchar* fragment_shader_source = shader_load(path);
    if (fragment_shader_source == NULL) {
        #ifdef Debug
            printf("!!! ERROR in engine_create_fragment_shader() !!!\n");
        #endif // Debug
        engine_exit();
        return 1;
    }
    GLuint fragment_shader;
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    GLint success;
    GLchar info_log[512];
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
        #ifdef Debug
            printf("!!! ERROR in glCompileShader(fragment_shader): %s !!!\n", info_log);
        #endif // Debug
        engine_exit();
        return 1;
    }

    return fragment_shader;
}


GLuint shader_create_shader_program(GLuint vertex_shader, GLuint fragment_shader) {
    GLuint shader_program;
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    
    GLint success;
    GLchar info_log[512];
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_program, 512, NULL, info_log);
        #ifdef Debug
            printf("!!! ERROR in glLinkProgram(shader_program): %s !!!\n", info_log);
        #endif // Debug
        engine_exit();
        return 1;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return shader_program;
}
