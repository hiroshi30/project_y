#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <SOIL.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


GLFWwindow* ENGINE_NAME_window;
bool keys[1024];


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
          keys[key] = true;
        } else if (action == GLFW_RELEASE) {
          keys[key] = false;
        }
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
    
    glfwSetKeyCallback(ENGINE_NAME_window, key_callback);
      
    glViewport(0, 0, width, height);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        #ifdef DEBUG
            printf("!!! ERROR in glewInit() !!!\n");
        #endif // DEBUG
        glfwDestroyWindow(ENGINE_NAME_window);
        glfwTerminate();
        return 1;
    }

    glEnable(GL_DEPTH_TEST);
    
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


// void obj_load(char* title, GLuint VAO, GLuint VBO, GLuint EBO) {
//     FILE *file = fopen(title, "r");

//     int vertices_count = 0;
//     int normals_count = 0;
//     int textures_count = 0;
//     int polygons_count = 0;
//     char c;

//     while(1) {
//         c = getc(file);
//         // comments
//         if (c == '#') {
//             while (getc(file) != '\n') {}
//         // mtl files names
//         } else if (c == 'm') {
//             while (getc(file) != '\n') {}
//         // name of model
//         } else if (c == 'o') {
//             while (getc(file) != '\n') {}
//         } else if (c == 'v') {
//             c = getc(file);
//             // coords of vertices 
//             if (c == ' ') {
//                 ++vertices_count;
//                 while (getc(file) != '\n') {}
//             // coords of normals
//             } else if (c == 'n') {
//                 ++normals_count;
//                 while (getc(file) != '\n') {}
//             // coords of textures 
//             } else if (c == 't') {
//                 ++textures_count;
//                 while (getc(file) != '\n') {}           
//             }
//         // i dont know
//         } else if (c == 's') {
//             while (getc(file) != '\n') {}
//         // what mtl style to use
//         } else if (c == 'u') {
//             while (getc(file) != '\n') {}
//         // numbers of coordinates, textures and normals what to use for polygon
//         } else if (c == 'f') {
//             ++polygons_count;
//             while (getc(file) != '\n') {}
//         } else {break;}
//     }

//     rewind(file);

//     GLfloat verticies[vertices_count * 3];
//     GLfloat normals[normals_count * 3];
//     GLfloat textures[textures_count * 2];
//     GLuint polygons[polygons_count * 3 * 3];

//     int vertices_index = 0;
//     int normals_index = 0;
//     int textures_index = 0;
//     int polygons_index = 0;

//     while(1) {
//         c = getc(file);
//         if (c == '#') {
//             while (getc(file) != '\n') {}
//         } else if (c == 'm') {
//             while (getc(file) != '\n') {}
//         } else if (c == 'o') {
//             while (getc(file) != '\n') {}
//         } else if (c == 'v') {
//             c = getc(file);
//             if (c == ' ') {
//                 for (int i = 0; i < 3; ++i) {
//                     fscanf(file, "%f", &verticies[vertices_index * 3 + i]);
//                 }
//                 ++vertices_index;
//                 while (getc(file) != '\n') {}
//             } else if (c == 'n') {
//                 for (int i = 0; i < 3; ++i) {
//                     fscanf(file, "%f", &normals[normals_index * 3 + i]);
//                 }
//                 ++normals_index;
//                 while (getc(file) != '\n') {}
//             } else if (c == 't') {
//                 for (int i = 0; i < 2; ++i) {
//                     fscanf(file, "%f", &textures[textures_index * 2 + i]);
//                 }
//                 ++textures_index;
//                 while (getc(file) != '\n') {}
//             }
//         } else if (c == 's') {
//             while (getc(file) != '\n') {}
//         } else if (c == 'u') {
//             while (getc(file) != '\n') {}
//         } else if (c == 'f') {
//             for (int i = 0; i < 3; ++i) {
//                 fscanf(file, "%u", &polygons[polygons_index * 3 + i + 0]);
//                 getc(file);
//                 fscanf(file, "%u", &polygons[polygons_index * 3 + i + 1]);
//                 getc(file);1
//                 fscanf(file, "%u", &polygons[polygons_index * 3 + i + 2]);
//             }
//             ++polygons_index;
//             while (getc(file) != '\n') {}
//         } else {break;}
//     }

//     fclose(file);

//     ENGINE_NAME_load_model(VAO, VBO, EBO, vertices, sizeof_vertices, (GLuint*){3, 2}, sizeof(GLuint) * 2, indices, sizeof_indices);
// }


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
