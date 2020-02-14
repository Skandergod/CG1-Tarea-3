#include "Object.h"
//static Object* instance;
//static unsigned int VBO, VAO, EBO;

//Object* Object::instance = nullptr;
unsigned int Object::VBO = 0;
unsigned int Object::VAO = 0;


Object::Object() {
	const float sz = 0.5f;
	float ObjectVertices[] = {
		// positions        	// texture Coords
		-sz,sz,
		sz, sz,
		-sz,-sz,
		sz,-sz,
	};

	// setup plane VAO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ObjectVertices), &ObjectVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
	glBindVertexArray(0);

}

Object::~Object() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Object::Bind()
{
	glBindVertexArray(VAO);
}

void Object::Draw()
{
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

