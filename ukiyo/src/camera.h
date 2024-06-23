#ifndef CAMERA_H
#define CAMERA_H


typedef struct {
	vec3 position;
	vec3 world_up;
	
	vec3 front;
	vec3 right;
	vec3 up;

	GLfloat yaw;
	GLfloat pitch;

	GLfloat fov;
	GLfloat min_fov;
	GLfloat max_fov;

	GLfloat movement_speed;
	GLfloat sensitivity;
	
	mat4x4 view;
} Camera;


Camera *Camera_allocate(
    GLfloat x, GLfloat y, GLfloat z,
    GLfloat world_up_x, GLfloat world_up_y, GLfloat world_up_z,
    
    GLfloat yaw,
    GLfloat pitch,

    GLfloat min_fov,
    GLfloat max_fov,
    
    GLfloat movement_speed,
    GLfloat sensitivity);
void Camera_deallocate(Camera *camera);

void Camera_update(Camera *camera);
void Camera_calculateView(Camera *camera);

void Camera_move(Camera *camera);
void Camera_look(Camera *camera);
void Camera_scroll(Camera *camera);

void Camera_actions(Camera *camera);


#endif // CAMERA_H
