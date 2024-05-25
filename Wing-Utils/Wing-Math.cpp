
#define _USE_MATH_DEFINES

#include "Wing-Math.h"
#include <iostream>
#include <cmath>

vec3::vec3() {
	x = 0;
	y = 0;
	z = 0;
}

vec3::vec3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

float vec3::length() {
	return sqrt(x * x + y * y + z * z);
}

vec3 vec3Add(vec3 vec1, vec3 vec2) {
	return vec3(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
}

vec3 vec3Skalar(vec3 vec, float skalar) {
	return vec3(vec.x * skalar, vec.y * skalar, vec.z * skalar);
}

float vec3Dot(vec3 vec1, vec3 vec2) {
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

float rad2Deg(float rad) {
	return rad * 180 / M_PI;
}

float vec3Cos(vec3 vec1, vec3 vec2) {
	return vec3Dot(vec1, vec2) / (vec1.length() * vec2.length());
}

float vec3Deg(vec3 vec1, vec3 vec2) {
	return rad2Deg(acos(vec3Cos(vec1, vec2)));
}

float pow(float in) {
	return in * in;
}

vec3 vec3Proj(vec3 from, vec3 to) {
	std::cout << from.length() * vec3Cos(from, to) << std::endl;
	std::cout << vec3Cos(from, to) << std::endl;
	return vec3Skalar(to, vec3Dot(from, to) / pow(to.length()));
}

vec3 vec3Sub(vec3 min, vec3 sub) {
	return vec3(min.x - sub.x, min.y - sub.y, min.z - sub.z);
}

vec3 vec3Normalize(vec3 vec) {
	return vec3Skalar(vec, 1/vec.length());
}

float vec3EdgeEqu(vec3 start, vec3 norm, vec3 point) {
	return vec3Dot(vec3Normalize(norm), (vec3Sub(point, start)));
}