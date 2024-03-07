#include <ENGINE_NAME.h>
#include <mat4x4.h>

#include <stdio.h>


int main(void) {
   	if (ENGINE_NAME_init(500, 250, "project_y") != 0) {
        return 1;
    }

    GLuint vertex_shader = ENGINE_NAME_create_vertex_shader("shaders/default.vert");
    GLuint fragment_shader = ENGINE_NAME_create_fragment_shader("shaders/default.frag");
    GLuint shader_program = ENGINE_NAME_create_shader_program(vertex_shader, fragment_shader);

    GLfloat vertices[] = {
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f
    };
    GLuint data[] = {3, 3, 2}; 
    GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);


    ENGINE_NAME_load_model(VAO, VBO, EBO, vertices, sizeof(vertices), data, sizeof(data), indices, sizeof(indices));


    GLuint texture = ENGINE_NAME_create_texture("textures/grass.jpg");

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    mat4x4 transform = identity_mat4x4;
    mat4x4_scale(transform, 0.62f, 1.2f, 1.0f);
    mat4x4_rotate(transform, 45.0f, 0.0f, 0.0f);
    mat4x4_translate(transform, 0.2f, 0.2f, 0.0f);
    mat4x4_transpose(transform);


    while (!glfwWindowShouldClose(ENGINE_NAME_window)) {
        glfwPollEvents();

        glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_2D, texture);

        glUseProgram(shader_program);

        GLuint loaction = glGetUniformLocation(shader_program, "transform");
        glUniformMatrix4fv(loaction, 1, GL_FALSE, begin_mat4x4(transform));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(ENGINE_NAME_window);
    }

    glDeleteTextures(1, &texture);

    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);

    glDeleteProgram(shader_program);

    ENGINE_NAME_exit();

    return 0;
}
