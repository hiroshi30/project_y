#include <ENGINE_NAME.h>

#include <stdio.h>


int main(void) {
   	if (ENGINE_NAMEInit(500, 250, "project_y") != 0) {
        return 1;
    }

    GLuint vertex_shader = ENGINE_NAMECreateVertexShader("shaders/default.vert");
    GLuint fragment_shader = ENGINE_NAMECreateFragmentShader("shaders/default.frag");
    GLuint shader_program = ENGINE_NAMECreateShaderProgram(vertex_shader, fragment_shader);

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


    ENGINE_NAMELoadModel(VAO, VBO, EBO, vertices, sizeof(vertices), data, sizeof(data), indices, sizeof(indices));


    GLuint texture = ENGINE_NAMECreateTexture("textures/grass.jpg");

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    GLfloat mat4x4[4][4] = {
        {1, 0, 0, 0.2},
        {0, 1, 0, 0.2},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    while (!glfwWindowShouldClose(ENGINE_NAMEWindow)) {
        glfwPollEvents();

        glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_2D, texture);

        glUseProgram(shader_program);

        GLuint loaction = glGetUniformLocation(shader_program, "transform");
        glUniformMatrix4fv(loaction, 1, GL_FALSE, &mat4x4[0][0]);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(ENGINE_NAMEWindow);
    }

    glDeleteTextures(1, &texture);

    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);

    glDeleteProgram(shader_program);

    ENGINE_NAMEExit();

    return 0;
}
