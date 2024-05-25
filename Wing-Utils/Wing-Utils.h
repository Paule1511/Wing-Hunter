#pragma once
#include <stdint.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include "Wing-Shapes.h"

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
//AKTUELL UNDER ENTWICKLUNG.
//NICHTS BERÜHREN AUSSER AUSDRÜCKLICHE ERLAUBNIS VON PAUL
//KOMMENTIEREN ERLAUBT. BEI FRAGEN AN PAUL WENDEN
//
//--------------PAUL------------

const std::string RESOURCE_PATH = "../resources/";
const std::string SHADERS_PATH = "../resources/shaders";
const std::string FRAGMENT_SHADERS_PATH = "../resources/shaders/fragment/";
const std::string VERTEX_SHADERS_PATH = "../resources/shaders/vertex/";

class renderEngine {
private:
	GLFWwindow* window;
	void drawShapeArray(std::vector<Poly> Shapes);
	int renderDist;
	unsigned int VAO;
	std::vector<unsigned int> VBOs;
	void initGPUBuffers();
public:
	renderEngine(const char* titel, uint16_t width, uint16_t heigth);
};

static std::vector<Poly> createTestShapes();

static unsigned int createShaderProgram(const char* filePathVertex, const char* filePathFragment);

static unsigned int createShaderModule(std::string filePath, unsigned int moduleType);

static GLFWwindow* createGLFWWindowGL(const char* titel, uint16_t width, uint16_t heigth);