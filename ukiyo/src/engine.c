#ifdef DEBUG
#include <stdio.h>
#endif// DEBUG
#include <stdlib.h>
#include <stdbool.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "engine.h"


GLFWwindow *engine_window;
bool keys[1024];

GLfloat last_mouse_x;
GLfloat last_mouse_y;

GLfloat delta_mouse_x;
GLfloat delta_mouse_y;

GLfloat scroll_x;
GLfloat scroll_y;

GLfloat previous_time;
GLfloat current_time;
GLfloat delta_time;


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
    
    engine_window = glfwCreateWindow(width, height, title, 0, 0);
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

    previous_time = glfwGetTime();
}


void engineExit(void) {
    glfwDestroyWindow(engine_window);
    glfwTerminate();
}


void engineExitFailure(void) {
    glfwDestroyWindow(engine_window);
    glfwTerminate();
    exit(EXIT_FAILURE);
}


bool engineWorking(void) {
    return !glfwWindowShouldClose(engine_window);
}


void engineEvents(void) {
    glfwPollEvents();
}


void engineTime(void) {
    current_time = glfwGetTime();
    delta_time = current_time - previous_time;
    previous_time = current_time;
}


void engineClear(void) {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void engineSwapBuffers(void) {
    glfwSwapBuffers(engine_window);
}


void enginePolygonsMeshView(void) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}


GLint engineGet_MAX_VERTEX_ATTRIBS(void) {
    GLint MAX_VERTEX_ATTRIBS;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &MAX_VERTEX_ATTRIBS);

    return MAX_VERTEX_ATTRIBS;
}
