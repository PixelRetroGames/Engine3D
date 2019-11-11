#pragma once

#include "stdafx.h"
#include "../Utilities/utilities.h"
#include "./Vertex.h"
#include "./Shaders.h"
#include <vector>

struct Triple
{
	GLushort x, y, z;
};

class Model
{
public:
	std::vector<Vertex> v;
	std::vector<GLushort> pos;

public:
	Shaders shaders;
	GLuint vertex_buffer, pos_buffer;

	void Parse(std::string filename);
};