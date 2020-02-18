#pragma once

#include "EDpch.h"
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>



class Object {
	//static Object* instance;
	
public:
	glm::vec3 scale;
	glm::vec3 rotate;
	glm::vec3 translate;
	glm::mat4 rotateMatrix;
	glm::mat4 scaleMatrix;
	glm::mat4 translateMatrix;
	glm::mat4 matrixModel;
	std::vector<glm::vec3> vertex;
	static unsigned int VBO, VAO;
	Object();
	~Object();
	void Draw();
	void Bind();
	void Init();
	void Rotation(glm::vec3 t);
	void Translation(glm::vec3 t);
	void Scale(glm::vec3 t);
	void modelMatrix();
	void DrawLines();
	void DrawPoints();
	//void Object();
	//static Object* Instance();
};



