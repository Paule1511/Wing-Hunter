#include "Wing-Shapes.h"
#include <stdint.h>
#include <vector>

Coords::Coords(int x, int y, int z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Coords::Coords() {
	return;
}


RGBA::RGBA(int r = 255, int g = 255, int b = 255, int a = 255) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Vertex::Vertex(Coords coords, RGBA colors = RGBA()) {
	this->coords = coords;
	this->colors = colors;
}

Poly::Poly(std::vector<Vertex> vertexes) {
	this->vertexes = vertexes;
}

void Poly::Append(Vertex vertex) {
	this->vertexes.push_back(vertex);
}

void Poly::Append(std::vector<Vertex> vertexes) {
	this->vertexes.insert(this->vertexes.end(), vertexes.begin(), vertexes.end());
}

std::vector<Coords> Poly::getVertexCoords() {
	std::vector<Coords> outVector{};
	for (int i = 0; i < vertexes.size(); i++) {
		outVector.push_back(vertexes[i].coords);
	}
	return outVector;
}

std::vector<RGBA> Poly::getVertexColors() {
	std::vector<RGBA> outVector{};
	for (int i = 0; i < vertexes.size(); i++) {
		outVector.push_back(vertexes[i].colors);
	}
	return outVector;
}
