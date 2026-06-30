#pragma once
#include <glad/glad.h>

class EBO {
public:
	GLuint id;
	EBO(const GLuint* const indices, size_t size) {
		glGenBuffers(1, &id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	}

	void Bind()   const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	}
	void Unbind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	void Delete() const {
		glDeleteBuffers(1, &id);
	}

};