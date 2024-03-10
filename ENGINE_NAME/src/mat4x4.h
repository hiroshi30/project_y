#ifndef mat4x4_h
#define mat4x4_h


#define mat4x4_begin(x) &x[0][0]
#define identity_mat4x4 {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}
#define zero_mat4x4 {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}


typedef GLfloat mat4x4[4][4];


void mat4x4_make_zero_matrix(mat4x4 output);
void mat4x4_make_identity_matrix(mat4x4 output);

void mat4x4_multiplication(mat4x4 multiplier1, mat4x4 multiplier2, mat4x4 output);
void mat4x4_scale(mat4x4 output, GLfloat x, GLfloat y, GLfloat z);
void mat4x4_translate(mat4x4 output, GLfloat x, GLfloat y, GLfloat z);
void mat4x4_rotate(mat4x4 output, GLfloat x, GLfloat y, GLfloat z);
void mat4x4_transpose(mat4x4 output);

void mat4x4_perspective_projection(mat4x4 output, GLfloat fov, GLfloat attitude, GLfloat near, GLfloat far);
void mat4x4_perspective_projection2(mat4x4 output, GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far);
void mat4x4_orthographic_projection(mat4x4 output, GLfloat fov, GLfloat attitude, GLfloat near, GLfloat far);
void mat4x4_orthographic_projection2(mat4x4 output, GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far);

void mat4x4_look_at(mat4x4 output, vec3 camera_position, vec3 camera_target, vec3 world_up);


#endif // mat4x4_h
