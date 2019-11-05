#pragma once

#include "../Utilities/utilities.h"

class Camera
{
private:
	Vector3 position;
	Vector3 target;
	Vector3 up;
	GLfloat moveSpeed, rotateSpeed;
	GLfloat m_near, m_far, fov;
	GLfloat deltaTime;
	Vector3 xAxis, yAxis, zAxis;
	Matrix viewMatrix, worldMatrix;
	Matrix perspectiveMatrix;

private:
	// Important
	void Move(Vector3 *axis, GLfloat direction);

public:
	// Important
	void Move_OX(GLfloat direction);
	void Move_OY(GLfloat direction);
	void Move_OZ(GLfloat direction);

	void Rotate_OX(GLfloat direction);
	void Rotate_OY(GLfloat direction);
	void Rotate_OZ(GLfloat direction);

	void Update_axis();
	void Update_world_view();

	// Constructors
	Camera();

	// Setters
	void Set_position(Vector3 _position);
	void Set_target(Vector3 _target);
	void Set_up(Vector3 _up);
	void Set_moveSpeed(GLfloat _moveSpeed);
	void Set_rotateSpeed(GLfloat _rotateSpeed);
	void Set_near(GLfloat _near);
	void Set_far(GLfloat _far);
	void Set_fov(GLfloat _fov);
	void Set_deltaTime(GLfloat _deltaTime);
	void Set_xAxis(Vector3 _xAxis);
	void Set_yAxis(Vector3 _yAxis);
	void Set_zAxis(Vector3 _zAxis);
	void Set_viewMatrix(Matrix _viewMatrix);
	void Set_worldMatrix(Matrix _worldwMatrix);

	// Getters
	Vector3 Get_position();
	Vector3 Get_target();
	Vector3 Get_up();
	GLfloat Get_moveSpeed();
	GLfloat Get_rotateSpeed();
	GLfloat Get_near();
	GLfloat Get_far();
	GLfloat Get_fov();
	GLfloat Get_deltaTime();
	Vector3 Get_xAxis();
	Vector3 Get_yAxis();
	Vector3 Get_zAxis();
	Matrix Get_viewMatrix();
	Matrix Get_worldMatrix();
	Matrix Get_perspectiveMatrix();
};