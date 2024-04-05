#include <math.h>

#include <all.h>


int main(void) {
    const GLuint window_width = 800;
    const GLuint window_height = 600;

   	if (engine_init(window_width, window_height, "project_y") != 0) {
        return 1;
    }

    GLuint vertex_shader = shader_create_vertex("shaders/default.vert");
    GLuint fragment_shader = shader_create_fragment("shaders/default.frag");
    GLuint shader_program = shader_create_shader_program(vertex_shader, fragment_shader);

    GLuint light_vertex_shader = shader_create_vertex("shaders/light.vert");
    GLuint light_fragment_shader = shader_create_fragment("shaders/light.frag");
    GLuint light_shader_program = shader_create_shader_program(light_vertex_shader, light_fragment_shader);

    GLfloat vbo_data[] = {
        -0.5, -0.5, -0.5,  0,  0, -1,
         0.5, -0.5, -0.5,  0,  0, -1, 
         0.5,  0.5, -0.5,  0,  0, -1, 
         0.5,  0.5, -0.5,  0,  0, -1, 
        -0.5,  0.5, -0.5,  0,  0, -1, 
        -0.5, -0.5, -0.5,  0,  0, -1, 

        -0.5, -0.5,  0.5,  0,  0, 1,
         0.5, -0.5,  0.5,  0,  0, 1,
         0.5,  0.5,  0.5,  0,  0, 1,
         0.5,  0.5,  0.5,  0,  0, 1,
        -0.5,  0.5,  0.5,  0,  0, 1,
        -0.5, -0.5,  0.5,  0,  0, 1,

        -0.5,  0.5,  0.5, -1,  0,  0,
        -0.5,  0.5, -0.5, -1,  0,  0,
        -0.5, -0.5, -0.5, -1,  0,  0,
        -0.5, -0.5, -0.5, -1,  0,  0,
        -0.5, -0.5,  0.5, -1,  0,  0,
        -0.5,  0.5,  0.5, -1,  0,  0,

         0.5,  0.5,  0.5,  1,  0,  0,
         0.5,  0.5, -0.5,  1,  0,  0,
         0.5, -0.5, -0.5,  1,  0,  0,
         0.5, -0.5, -0.5,  1,  0,  0,
         0.5, -0.5,  0.5,  1,  0,  0,
         0.5,  0.5,  0.5,  1,  0,  0,

        -0.5, -0.5, -0.5,  0, -1,  0,
         0.5, -0.5, -0.5,  0, -1,  0,
         0.5, -0.5,  0.5,  0, -1,  0,
         0.5, -0.5,  0.5,  0, -1,  0,
        -0.5, -0.5,  0.5,  0, -1,  0,
        -0.5, -0.5, -0.5,  0, -1,  0,

        -0.5,  0.5, -0.5,  0,  1,  0,
         0.5,  0.5, -0.5,  0,  1,  0,
         0.5,  0.5,  0.5,  0,  1,  0,
         0.5,  0.5,  0.5,  0,  1,  0,
        -0.5,  0.5,  0.5,  0,  1,  0,
        -0.5,  0.5, -0.5,  0,  1,  0
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
        0, 0, 10,   // vec3 position
        0, 1, 0,    // vec3 world_up
        7, 0.09,    // movement_speed, sensitivity
        30, 90,     // min_FOV, max_FOV
        -90, 0      // yaw (x), pitch (y)
    );

    mat4x4 projection;
    
    mat4x4 object_models[15];
    for (int i = 0; i < 15; ++i) {
        mat4x4_make_identity(object_models[i]);
        mat4x4_translate(object_models[i], random(-5, 5), random(-5, 5), random(-5, 5));
        mat4x4_rotate(object_models[i], random(-90, 90), random(-90, 90), random(-90, 90));
    }

    GLfloat delta_time;
    GLfloat previous_time = glfwGetTime();
    GLfloat current_time;

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while (!glfwWindowShouldClose(engine_window)) {
        current_time = glfwGetTime();
        delta_time = current_time - previous_time;
        previous_time = current_time;
        
        glfwPollEvents();
        Camera_move(&camera, delta_time);
        Camera_look(&camera);
        Camera_scroll(&camera);
        Camera_look_at(&camera);

        mat4x4_perspective_projection(projection, camera.FOV, (GLfloat)window_width / (GLfloat)window_height, 0.1, 100);

        mat4x4 light_model = mat4x4_identity;
        mat4x4_translate(light_model, 7 * cos(glfwGetTime()), 1, -7 * sin(glfwGetTime()));
        mat4x4_scale(light_model, 0.2, 0.2, 0.2);


        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glUseProgram(shader_program);

        GLint view_location = glGetUniformLocation(shader_program, "view");
        glUniformMatrix4fv(view_location, 1, GL_TRUE, mat4x4_begin(camera.view));

        GLint projection_location = glGetUniformLocation(shader_program, "projection");
        glUniformMatrix4fv(projection_location, 1, GL_TRUE, mat4x4_begin(projection));

        GLint object_color_location = glGetUniformLocation(shader_program, "object_color");
        glUniform3f(object_color_location, 1, 0.5, 0.31);

        GLint light_color_location = glGetUniformLocation(shader_program, "light_color");
        glUniform3f(light_color_location,  1, 1, 1);
        
        GLint light_position_location = glGetUniformLocation(shader_program, "light_position");
        glUniform3f(light_position_location, light_model[0][3], light_model[1][3], light_model[2][3]);

        GLint model_location = glGetUniformLocation(shader_program, "model");
        for (int i = 0; i < 15; ++i) {
            glUniformMatrix4fv(model_location, 1, GL_TRUE, mat4x4_begin(object_models[i]));

            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glBindVertexArray(0);
        }


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


        glfwSwapBuffers(engine_window);
    }

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &light_VAO);

    glDeleteProgram(shader_program);
    glDeleteProgram(light_shader_program);

    engine_exit();

    return 0;
}
