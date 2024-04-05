#include <stdbool.h>
#include <math.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <constants.h>
#include <vec3.h>
#include <mat4x4.h>
#include <camera.h>


extern bool keys[1024];

extern GLfloat delta_x;
extern GLfloat delta_y;

extern GLfloat scroll_x;
extern GLfloat scroll_y;


void Camera_construct(
        Camera* camera,
        
        GLfloat x,
        GLfloat y,
        GLfloat z,
        
        GLfloat up_x,
        GLfloat up_y,
        GLfloat up_z,
        
        GLfloat movement_speed,
        GLfloat sensitivity,

        GLfloat min_FOV,
        GLfloat max_FOV,
        
        GLfloat yaw,
        GLfloat pitch
    ) {
    vec3_make(camera->position, x, y, z);
    vec3_make(camera->world_up, up_x, up_y, up_z);
    camera->movement_speed = movement_speed;
    camera->sensitivity = sensitivity;

    camera->FOV = max_FOV;
    camera->min_FOV = min_FOV;
    camera->max_FOV = max_FOV;
    
    camera->yaw = yaw;
    camera->pitch = pitch;

    Camera_update(camera);
}


void Camera_update(Camera* camera) {
    vec3_make(camera->front,
    	cos(camera->yaw * degrees_to_radians) * cos(camera->pitch * degrees_to_radians),
    	sin(camera->pitch * degrees_to_radians),
    	sin(camera->yaw * degrees_to_radians) * cos(camera->pitch * degrees_to_radians)
    );
    vec3_normalize(camera->front);  

    vec3_cross(camera->front, camera->world_up, camera->right);
    vec3_normalize(camera->right);

    vec3_cross(camera->right, camera->front, camera->up);
    vec3_normalize(camera->up);
}


void Camera_look_at(Camera* camera) {
    mat4x4_make_identity(camera->view);

    camera->view[0][0] = camera->right[0];
    camera->view[0][1] = camera->right[1];
    camera->view[0][2] = camera->right[2];

    camera->view[1][0] = camera->up[0];
    camera->view[1][1] = camera->up[1];
    camera->view[1][2] = camera->up[2];

    camera->view[2][0] = -camera->front[0];
    camera->view[2][1] = -camera->front[1];
    camera->view[2][2] = -camera->front[2];

    // mat4x4 temp = mat4x4_identity;
    // temp[0][3] = -camera->position[0];
    // temp[1][3] = -camera->position[1];
    // temp[2][3] = -camera->position[2];

    // mat4x4_multiplication(camera->view, temp, camera->view);

    camera->view[0][3] = -(camera->right[0] * camera->position[0] + camera->right[1] * camera->position[1] + camera->right[2] * camera->position[2]);
    camera->view[1][3] = -(camera->up[0] * camera->position[0] + camera->up[1] * camera->position[1] + camera->up[2] * camera->position[2]);
    camera->view[2][3] = camera->front[0] * camera->position[0] + camera->front[1] * camera->position[1] + camera->front[2] * camera->position[2];
}


void Camera_move(Camera* camera, GLfloat delta_time) {
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_S] || keys[GLFW_KEY_A] || keys[GLFW_KEY_D]) {
        GLfloat camera_speed = camera->movement_speed * delta_time;
        vec3 temp = {0, 0, 0};

        if (keys[GLFW_KEY_W]) {
            vec3_addition(temp, camera->front, temp);
        }

        if (keys[GLFW_KEY_S]) {
            vec3_subtraction(temp, camera->front, temp);
        }

        if (keys[GLFW_KEY_A]) {
            vec3_subtraction(temp, camera->right, temp);
        }

        if (keys[GLFW_KEY_D]) {
            vec3_addition(temp, camera->right, temp);
        }

        vec3_normalize(temp);
        vec3_multiplication_scalar(temp, camera_speed, temp);
        vec3_addition(camera->position, temp, camera->position);
    }
}


void Camera_look(Camera* camera) {
    camera->yaw -= delta_x * camera->sensitivity;
    delta_x = 0;
    while (camera->yaw > 360) {
        camera->yaw -= 360;
    }
    while (camera->yaw < 0) {
        camera->yaw += 360;
    }

    camera->pitch += delta_y * camera->sensitivity;
    delta_y = 0;
    if (camera->pitch > 89) {
        camera->pitch = 89;
    } else if (camera->pitch < -89) {
        camera->pitch = -89;
    }

    Camera_update(camera);
}


void Camera_scroll(Camera* camera) {
    camera->FOV -= scroll_y;
    if (camera->FOV < camera->min_FOV) {
        camera->FOV = camera->min_FOV;
    }
    if (camera->FOV > camera->max_FOV) {
        camera->FOV = camera->max_FOV;
    }
}
