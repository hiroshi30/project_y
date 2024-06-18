#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "constants.h"
#include "vec3.h"
#include "mat4x4.h"
#include "camera.h"


extern bool keys[1024];

extern GLfloat delta_mouse_x;
extern GLfloat delta_mouse_y;

extern GLfloat scroll_x;
extern GLfloat scroll_y;


Camera *cameraAllocate(
    GLfloat x, GLfloat y, GLfloat z,
    GLfloat world_up_x, GLfloat world_up_y, GLfloat world_up_z,
    
    GLfloat yaw,
    GLfloat pitch,

    GLfloat min_fov,
    GLfloat max_fov,
    
    GLfloat movement_speed,
    GLfloat sensitivity) {
    
    Camera *camera = malloc(sizeof(Camera));

    vec3Make(camera->position, x, y, z);
    vec3Make(camera->world_up, world_up_x, world_up_y, world_up_z);
    
    camera->yaw = yaw;
    camera->pitch = pitch;

    camera->fov = max_fov;
    camera->min_fov = min_fov;
    camera->max_fov = max_fov;
    
    camera->movement_speed = movement_speed;
    camera->sensitivity = sensitivity;

    cameraUpdate(camera);

    return camera;
}


void cameraDeallocate(Camera *camera) {
    free(camera);
}


void cameraUpdate(Camera *camera) {
    vec3Make(camera->front,
    	cos(camera->yaw * DEGREES_TO_RADIANS) * cos(camera->pitch * DEGREES_TO_RADIANS),
    	sin(camera->pitch * DEGREES_TO_RADIANS),
    	sin(camera->yaw * DEGREES_TO_RADIANS) * cos(camera->pitch * DEGREES_TO_RADIANS)
    );
    vec3Normalize(camera->front);  

    vec3Cross(camera->front, camera->world_up, camera->right);
    vec3Normalize(camera->right);

    vec3Cross(camera->right, camera->front, camera->up);
    vec3Normalize(camera->up);
}


void cameraCalculateView(Camera *camera) {
    mat4x4Identity(camera->view);

    camera->view[0][0] = camera->right[0];
    camera->view[0][1] = camera->right[1];
    camera->view[0][2] = camera->right[2];

    camera->view[1][0] = camera->up[0];
    camera->view[1][1] = camera->up[1];
    camera->view[1][2] = camera->up[2];

    camera->view[2][0] = -camera->front[0];
    camera->view[2][1] = -camera->front[1];
    camera->view[2][2] = -camera->front[2];

    // mat4x4 temp;
    // mat4x4Identity(temp);
    // temp[0][3] = -camera->position[0];
    // temp[1][3] = -camera->position[1];
    // temp[2][3] = -camera->position[2];
    // mat4x4Multiplication(camera->view, temp, camera->view);

    camera->view[0][3] = -(camera->right[0] * camera->position[0] + camera->right[1] * camera->position[1] + camera->right[2] * camera->position[2]);
    camera->view[1][3] = -(camera->up[0] * camera->position[0] + camera->up[1] * camera->position[1] + camera->up[2] * camera->position[2]);
    camera->view[2][3] = camera->front[0] * camera->position[0] + camera->front[1] * camera->position[1] + camera->front[2] * camera->position[2];
}


void cameraMove(Camera *camera, GLfloat delta_time) {
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_S] || keys[GLFW_KEY_A] || keys[GLFW_KEY_D]) {
        GLfloat camera_speed = camera->movement_speed * delta_time;
        vec3 temp;
        vec3Zero(temp);

        if (keys[GLFW_KEY_W]) {
            vec3Addition(temp, camera->front, temp);
        }

        if (keys[GLFW_KEY_S]) {
            vec3Subtraction(temp, camera->front, temp);
        }

        if (keys[GLFW_KEY_A]) {
            vec3Subtraction(temp, camera->right, temp);
        }

        if (keys[GLFW_KEY_D]) {
            vec3Addition(temp, camera->right, temp);
        }

        vec3Normalize(temp);
        vec3ScalarMultiplication(temp, camera_speed, temp);
        vec3Addition(camera->position, temp, camera->position);
    }
}


void cameraLook(Camera *camera) {
    camera->yaw -= delta_mouse_x * camera->sensitivity;
    delta_mouse_x = 0;
    while (camera->yaw > 360) {
        camera->yaw -= 360;
    }
    while (camera->yaw < 0) {
        camera->yaw += 360;
    }

    camera->pitch += delta_mouse_y * camera->sensitivity;
    delta_mouse_y = 0;
    if (camera->pitch > 89) {
        camera->pitch = 89;
    } else if (camera->pitch < -89) {
        camera->pitch = -89;
    }

    cameraUpdate(camera);
}


void cameraScroll(Camera *camera) {
    camera->fov -= scroll_y;
    if (camera->fov < camera->min_fov) {
        camera->fov = camera->min_fov;
    }
    if (camera->fov > camera->max_fov) {
        camera->fov = camera->max_fov;
    }
}
