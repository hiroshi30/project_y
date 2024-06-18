#ifdef DEBUG
#include <stdio.h>
#endif// DEBUG
#include <stdlib.h>
#include <stdbool.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


GLFWwindow *engine_window;
bool keys[1024];

GLfloat last_mouse_x;
GLfloat last_mouse_y;

GLfloat delta_mouse_x;
GLfloat delta_mouse_y;

GLfloat scroll_x;
GLfloat scroll_y;


void engineExit(void) {
    glfwDestroyWindow(engine_window);
    glfwTerminate();
}


void engineExitFailure(void) {
    glfwDestroyWindow(engine_window);
    glfwTerminate();
    exit(EXIT_FAILURE);
}


void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode) {
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


void mouseCallback(GLFWwindow *window, double x, double y) {
    delta_mouse_x = last_mouse_x - x;
    delta_mouse_y = last_mouse_y - y;

    last_mouse_x = x;
    last_mouse_y = y;
}


void scrollCallback(GLFWwindow *window, double x, double y) {
    scroll_x = x;
    scroll_y = y;
}


void engineInit(int width, int height, const char *title) {
    if (glfwInit() == GLFW_FALSE) {
        #ifdef DEBUG
        printf("!!! ERROR in engineInit(): error in glfwInit() !!!\n");
        #endif // DEBUG
        engineExitFailure();
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    engine_window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (engine_window == NULL) {
        #ifdef DEBUG
        printf("!!! ERROR in engineInit(): error in glfwCreateWindow() !!!\n");
        #endif // DEBUG
        engineExitFailure();
    }
    glfwMakeContextCurrent(engine_window);
    
    glfwSetInputMode(engine_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetKeyCallback(engine_window, keyCallback);
    glfwSetCursorPosCallback(engine_window, mouseCallback);
    glfwSetScrollCallback(engine_window, scrollCallback);

    last_mouse_x = (GLfloat)width / 2;
    last_mouse_y = (GLfloat)height / 2;
    
    glfwSetCursorPos(engine_window, last_mouse_x, last_mouse_y);

    glViewport(0, 0, width, height);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        #ifdef DEBUG
        printf("!!! ERROR in engineInit(): error in glewInit() !!!\n");
        #endif // DEBUG
        engineExitFailure();
    }

    glEnable(GL_DEPTH_TEST);
}


GLint engineGet_MAX_VERTEX_ATTRIBS(void) {
    GLint MAX_VERTEX_ATTRIBS;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &MAX_VERTEX_ATTRIBS);

    return MAX_VERTEX_ATTRIBS;
}
