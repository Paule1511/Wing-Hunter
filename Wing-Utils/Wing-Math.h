#pragma once

#include <cmath>
#include <vector>


struct vec3 {
	float x;
	float y;
	float z;
	float length();
	vec3();
	vec3(float x, float y, float z);
};
float pow(float in);

vec3 vec3Add(vec3 vec1, vec3 vec2);

float vec3EdgeEqu(vec3 start, vec3 norm, vec3 point);

vec3 vec3Normalize(vec3 vec);

vec3 vec3Sub(vec3 min, vec3 sub);

float rad2Deg(float rad);

float vec3Dot(vec3 vec1, vec3 vec2);

float rad2Deg(float rad);

float vec3Cos(vec3 vec1, vec3 vec2);

float vec3Deg(vec3 vec1, vec3 vec2);

vec3 vec3Skalar(vec3 vec, float skalar);

vec3 vec3Proj(vec3 from, vec3 to);