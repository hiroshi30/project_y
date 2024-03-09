#include <ENGINE_NAME.h>

#include <stdio.h>
#include <math.h>


int main(void) {
    const GLuint window_width = 500;
    const GLuint window_height = 500;

   	if (ENGINE_NAME_init(window_width, window_height, "project_y") != 0) {
        return 1;
    }

    GLuint vertex_shader = ENGINE_NAME_create_vertex_shader("shaders/default.vert");
    GLuint fragment_shader = ENGINE_NAME_create_fragment_shader("shaders/default.frag");
    GLuint shader_program = ENGINE_NAME_create_shader_program(vertex_shader, fragment_shader);

    GLfloat vbo_data[] = {
        -0.5f,  0.5f,  0.5f,    0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,    1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,    1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,

         0.5f,  0.5f, -0.5f,    0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,    1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,    1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,    0.0f, 1.0f
    };
    GLuint data[] = {3, 2}; 
    GLuint indices[] = {
        0, 1, 3,
        1, 3, 2,

        5, 4, 6,
        4, 6, 7,
        
        5, 4, 0,
        4, 0, 1,

        6, 7, 3,
        7, 3, 2,

        1, 4, 2,
        4, 2, 7,

        5, 0, 6,
        0, 6, 3
    };

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    ENGINE_NAME_load_model(VAO, VBO, EBO, vbo_data, sizeof(vbo_data), data, sizeof(data), indices, sizeof(indices));

    GLuint texture = ENGINE_NAME_create_texture("textures/container.jpg");

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    mat4x4 projection;
    mat4x4_perspective_projection(projection, 45.0f, (GLfloat)window_width / (GLfloat)window_height, 0.1f, 100.0f);

    GLfloat translate[] = {
         0.0f,  0.5f, 0.0f,
        -2.5f, -2.5f, 0.0f,
        -2.5f,  2.5f, 0.0f,
         2.5f, -2.5f, 0.0f,
         2.5f,  2.5f, 0.0f
    };

    while (!glfwWindowShouldClose(ENGINE_NAME_window)) {
        glfwPollEvents();

        glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_2D, texture);

        glUseProgram(shader_program);

        GLfloat radius = 13.0f;
        GLfloat camX = sin(glfwGetTime()) * radius;
        GLfloat camZ = cos(glfwGetTime()) * radius;

        mat4x4 view;
        mat4x4_look_at(view,
            camX, 0.0f, camZ,
            0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f
        );

        GLint view_location = glGetUniformLocation(shader_program, "view");
        glUniformMatrix4fv(view_location, 1, GL_TRUE, begin_mat4x4(view));

        GLint projection_location = glGetUniformLocation(shader_program, "projection");
        glUniformMatrix4fv(projection_location, 1, GL_TRUE, begin_mat4x4(projection));

        GLint model_location = glGetUniformLocation(shader_program, "model");

        for (GLuint i = 0; i < 5; ++i) {
            mat4x4 model = identity_mat4x4;
            mat4x4_translate(model, translate[i * 3], translate[i * 3 + 1], translate[i * 3 + 2]);
            mat4x4_rotate(model, (GLfloat)glfwGetTime() * 30.0f * i, (GLfloat)glfwGetTime() * 40.0f * i, 0.0f);
            glUniformMatrix4fv(model_location, 1, GL_TRUE, begin_mat4x4(model));

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }

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
