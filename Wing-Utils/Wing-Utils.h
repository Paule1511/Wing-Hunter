#pragma once
#include <stdint.h>
#include <GLFW/glfw3.h>
class renderEngine {
private:
	GLFWwindow* window;
public:
	renderEngine(const char* titel, uint16_t width, uint16_t heigth);
};