#include <ENGINE_NAME.h>


void movement(vec3 camera_position, vec3 camera_front, vec3 world_up) {
    GLfloat camera_speed = 0.05f;
    vec3 temp;
    
    if (keys[GLFW_KEY_W]) {
        vec3_multiplication_scalar(camera_front, camera_speed, temp);
        vec3_addition(camera_position, temp, camera_position);
    }

    if (keys[GLFW_KEY_S]) {
        vec3_multiplication_scalar(camera_front, camera_speed, temp);
        vec3_subtraction(camera_position, temp, camera_position);
    }

    if (keys[GLFW_KEY_A]) {
        vec3_cross(camera_front, world_up, temp);
        vec3_normalize(temp);
        vec3_multiplication_scalar(temp, camera_speed, temp);
        vec3_subtraction(camera_position, temp, camera_position);
    }

    if (keys[GLFW_KEY_D]) {
        vec3_cross(camera_front, world_up, temp);
        vec3_normalize(temp);
        vec3_multiplication_scalar(temp, camera_speed, temp);
        vec3_addition(camera_position, temp, camera_position);
    }
}


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

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);e


    vec3 camera_position = {0.0f, 0.0f, 3.0f};
    vec3 camera_front = {0.0f, 0.0f, -1.0f};
    vec3 world_up = {0.0f, 1.0f, 0.0f};


    mat4x4 projection;
    mat4x4_perspective_projection(projection, 45.0f, (GLfloat)window_width / (GLfloat)window_height, 0.1f, 100.0f);

    vec3 cube_positions[10];
    vec3_make(cube_positions[0],  0.0f,  0.0f,  0.0f);
    vec3_make(cube_positions[1],  2.0f,  5.0f, -15.0f);
    vec3_make(cube_positions[2], -1.5f, -2.2f, -2.5f);
    vec3_make(cube_positions[3], -3.8f, -2.0f, -12.3f);
    vec3_make(cube_positions[4],  2.4f, -0.4f, -3.5f);
    vec3_make(cube_positions[5], -1.7f,  3.0f, -7.5f);
    vec3_make(cube_positions[6],  1.3f, -2.0f, -2.5f);
    vec3_make(cube_positions[7],  1.5f,  2.0f, -2.5f);
    vec3_make(cube_positions[8],  1.5f,  0.2f, -1.5f);
    vec3_make(cube_positions[9], -1.3f,  1.0f, -1.5f);

    GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;
    GLfloat current_time;

    while (!glfwWindowShouldClose(ENGINE_NAME_window)) {
        glfwPollEvents();
        movement(camera_position, camera_front, world_up);

        glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_2D, texture);

        glUseProgram(shader_program);

        mat4x4 view;
        mat4x4_look_at(view, camera_position, camera_front, world_up);

        GLint view_location = glGetUniformLocation(shader_program, "view");
        glUniformMatrix4fv(view_location, 1, GL_TRUE, mat4x4_begin(view));

        GLint projection_location = glGetUniformLocation(shader_program, "projection");
        glUniformMatrix4fv(projection_location, 1, GL_TRUE, mat4x4_begin(projection));

        GLint model_location = glGetUniformLocation(shader_program, "model");

        glBindVertexArray(VAO);
        for (GLuint i = 0; i < 10; ++i) {
            mat4x4 model = identity_mat4x4;
            mat4x4_translate(model, cube_positions[i][0], cube_positions[i][1], cube_positions[i][2]);
            // mat4x4_rotate(model, (GLfloat)glfwGetTime() * 30.0f * i, (GLfloat)glfwGetTime() * 40.0f * i, 0.0f);

            glUniformMatrix4fv(model_location, 1, GL_TRUE, mat4x4_begin(model));

            glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
        }
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
