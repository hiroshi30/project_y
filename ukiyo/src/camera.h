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


Camera *cameraAllocate(
    GLfloat x, GLfloat y, GLfloat z,
    GLfloat world_up_x, GLfloat world_up_y, GLfloat world_up_z,
    
    GLfloat yaw,
    GLfloat pitch,

    GLfloat min_fov,
    GLfloat max_fov,
    
    GLfloat movement_speed,
    GLfloat sensitivity);
void cameraDeallocate(Camera *camera);

void cameraMove(Camera *camera, GLfloat delta_time);
void cameraLook(Camera *camera);
void cameraScroll(Camera *camera);
void cameraUpdate(Camera *camera);

void cameraCalculateView(Camera *camera);


#endif // CAMERA_H
