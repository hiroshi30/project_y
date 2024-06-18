#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>

#include "engine.h"


GLchar *shaderLoad(const char *path) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        return NULL;
    }

    fseek(file, 0L, SEEK_END);
    long length = ftell(file);
    rewind(file);

    GLchar *shader = memset(malloc(sizeof(GLchar) * (length + 1)), '\0', sizeof(GLchar) * (length + 1));
    // GLchar *shader = malloc(sizeof(GLchar) * (length + 1));
    // shader[length - 1] = '\0';
    fread(shader, sizeof(GLchar), length, file);
    fclose(file);

    return shader;
}


GLuint vertexShader(const char *path) {
    GLchar *temp = shaderLoad(path);
    const GLchar *vertex_shader_source = temp;

    if (vertex_shader_source == NULL) {
        #ifdef DEBUG
        printf("!!! ERROR in vertexShader(): there is no file with \"%s\" name !!!\n", path);
        #endif // DEBUG
        engineExitFailure();
        return 1;
    }

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    free(temp);
    glCompileShader(vertex_shader);

    GLint success;
    GLchar info_log[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        #ifdef DEBUG
        printf("!!! ERROR in vertexShader(): error in glGetShaderiv() !!!\n%s\n", info_log);
        #endif // DEBUG
        engineExitFailure();
        return 1;
    }

    return vertex_shader;
}


GLuint fragmentShader(const char *path) {
    GLchar *temp = shaderLoad(path);
    const GLchar *fragment_shader_source = temp;

    if (fragment_shader_source == NULL) {
        #ifdef DEBUG
        printf("!!! ERROR in fragmentShader(): there is no file with \"%s\" name !!!\n", path);
        #endif // DEBUG
        engineExitFailure();
        return 1;
    }

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    free(temp);
    glCompileShader(fragment_shader);

    GLint success;
    GLchar info_log[512];
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
        #ifdef DEBUG
        printf("!!! ERROR in fragmentShader(): error in glGetShaderiv() !!!\n%s\n", info_log);
        #endif // DEBUG
        engineExitFailure();
        return 1;
    }

    return fragment_shader;
}


GLuint shaderProgram(const char *vertex_path, const char *fragment_path) {
    GLuint vertex_shader = vertexShader(vertex_path);
    GLuint fragment_shader = fragmentShader(fragment_path);

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    
    GLint success;
    GLchar info_log[512];
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_program, 512, NULL, info_log);
        #ifdef DEBUG
        printf("!!! ERROR in shaderProgram(): error in glGetProgramiv() !!!\n%s\n", info_log);
        #endif // DEBUG
        engineExitFailure();
        return 1;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return shader_program;
}
