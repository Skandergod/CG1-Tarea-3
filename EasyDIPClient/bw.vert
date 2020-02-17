#version 330 core

layout (location = 0) in vec3 pos;
uniform mat4 modelMatrix;
uniform mat4 rotMat;
uniform mat4 transMat;
uniform mat4 scaleMat;
void main()
{
	gl_Position =  transMat * scaleMat * rotMat* vec4(pos, 1.0f);
}