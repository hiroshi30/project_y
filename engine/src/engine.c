#ifdef Debug
#include <stdio.h>
#endif// Debug
#include <stdbool.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


GLFWwindow* engine_window;
bool keys[1024];

GLfloat last_x;
GLfloat last_y;

GLfloat delta_x;
GLfloat delta_y;

GLfloat scroll_x;
GLfloat scroll_y;


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


void mouse_callback(GLFWwindow* window, double x, double y) {
    delta_x = last_x - x;
    delta_y = last_y - y;

    last_x = x;
    last_y = y;
}


void scroll_callback(GLFWwindow* window, double x, double y) {
    scroll_x = x;
    scroll_y = y;
}


int engine_init(int width, int height, const char* title) {
    if (glfwInit() == GLFW_FALSE) {
        #ifdef Debug
            printf("!!! ERROR in glfwInit() !!!\n");
        #endif // Debug
        glfwTerminate();

        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    engine_window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (engine_window == NULL) {
        #ifdef Debug
            printf("!!! ERROR in glfwCreateWindow() !!!\n");
        #endif // Debug
        glfwDestroyWindow(engine_window);
        glfwTerminate();

        return 1;
    }
    glfwMakeContextCurrent(engine_window);
    
    glfwSetInputMode(engine_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetKeyCallback(engine_window, key_callback);
    glfwSetCursorPosCallback(engine_window, mouse_callback);
    glfwSetScrollCallback(engine_window, scroll_callback);

    last_x = (GLfloat)width / 2;
    last_y = (GLfloat)height / 2;
    
    glfwSetCursorPos(engine_window, last_x, last_y);

    glViewport(0, 0, width, height);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        #ifdef Debug
            printf("!!! ERROR in glewInit() !!!\n");
        #endif // Debug
        glfwDestroyWindow(engine_window);
        glfwTerminate();

        return 1;
    }

    glEnable(GL_DEPTH_TEST);
    
    return 0;
}


void engine_exit(void) {
    glfwDestroyWindow(engine_window);
    glfwTerminate();
}


GLint engine_get_MAX_VERTEX_ATTRIBS(void) {
    GLint MAX_VERTEX_ATTRIBS;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &MAX_VERTEX_ATTRIBS);

    return MAX_VERTEX_ATTRIBS;
}






























// void engine_load_model(GLuint VAO, GLuint VBO, GLuint EBO, GLfloat* vertices, GLuint sizeof_vertices, GLuint* data, GLuint sizeof_data, GLuint* indices, GLuint sizeof_indices) {
//     glBindVertexArray(VAO);

//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof_vertices, vertices, GL_STATIC_DRAW);
    
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof_indices, indices, GL_STATIC_DRAW);

//     GLuint data_length = sizeof_data / sizeof(GLuint);
//     GLuint vertex_length = 0;
//     for (GLuint i = 0; i < data_length; ++i) {
//         vertex_length += data[i];
//     }
//     GLuint stride = 0;
//     for (GLuint i = 0; i < data_length; ++i) {
//         glVertexAttribPointer(i, data[i], GL_FLOAT, GL_FALSE, vertex_length * sizeof(GLfloat), (GLvoid*)(stride * sizeof(GLfloat)));
//         glEnableVertexAttribArray(i);
//         stride += data[i];
//     }

//     glBindVertexArray(0);
// }


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

//     engine_load_model(VAO, VBO, EBO, vertices, sizeof_vertices, (GLuint*){3, 2}, sizeof(GLuint) * 2, indices, sizeof_indices);
// }
