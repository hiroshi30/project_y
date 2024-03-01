#define DEBUG

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


GLFWwindow* window;


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}


int engine_init(int width, int height, char* title) {
    if (glfwInit() == GLFW_FALSE) {
        #ifdef DEBUG
            printf("!!! ERROR in glfwInit() !!!\n");
        #endif // DEBUG
        glfwTerminate();
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL) {
        #ifdef DEBUG
            printf("!!! ERROR in glfwCreateWindow() !!!\n");
        #endif // DEBUG
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
      
    glViewport(0, 0, width, height);

    glfwSetKeyCallback(window, key_callback);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        #ifdef DEBUG
            printf("!!! ERROR in glewInit() !!!\n");
        #endif // DEBUG
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }

    return 0;
}


void engine_exit(void) {
    glfwDestroyWindow(window);
    glfwTerminate();
}


GLchar* load_shader(char* path) {
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


GLuint create_vertex_shader(char* path) {
    const GLchar* vertex_shader_source = load_shader(path);
    if (vertex_shader_source == NULL) {
        #ifdef DEBUG
            printf("!!! ERROR in loading vertex shader source !!!\n");
        #endif // DEBUG
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
        #ifdef DEBUG
            printf("!!! ERROR in creating vertex shader !!!\n%s\n", info_log);
        #endif // DEBUG
        engine_exit();
        return 1;
    }

    return vertex_shader;
}


GLuint create_fragment_shader(char* path) {
    const GLchar* fragment_shaderSource = load_shader(path);
    if (fragment_shaderSource == NULL) {
        #ifdef DEBUG
            printf("!!! ERROR in loading fragment shader source !!!\n");
        #endif // DEBUG
        engine_exit();
        return 1;
    }
    GLuint fragment_shader;
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragment_shader, 1, &fragment_shaderSource, NULL);
    glCompileShader(fragment_shader);

    GLint success;
    GLchar info_log[512];
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
        #ifdef DEBUG
            printf("!!! ERROR in creating fragment shader !!!\n%s\n", info_log);
        #endif // DEBUG
        engine_exit();
        return 1;
    }

    return fragment_shader;
}

GLuint create_shader_program(GLuint vertex_shader, GLuint fragment_shader) {
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
        #ifdef DEBUG
            printf("!!! ERROR in creating shader program !!!\n%s\n", info_log);
        #endif // DEBUG
        engine_exit();
        return 1;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return shader_program;
}