#ifndef ENGINE_H
#define ENGINE_H


int engine_init(int width, int height, const char* title);
void engine_exit(void);
GLint engine_get_MAX_VERTEX_ATTRIBS(void);

// void engine_load_model(GLuint VAO, GLuint VBO, GLuint EBO, GLfloat* vertices, GLuint sizeof_vertices, GLuint* data, GLuint sizeof_data, GLuint* indices, GLuint sizeof_indices);
// void obj_load(char* title, GLuint VAO, GLuint VBO, GLuint EBO);


#endif // ENGINE_H
