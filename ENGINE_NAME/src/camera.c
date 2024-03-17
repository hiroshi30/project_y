#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <constants.h>
#include <vec3.h>
#include <mat4x4.h>
#include <camera.h>

#include <stdbool.h>
#include <math.h>


extern bool keys[1024];
extern GLfloat x_offset;
extern GLfloat y_offset;
extern GLfloat x_scroll;
extern GLfloat y_scroll;


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
        GLfloat FOV,
        
        GLfloat yaw,
        GLfloat pitch
    ) {
    vec3_make(camera->position, x, y, z);
    vec3_make(camera->world_up, up_x, up_y, up_z);
    camera->movement_speed = movement_speed;
    camera->sensitivity = sensitivity;
    camera->FOV = FOV;
    camera->max_FOV = FOV;
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
    mat4x4_make_identity_matrix(camera->view);

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
    GLfloat camera_speed = camera->movement_speed * delta_time;
    vec3 temp = {0, 0, 0};
    bool move = false;

    if (keys[GLFW_KEY_W]) {
        vec3_addition(temp, camera->front, temp);
        move = true;
    }

    if (keys[GLFW_KEY_S]) {
        vec3_subtraction(temp, camera->front, temp);
        move = true;
    }

    if (keys[GLFW_KEY_A]) {
        vec3_subtraction(temp, camera->right, temp);
        move = true;
    }

    if (keys[GLFW_KEY_D]) {
        vec3_addition(temp, camera->right, temp);
        move = true;
    }

    if (move) {
        vec3_normalize(temp);
        vec3_multiplication_scalar(temp, camera_speed, temp);
        vec3_addition(camera->position, temp, camera->position);
    }
}


void Camera_look(Camera* camera) {
	x_offset *= camera->sensitivity;
    y_offset *= camera->sensitivity;

    camera->yaw -= x_offset;
    camera->pitch += y_offset;

    if (camera->pitch > 89.5f) {
        camera->pitch = 89.5f;
    } else if (camera->pitch < -89.5f) {
        camera->pitch = -89.5f;
    }

    Camera_update(camera);
}


void Camera_scroll(Camera* camera) {
    camera->FOV -= y_scroll;
    if (camera->FOV < 1.0f) {
        camera->FOV = 1.0f;
    }
    if (camera->FOV > camera->max_FOV) {
        camera->FOV = camera->max_FOV;
    }
}
