#pragma once
#include "Math.h"

struct Vertex 
{
	Vector3 pos;
	Vector3 color;

	Vector3 norm, binorm, tgt;
	Vector2 uv;

	Vertex() {}
	Vertex(const Vertex &other)
	{
		pos = other.pos;
		color = other.color;
		norm = other.norm;
		binorm = other.binorm;
		tgt = other.tgt;
		uv = other.uv;
	}
};