#include <engine.h>

#include <stdio.h>
#include <math.h>


int main(void) {
   	if (engine_init(500, 250, "project_y") != 0) {
        return 1;
    }

    // GLint nr_atr;
    // glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nr_atr);
    // printf("!!! %d !!!\n", nr_atr);

    GLuint vertex_shader = create_vertex_shader("C:/Users/hiroshi/Desktop/project_y/shaders/default.vert");
    GLuint fragment_shader = create_fragment_shader("C:/Users/hiroshi/Desktop/project_y/shaders/default.frag");
    GLuint shader_program = create_shader_program(vertex_shader, fragment_shader);

    GLfloat vertices[] = {
         0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f
    };
    
    GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    GLuint length = sizeof(indices) / sizeof(GLuint);

    GLfloat texture_coords[] = {
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f
    };


    GLuint EBO;
    GLuint VBO;
    GLuint VAO;

    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_program);

        GLfloat multiplier = (1 + sin(glfwGetTime())) / 2;
        GLuint location = glGetUniformLocation(shader_program, "multiplier");
        glUniform1f(location, multiplier);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, length, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);

    glDeleteProgram(shader_program);

    engine_exit();

    return 0;
}
