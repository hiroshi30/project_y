#define DEBUG

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <SOIL.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


GLFWwindow* ENGINE_NAME_window;


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}


int ENGINE_NAME_init(int width, int height, char* title) {
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
    
    ENGINE_NAME_window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (ENGINE_NAME_window == NULL) {
        #ifdef DEBUG
            printf("!!! ERROR in glfwCreateWindow() !!!\n");
        #endif // DEBUG
        glfwDestroyWindow(ENGINE_NAME_window);
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(ENGINE_NAME_window);
      
    glViewport(0, 0, width, height);

    glfwSetKeyCallback(ENGINE_NAME_window, key_callback);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        #ifdef DEBUG
            printf("!!! ERROR in glewInit() !!!\n");
        #endif // DEBUG
        glfwDestroyWindow(ENGINE_NAME_window);
        glfwTerminate();
        return 1;
    }

    return 0;
}


void ENGINE_NAME_exit(void) {
    glfwDestroyWindow(ENGINE_NAME_window);
    glfwTerminate();
}


GLint ENGINE_NAME_get_MAX_VERTEX_ATTRIBS(void) {
    GLint MAX_VERTEX_ATTRIBS;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &MAX_VERTEX_ATTRIBS);
    return MAX_VERTEX_ATTRIBS;
}


GLchar* ENGINE_NAME_load_shader(char* path) {
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


GLuint ENGINE_NAME_create_vertex_shader(char* path) {
    const GLchar* vertex_shader_source = ENGINE_NAME_load_shader(path);
    if (vertex_shader_source == NULL) {
        #ifdef DEBUG
            printf("!!! ERROR in loading vertex shader source !!!\n");
        #endif // DEBUG
        ENGINE_NAME_exit();
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
        ENGINE_NAME_exit();
        return 1;
    }

    return vertex_shader;
}


GLuint ENGINE_NAME_create_fragment_shader(char* path) {
    const GLchar* fragment_shader_source = ENGINE_NAME_load_shader(path);
    if (fragment_shader_source == NULL) {
        #ifdef DEBUG
            printf("!!! ERROR in loading fragment shader source !!!\n");
        #endif // DEBUG
        ENGINE_NAME_exit();
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
        #ifdef DEBUG
            printf("!!! ERROR in creating fragment shader !!!\n%s\n", info_log);
        #endif // DEBUG
        ENGINE_NAME_exit();
        return 1;
    }

    return fragment_shader;
}


GLuint ENGINE_NAME_create_shader_program(GLuint vertex_shader, GLuint fragment_shader) {
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
        ENGINE_NAME_exit();
        return 1;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return shader_program;
}


void ENGINE_NAME_load_model(GLuint VAO, GLuint VBO, GLuint EBO, GLfloat* vertices, GLuint sizeof_vertices, GLuint* data, GLuint sizeof_data, GLuint* indices, GLuint sizeof_indices) {
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof_vertices, vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof_indices, indices, GL_STATIC_DRAW);

    GLuint data_length = sizeof_data / sizeof(GLuint);
    GLuint vertex_length = 0;
    for (GLuint i = 0; i < data_length; ++i) {
        vertex_length += data[i];
    }
    GLuint stride = 0;
    for (GLuint i = 0; i < data_length; ++i) {
        glVertexAttribPointer(i, data[i], GL_FLOAT, GL_FALSE, vertex_length * sizeof(GLfloat), (GLvoid*)(stride * sizeof(GLfloat)));
        glEnableVertexAttribArray(i);
        stride += data[i];
    }

    glBindVertexArray(0);
}


GLuint ENGINE_NAME_create_texture(char* path) {
    int width, height;
    unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);

    GLuint texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}
