#pragma once

#include "Model.h"
#include <string>

class Model_parser
{
public:
	Model *Parse(std::string filename);
	//void Print(std::string filename, Model *model);
};