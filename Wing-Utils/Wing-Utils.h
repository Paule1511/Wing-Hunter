#pragma once
#include <stdint.h>
#include <GLFW/glfw3.h>

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
//AKTUELL UNDER ENTWICKLUNG.
//NICHTS BERÜHREN AUSSER AUSDRÜCKLICHE ERLAUBNIS VON PAUL
//KOMMENTIEREN ERLAUBT. BEI FRAGEN AN PAUL WENDEN
//
//--------------PAUL------------

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

class renderEngine {
private:
	GLFWwindow* window;
public:
	renderEngine(const char* titel, uint16_t width, uint16_t heigth);
};