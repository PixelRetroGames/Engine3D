#include "stdafx.h"
#include "Model.h"


void Model::Parse(std::string filename)
{
	FILE *in = fopen(filename.c_str(), "r");
	if (!in)
		return;
	int nr_vertices;
	fscanf(in, "NrVertices: %d ", &nr_vertices);
	Model *model = this;
	for (int i = 0; i<nr_vertices; i++)
	{
		Vertex a;
		int x;
		fscanf(in, "%d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f]; ",
			&x, &a.pos.x, &a.pos.y, &a.pos.z, &a.norm.x, &a.norm.y, &a.norm.z, &a.binorm.x, &a.binorm.y, &a.binorm.z,
			&a.tgt.x, &a.tgt.y, &a.tgt.z, &a.uv.x, &a.uv.y);
		model->v.push_back(a);
	}
	int nr_indices;
	fscanf(in, "NrIndices: %d ", &nr_indices);
	nr_indices /= 3;
	for (int i = 0; i<nr_indices; i++)
	{
		Triple a;
		int x;
		fscanf(in, "%d. %hu, %hu, %hu", &x, &a.x, &a.y, &a.z);
		model->pos.push_back(a.x);
		model->pos.push_back(a.y);
		model->pos.push_back(a.z);
	}
	fclose(in);
}