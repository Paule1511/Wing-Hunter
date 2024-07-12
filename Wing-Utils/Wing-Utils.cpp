#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Wing-Utils.h"
#include <chrono>
#include "Wing-Shapes.h"

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
//PAUSED. DESCISION BETWEEN OPENGL AND VULKAN IS GETTIN

//--------------PAUL------------

static unsigned int createShaderProgram(const char* vertexFileName, const char* fragmentFileName) {
	std::string vertexFilePath = VERTEX_SHADERS_PATH + vertexFileName;
	std::string fragmentFilePath = FRAGMENT_SHADERS_PATH + fragmentFileName;
	std::vector<unsigned int> shaderModules;

	shaderModules.push_back(createShaderModule(vertexFilePath, GL_VERTEX_SHADER)); 
	shaderModules.push_back(createShaderModule(fragmentFilePath, GL_FRAGMENT_SHADER));

	unsigned int shaderProgram = glCreateProgram();
	for (int i = 0; i < shaderModules.size(); i++) {
		glAttachShader(shaderProgram, shaderModules[i]);
	}

	glLinkProgram(shaderProgram);

	for (int i = 0; i < shaderModules.size(); i++) {
		glDeleteShader(shaderModules[i]);
	}

	int shaderRes;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &shaderRes);
	if (!shaderRes) {
		char err[1024];
		glGetProgramInfoLog(shaderProgram, 1024, NULL, err);
		std::cout << "Failed to Compile Shader. ERROR:\n" << err << std::endl;
	}
	else {
		std::cout << "Shader Successfully created" << std::endl;
	}

	return shaderProgram;
}


static unsigned int createShaderModule(std::string filePath, unsigned int moduleType) {
	std::ifstream file;
	std::string fileString;
	std::string line;

	file.open(filePath);
	while (std::getline(file, line)) {
		fileString += line + "\n";
	}
	file.close();

	const char* shaderSource = fileString.c_str();
	unsigned int shaderModule = glCreateShader(moduleType);

	glShaderSource(shaderModule, 1, &shaderSource, NULL);
	glCompileShader(shaderModule);

	int compResult;
	glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &compResult);
	if (!compResult) {
		char err[1024];
		glGetShaderInfoLog(shaderModule, 1024, NULL, err);
		std::cout << "Failed to Compile Shader. ERROR:\n" << err << std::endl;
	}

	return shaderModule;
}

static GLFWwindow* createGLFWWindowGL(const char* titel, uint16_t width, uint16_t heigth) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, heigth, titel, NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to Create Window." << std::endl;
		glfwTerminate();
		return NULL;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to load GLAD." << std::endl;
		glfwTerminate();
		return NULL;
	}

	return window;
}

static double getTime() {
	auto duration = std::chrono::system_clock::now().time_since_epoch();
	double time = (double)std::chrono::duration_cast<std::chrono::microseconds>(duration).count() / 1000;
	return time;
}

void renderEngine::drawShapeArray(std::vector<Poly> Shapes) {
	int width;
	int height;
	std::vector<float> vertices;
	std::vector<float> colors;

	glfwGetFramebufferSize(window, &width, &height);

	for (int i = 0; i < Shapes.size(); i++) {
		std::vector<Coords> ShapeCoords = Shapes[i].getVertexCoords();
		for (int j = 0; j < ShapeCoords.size(); j++) {
			float x = 2.0f/width*ShapeCoords[j].x - 1;
			float y = 2.0f/height*(height-ShapeCoords[j].y) - 1;
			float z = 2.0f/1000*ShapeCoords[j].z;
			//std::cout << x << " " << y << " " << z << std::endl;
			vertices.insert(vertices.end(), {x, y, z});
		}
	}

	for (int i = 0; i < Shapes.size(); i++) {
		std::vector<RGBA> ShapeColors = Shapes[i].getVertexColors();
		for (int j = 0; j < ShapeColors.size(); j++) {
			float r = (float) ShapeColors[j].r / 255;
			float g = (float) ShapeColors[j].g / 255;
			float b = (float) ShapeColors[j].b / 255;
			float a = (float) ShapeColors[j].a / 255;
			//std::cout << r << " " << g << " " << b << std::endl;
			colors.insert(colors.end(), {r, g, b, a});
		}
	}

	glBindVertexArray(VAO);

	//POSITIONS
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//COLORS
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(float), colors.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	//DRAW

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

void renderEngine::initGPUBuffers() {

	glGenVertexArrays(1, &VAO);
	VBOs.resize(2);
	glGenBuffers(2, VBOs.data());
}

renderEngine::renderEngine(const char* titel, uint16_t width, uint16_t heigth) {


	window = createGLFWWindowGL(titel, width, heigth);

	unsigned int shader = createShaderProgram("defaultVert.txt", "defaultFrag.txt");

	initGPUBuffers();
	std::vector<Poly> testShapeVector = createTestShapes();
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	while (!glfwWindowShouldClose(window)) {
		double start = getTime();
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shader);
		drawShapeArray(testShapeVector);
		glfwSwapBuffers(window);
		std::cout << "FPS: " << 1000 / (getTime() - start) << std::endl;
	}
	glfwTerminate();
}

static std::vector<Poly> createTestShapes() {
	std::vector<Poly> shapes{};
	Vertex vert1 = Vertex(Coords{ 500, 250, 0 }, RGBA{ 255,0,0,255 });
	Vertex vert2 = Vertex(Coords{ 250, 500, 0 }, RGBA{ 0,255,0,255 });
	Vertex vert3 = Vertex(Coords{ 750, 500, 0 }, RGBA{ 0,0,255,255 });
	//Vertex vert4 = Vertex(Coords{ 1000, 500, 0 }, RGBA{ 0,0,255,255 });
	//shapes.push_back(Poly({ vert1, vert2, vert3, vert4}));
	shapes.push_back(Poly({ vert1, vert2, vert3}));
	return shapes;
}

//https://learnopengl.com/Getting-started/Hello-Triangle Learn Material for OPENGL.
