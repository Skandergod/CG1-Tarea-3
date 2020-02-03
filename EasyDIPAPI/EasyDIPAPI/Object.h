#pragma once

#include <glad/glad.h>


class Object {
	static Object* instance;
	int **vertex;
	static unsigned int VBO, VAO;
	Object();
	~Object();
public:
	void Draw();
	void Bind();
	static Object* Instance();
};



