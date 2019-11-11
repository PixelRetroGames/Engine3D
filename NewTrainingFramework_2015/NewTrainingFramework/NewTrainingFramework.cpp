// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include <conio.h>
#include "Globals.h"
#include "Camera.h"
#include "Model.h"



GLuint vboId, buffer2;
Shaders myShaders, lineShaders;
Model model;
Camera camera;

int Init ( ESContext *esContext )
{
	//glEnable(GL_DEPTH_TEST);
	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );

	//triangle data (heap)
	Vertex verticesData[6];

	verticesData[0].pos.x =  -0.5f;  verticesData[0].pos.y =  0.5f;  verticesData[0].pos.z =  0.0f;
	verticesData[0].color = Vector3(1.0f, 0.0f, 0.0f);
	
	verticesData[1].pos.x = -0.5f;  verticesData[1].pos.y = -0.5f;  verticesData[1].pos.z =  0.0f;
	verticesData[1].color = Vector3(0.0f, 1.0f, 0.0f);
	
	verticesData[2].pos.x =  0.5f;  verticesData[2].pos.y = -0.5f;  verticesData[2].pos.z =  0.0f;
	verticesData[2].color = Vector3(0.0f, 0.0f, 1.0f);

	verticesData[3].pos.x = 0.5f;  verticesData[3].pos.y = 0.5f;  verticesData[3].pos.z = 0.0f;
	verticesData[3].color = Vector3(0.0f, 1.0f, 0.0f);

	verticesData[4].pos.x = -0.5f;  verticesData[4].pos.y = 0.5f;  verticesData[4].pos.z = 0.0f;
	verticesData[4].color = Vector3(1.0f, 0.0f, 0.0f);

	verticesData[5].pos.x = 0.5f;  verticesData[5].pos.y = -0.5f;  verticesData[5].pos.z = 0.0f;
	verticesData[5].color = Vector3(0.0f, 0.0f, 1.0f);

	//buffer object
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesData), verticesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	verticesData[0].pos.x = 0.0f;  verticesData[0].pos.y = 1.0f;  verticesData[0].pos.z = 0.0f;

	verticesData[1].pos.x = 0.0f;  verticesData[1].pos.y = -1.0;  verticesData[1].pos.z = 0.0f;
	
	glGenBuffers(1, &buffer2);
	glBindBuffer(GL_ARRAY_BUFFER, buffer2);
	glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(verticesData[0]), verticesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//creation of shaders and program 
	int rtn = myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
	rtn = rtn || lineShaders.Init("../Resources/Shaders/LineShaderVS.vs", "../Resources/Shaders/LineShaderFS.fs");
	
	//MODEL
	model.Parse("../Resources/Models/Bila.nfg");

	glGenBuffers(1, &model.vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, model.vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.v[0]) * model.v.size(), &model.v[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &model.pos_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.pos_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(model.pos[0]) * model.pos.size(), &model.pos[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	rtn = rtn || model.shaders.Init("../Resources/Shaders/ModelShaderVS.vs", "../Resources/Shaders/ModelShaderFS.fs");

	return rtn;
}

void Draw ( ESContext *esContext )
{
	int err = glGetError();
	fprintf(stderr, "%d\n", err);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(myShaders.program);

	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	err = glGetError();

	
	if(myShaders.positionAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.positionAttribute);
		glVertexAttribPointer(myShaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	err = glGetError();

	if (myShaders.colorAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.colorAttribute);
		glVertexAttribPointer(myShaders.colorAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),(void*)sizeof(Vector3));
	}
	err = glGetError();

	if (myShaders.transformUniform != -1)
	{
		glUniformMatrix4fv(myShaders.transformUniform, 1, GL_FALSE, (GLfloat*)Globals::M.m);
	}
	err = glGetError();

	glDrawArrays(GL_TRIANGLES, 0, 6);
	err = glGetError();

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// LINE
	glUseProgram(lineShaders.program);
	err = glGetError();

	glBindBuffer(GL_ARRAY_BUFFER, buffer2);
	err = glGetError();

	if (lineShaders.positionAttribute != -1)
	{
		glEnableVertexAttribArray(lineShaders.positionAttribute);
		glVertexAttribPointer(lineShaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	err = glGetError();

	glDrawArrays(GL_LINES, 0, 2);
	err = glGetError();

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// MODEL
	glUseProgram(model.shaders.program);
	err = glGetError();

	glBindBuffer(GL_ARRAY_BUFFER, model.vertex_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.pos_buffer);
	err = glGetError();

	if (model.shaders.positionAttribute != -1)
	{
		glEnableVertexAttribArray(model.shaders.positionAttribute);
		glVertexAttribPointer(model.shaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	err = glGetError();

	if (model.shaders.transformUniform != -1)
	{
		glUniformMatrix4fv(model.shaders.transformUniform, 1, GL_FALSE, (GLfloat*)Globals::M.m);
	}
	err = glGetError();

	//glDrawArrays(GL_LINES, 0, model.v.size());
	glDrawElements(GL_TRIANGLES, model.pos.size(), GL_UNSIGNED_SHORT, NULL);
	err = glGetError();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	err = glGetError();

	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update ( ESContext *esContext, float deltaTime )
{
	Globals::timeSinceLastUpdate += deltaTime;
	if (Globals::timeSinceLastUpdate < Globals::updateIterval)
		return;
	Globals::timeSinceLastUpdate = 0;
	/*Globals::alpha = Globals::alpha > 2 * PI ? Globals::alpha - 2 * PI : Globals::alpha;
	Globals::alpha += Globals::step;
	Globals::M.SetRotationY(Globals::alpha);*/

	camera.Set_deltaTime(deltaTime);
	//camera.Rotate_OX(1);
	//camera.Rotate_OY(1);
	//camera.Rotate_OZ(1);
	camera.Update_world_view();
	Globals::M = camera.Get_viewMatrix() * camera.Get_perspectiveMatrix();
	if ((GetKeyState(VK_LBUTTON) & 0x100) != 0)
	{
		POINT pct;
		GetCursorPos(&pct);
		ScreenToClient(esContext->hWnd, &pct);
		if (pct.x > Globals::screenWidth / 2.0)
			camera.Rotate_OY(-1);
		else
			camera.Rotate_OY(1);
	}
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	if (bIsPressed)
	{
		switch (key)
		{
		case 'A': camera.Move_OX(-1);
			break;
		case 'D': camera.Move_OX(1);
			break;
		case 'Z': camera.Move_OY(1);
			break;
		case 'X': camera.Move_OY(-1);
			break;
		case 'W': camera.Move_OZ(-1);
			break;
		case 'S': camera.Move_OZ(1);
			break;
		case VK_UP: camera.Rotate_OX(1);
			break;
		case VK_DOWN: camera.Rotate_OX(-1);
			break;
		case VK_LEFT: camera.Rotate_OY(1);
			break;
		case VK_RIGHT: camera.Rotate_OY(-1);
			break;
		case VK_OEM_4: camera.Rotate_OZ(1);
			break;
		case VK_OEM_6: camera.Rotate_OZ(-1);
			break;
		case VK_ESCAPE: exit(0);
			break;
		default:
			break;
		}
	}
}

void CleanUp()
{
	glDeleteBuffers(1, &vboId);
	glDeleteBuffers(1, &buffer2);
}

int _tmain(int argc, _TCHAR* argv[])
{
	//identifying memory leaks
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); 

	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();


	printf("Press any key...\n");
	_getch();

	
	return 0;
}

