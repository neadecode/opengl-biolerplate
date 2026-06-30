#pragma once
#include <glad/glad.h>
#include "vbo.h"

class VAO {
public:
	GLuint id;
	VAO() {
		glGenVertexArrays(1, &id);
		Bind();
	}
	//Defaulted to GL_FLOAT
	void LinkVBO(VBO vbo, GLuint attrIndex, GLuint size, size_t stride, size_t offset) {
		vbo.Bind();
		//index, size, type, normalized, stride, pointer
		glVertexAttribPointer(attrIndex, size, GL_FLOAT, GL_FALSE, (GLsizei)stride, (void*)offset);
		glEnableVertexAttribArray(attrIndex);
		vbo.Unbind();	
	}
	void Bind() {
		glBindVertexArray(id);
	}
	void Unbind() {
		glBindVertexArray(0);
	}
	void Delete() {
		glDeleteVertexArrays(1, &id);
	}
};