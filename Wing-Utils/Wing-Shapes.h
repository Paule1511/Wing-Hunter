#pragma once
#include <stdint.h>
#include <vector>


struct RGBA {
	uint8_t r = 255;
	uint8_t g = 255;
	uint8_t b = 255;
	uint8_t a = 255;
	RGBA(int r, int g, int b, int a);
};


struct Coords {
	int x;
	int y;
	int z;
	Coords(int x, int y, int z);
	Coords();
};

struct Vertex {
	Coords coords;
	RGBA colors;
	Vertex(Coords coords, RGBA colors);
};

struct Poly {
	std::vector<Vertex> vertexes;
	Poly(std::vector<Vertex> vertexes);
	void Append(Vertex vertex);
	void Append(std::vector<Vertex> vertexes);
	std::vector<Coords> getVertexCoords();
	std::vector<RGBA> getVertexColors();
};