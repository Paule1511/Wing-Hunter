#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Wing-Utils.h"

renderEngine::renderEngine(const char* titel, uint16_t width, uint16_t heigth) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(width, heigth, titel, NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to Create Window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "couldnt load GLAD" << std::endl;
		return;
	}
	glViewport(0, 0, width, heigth);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	while (!glfwWindowShouldClose(window)) {
		glfwSwapBuffers(window);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();
	}
	glfwTerminate();
}

//https://learnopengl.com/Getting-started/Hello-Triangle lern material