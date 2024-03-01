#include <stdio.h>
#include <string.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


extern GLuint EBO, VBO, VAO;
extern GLuint count;


void obj_load(char title[]) {
	FILE *file = fopen(title, "r");

	int vertices_count = 0;
	int normals_count = 0;
	int textures_count = 0;
	int polygons_count = 0;
	char c;

	while(1) {
		c = getc(file);
		// comments
		if (c == '#') {
			while (getc(file) != '\n') {}
		// mtl files names
		} else if (c == 'm') {
			while (getc(file) != '\n') {}
		// name of model
		} else if (c == 'o') {
			while (getc(file) != '\n') {}
		} else if (c == 'v') {
			c = getc(file);
			// coords of vertices 
			if (c == ' ') {
				++vertices_count;
				while (getc(file) != '\n') {}
			// coords of normals
			} else if (c == 'n') {
				++normals_count;
				while (getc(file) != '\n') {}
			// coords of textures 
			} else if (c == 't') {
				++textures_count;
				while (getc(file) != '\n') {}			
			}
		// i dont know
		} else if (c == 's') {
			while (getc(file) != '\n') {}
		// what mtl style to use
		} else if (c == 'u') {
			while (getc(file) != '\n') {}
		// numbers of coordinates, textures and normals what to use for polygon
		} else if (c == 'f') {
			++polygons_count;
			while (getc(file) != '\n') {}
		} else {break;}
	}

	rewind(file);

	GLfloat verts[vertices_count * 3];
	GLfloat norms[normals_count * 3];
	GLfloat texs[textures_count * 2];
	GLuint polygons_verts[polygons_count * 3];
	GLuint polygons_norms[polygons_count * 3];
	GLuint polygons_texs[polygons_count * 3];

	int vertices_index = 0;
	int normals_index = 0;
	int textures_index = 0;
	int polygons_index = 0;

	while(1) {
		c = getc(file);
		if (c == '#') {
			while (getc(file) != '\n') {}
		} else if (c == 'm') {
			while (getc(file) != '\n') {}
		} else if (c == 'o') {
			while (getc(file) != '\n') {}
		} else if (c == 'v') {
			c = getc(file);
			if (c == ' ') {
				for (int i = 0; i < 3; ++i) {
					fscanf(file, "%f", &verts[vertices_index * 3 + i]);
				}
				++vertices_index;
				while (getc(file) != '\n') {}
			} else if (c == 'n') {
				for (int i = 0; i < 3; ++i) {
					fscanf(file, "%f", &norms[normals_index * 3 + i]);
				}
				++normals_index;
				while (getc(file) != '\n') {}
			} else if (c == 't') {
				for (int i = 0; i < 2; ++i) {
					fscanf(file, "%f", &texs[textures_index * 2 + i]);
				}
				++textures_index;
				while (getc(file) != '\n') {}
			}
		} else if (c == 's') {
			while (getc(file) != '\n') {}
		} else if (c == 'u') {
			while (getc(file) != '\n') {}
		} else if (c == 'f') {
			for (int i = 0; i < 3; ++i) {
				fscanf(file, "%u", &polygons_verts[polygons_index * 3 + i]);
				getc(file);
				fscanf(file, "%u", &polygons_texs[polygons_index * 3 + i]);
				getc(file);
				fscanf(file, "%u", &polygons_norms[polygons_index * 3 + i]);
			}
			++polygons_index;
			while (getc(file) != '\n') {}
		} else {break;}
	}

	fclose(file);

	
    gladLoadGL();

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(polygons_verts), polygons_verts, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    count = polygons_index * 3;
}