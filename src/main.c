#include <ENGINE_NAME.h>

#include <stdio.h>
#include <math.h>


int main(void) {
    const GLuint window_width = 800;
    const GLuint window_height = 600;

   	if (ENGINE_NAME_init(window_width, window_height, "project_y") != 0) {
        return 1;
    }

    GLuint vertex_shader = ENGINE_NAME_create_vertex_shader("shaders/phong_light.vert");
    GLuint fragment_shader = ENGINE_NAME_create_fragment_shader("shaders/phong_light.frag");
    GLuint shader_program = ENGINE_NAME_create_shader_program(vertex_shader, fragment_shader);

    GLuint light_vertex_shader = ENGINE_NAME_create_vertex_shader("shaders/light.vert");
    GLuint light_fragment_shader = ENGINE_NAME_create_fragment_shader("shaders/light.frag");
    GLuint light_shader_program = ENGINE_NAME_create_shader_program(light_vertex_shader, light_fragment_shader);

    GLfloat vbo_data[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vbo_data), vbo_data, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    GLuint light_VAO;
    glGenVertexArrays(1, &light_VAO);

    glBindVertexArray(light_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    Camera camera;
    Camera_construct(&camera,
        0.0f, 0.0f, 3.0f,       // vec3 position
        0.0f, 1.0f, 0.0f,       // vec3 world_up
        5.0f, 0.09f, 90.0f,     // movement_speed, sensitivity
        -90.0f, 0.0f            // yaw (x), pitch (y)
    );

    mat4x4 projection;
    
    mat4x4 object_model = mat4x4_identity;

    GLfloat delta_time;
    GLfloat previous_time = glfwGetTime();
    GLfloat current_time;

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while (!glfwWindowShouldClose(ENGINE_NAME_window)) {
        current_time = glfwGetTime();
        delta_time = current_time - previous_time;
        previous_time = current_time;
        
        glfwPollEvents();
        Camera_move(&camera, delta_time);
        Camera_look(&camera);
        Camera_scroll(&camera);
        Camera_look_at(&camera);

        mat4x4_perspective_projection(projection, camera.FOV, (GLfloat)window_width / (GLfloat)window_height, 0.1f, 100.0f);

        mat4x4 light_model = mat4x4_identity;
        mat4x4_translate(light_model, 2.0f * cos(glfwGetTime()), 1.0f, -2.0f * sin(glfwGetTime()));
        mat4x4_scale(light_model, 0.2f, 0.2f, 0.2f);


        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glUseProgram(shader_program);

        GLint view_location = glGetUniformLocation(shader_program, "view");
        glUniformMatrix4fv(view_location, 1, GL_TRUE, mat4x4_begin(camera.view));

        GLint projection_location = glGetUniformLocation(shader_program, "projection");
        glUniformMatrix4fv(projection_location, 1, GL_TRUE, mat4x4_begin(projection));

        GLint model_location = glGetUniformLocation(shader_program, "model");
        glUniformMatrix4fv(model_location, 1, GL_TRUE, mat4x4_begin(object_model));

        GLint object_color_location = glGetUniformLocation(shader_program, "object_color");
        glUniform3f(object_color_location, 1.0f, 0.5f, 0.31f);

        GLint light_color_location = glGetUniformLocation(shader_program, "light_color");
        glUniform3f(light_color_location,  1.0f, 1.0f, 1.0f);
        
        GLint light_position_location = glGetUniformLocation(shader_program, "light_position");
        glUniform3f(light_position_location, light_model[0][3], light_model[1][3], light_model[2][3]);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);


        glUseProgram(light_shader_program);

        view_location = glGetUniformLocation(light_shader_program, "view");
        glUniformMatrix4fv(view_location, 1, GL_TRUE, mat4x4_begin(camera.view));

        projection_location = glGetUniformLocation(light_shader_program, "projection");
        glUniformMatrix4fv(projection_location, 1, GL_TRUE, mat4x4_begin(projection));

        model_location = glGetUniformLocation(light_shader_program, "model");
        glUniformMatrix4fv(model_location, 1, GL_TRUE, mat4x4_begin(light_model));

        glBindVertexArray(light_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);


        glfwSwapBuffers(ENGINE_NAME_window);
    }

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &light_VAO);

    glDeleteProgram(shader_program);
    glDeleteProgram(light_shader_program);

    ENGINE_NAME_exit();

    return 0;
}
