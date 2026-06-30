#pragma once
#include <glad/glad.h>

class VBO {
public:
	GLuint id;
	//Binds it
	VBO(const float* const vertices, size_t size) {
		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	void Bind()   const { 
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}
	void Unbind() const { 
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void Delete() const { 
		glDeleteBuffers(1, &id);
	}
};