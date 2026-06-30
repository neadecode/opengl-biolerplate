#pragma once
#include <glad/glad.h>
#include <string>

std::string getSource(char const* src);

class Shader {
public:
	GLuint id;
	Shader(char const* frag, char const* vert);

	void Use() const {
		glUseProgram(id);
	}

	void Delete() const {
		glDeleteProgram(id);	
	}
	static inline char error_buf[512];
	static inline int success;
};
