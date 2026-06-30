#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream> 
#include <fstream>

#include "Shader.h"
#include "vbo.h"
#include "ebo.h"
#include "vao.h"

int main(void) {
    if (!glfwInit()) { return -1; }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    float vertices[]{
        0.5f, 0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
    };

    unsigned int indices[]{ 0, 1, 2,  0, 2, 3 };

    GLFWwindow* window = glfwCreateWindow(800, 600, "Window", NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, 800, 600);

    Shader shader{ "default.frag", "default.vert" };
    VAO vao;
    VBO vbo{ vertices, sizeof(vertices) };
    EBO ebo{ indices, sizeof(indices) };
    vao.LinkVBO(vbo, 0, 3, sizeof(float) * 3, 0); 

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Use();
        vao.Bind();
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    vao.Delete();
    vbo.Delete();
    ebo.Delete();
    shader.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
}