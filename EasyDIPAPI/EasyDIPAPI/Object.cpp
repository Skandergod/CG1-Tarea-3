#include "Object.h"
#include "shaders/Shader.h"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/transform2.hpp"
//static Object* instance;
//static unsigned int VBO, VAO, EBO;

//Object* Object::instance = nullptr;
unsigned int Object::VBO = 0;
unsigned int Object::VAO = 0;


Object::Object() {
	scale = glm::vec3(1.0f);
	translate = glm::vec3(0.0f);
	rotate = glm::vec3(0.0f);
	Rotation(rotate);
	Scale(scale);
	Translation(translate);
	modelMatrix();
}

Object::~Object() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Object::Bind()
{
	glBindVertexArray(VAO);
}

void Object::Init() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertex.size(), &vertex[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	//Shader::setMat4("MatrixView", matrixView);
	glBindVertexArray(0);
	glEnable(GL_LINE_SMOOTH);
	
}
void Object::Draw()
{
	//glEnable(GL_DEPTH_TEST);
	glDrawArrays(GL_TRIANGLES, 0, vertex.size());
}

void Object::DrawLines() {
	glDrawArrays(GL_LINES, 0, vertex.size());
}

void Object::DrawPoints() {
	glPointSize(4.0f);
	glDrawArrays(GL_POINTS, 0, vertex.size());
}

void Object::Rotation(glm::vec3 t) {
	rotate = t;
	rotateMatrix = glm::mat4(1.0f);
	rotateMatrix = glm::rotate(rotateMatrix, t.x, glm::vec3(1, 0, 0));
	rotateMatrix = glm::rotate(rotateMatrix, t.y, glm::vec3(0, 1, 0));
	rotateMatrix = glm::rotate(rotateMatrix, t.z, glm::vec3(0, 0, 1));
}

void Object::Scale(glm::vec3 t) {
	scale = t;
	scaleMatrix = glm::scale(t);
}

void Object::Translation(glm::vec3 t) {
	translate = t;
	translateMatrix = glm::translate(t);
}

void Object::modelMatrix() {

	matrixModel = rotateMatrix * scaleMatrix * translateMatrix;

}