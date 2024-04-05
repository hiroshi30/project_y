#ifndef CAMERA_H
#define CAMERA_H


typedef struct Camera {
	GLfloat movement_speed;
	GLfloat sensitivity;

	GLfloat FOV;
	GLfloat min_FOV;
	GLfloat max_FOV;

	GLfloat yaw;
	GLfloat pitch;

	vec3 position;
	vec3 world_up;
	
	vec3 front;
	vec3 right;
	vec3 up;
	
	mat4x4 view;
} Camera;


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
);
void Camera_update(Camera* camera);
void Camera_look_at(Camera* camera);

void Camera_move(Camera* camera, GLfloat delta_time);
void Camera_look(Camera* camera);
void Camera_scroll(Camera* camera);


#endif // CAMERA_H
