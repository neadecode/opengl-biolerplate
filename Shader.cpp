#include "Shader.h"
#include <fstream>
#include <string.h>
#include <iostream>

std::string getSource(char const* src) {
	std::ifstream file{ src, std::ios::binary };

	return std::string{
		std::istreambuf_iterator<char>(file),
		std::istreambuf_iterator<char>()
	};
}


Shader::Shader(char const* frag, char const* vert) {
	std::string fSrc = getSource(frag);
	std::string vSrc = getSource(vert);
	
	//GL freaks out because it needs a pointer to pointer.
	GLchar const* gl_fSrc = fSrc.c_str();
	GLchar const* gl_vSrc = vSrc.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &gl_vSrc, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, sizeof(error_buf) / sizeof(char), NULL, error_buf);
		std::cout <<
			"ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << error_buf << std::endl;
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &gl_fSrc, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, sizeof(error_buf) / sizeof(char), NULL, error_buf);
		std::cout <<
			"ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << error_buf << std::endl;
	}

	id = glCreateProgram();
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	glLinkProgram(id);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}