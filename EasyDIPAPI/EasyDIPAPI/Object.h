#pragma once

#include <glad/glad.h>


class Object {
	//static Object* instance;
	
public:
	int** vertex;
	static unsigned int VBO, VAO;
	Object();
	~Object();
	void Draw();
	void Bind();
	//void Object();
	//static Object* Instance();
};



