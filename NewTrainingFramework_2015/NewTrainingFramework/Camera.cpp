#include "stdafx.h"
#include "Camera.h"
#include "Globals.h"

// Important

void Camera::Move(Vector3 *axis,GLfloat direction)
{
	Update_axis();
	Vector3 forward = axis->Normalize() * direction;
	Vector3 moveVector = forward * moveSpeed * deltaTime;
	position += moveVector;
	target += moveVector;
}

void Camera::Move_OX(GLfloat direction)
{
	Move(&xAxis, direction);
}

void Camera::Move_OY(GLfloat direction) 
{
	Move(&yAxis, direction);
}

void Camera::Move_OZ(GLfloat direction) 
{
	Move(&zAxis, direction);
}

void Camera::Rotate_OX(GLfloat direction)
{
	Matrix mRotateOX;
	mRotateOX.SetRotationX(direction * rotateSpeed * deltaTime);
	Vector4 localUp = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
	Vector4 rotatedLocalUp = localUp * mRotateOX;
	up = (Vector3)(rotatedLocalUp * worldMatrix);
	up = up.Normalize();
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Vector4 rotatedTarget = localTarget * mRotateOX;
	target = (Vector3)(rotatedTarget * worldMatrix);
}

void Camera::Rotate_OY(GLfloat direction)
{
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Matrix mRotateOY;
	mRotateOY.SetRotationY(direction * rotateSpeed * deltaTime);
	Vector4 rotatedTarget = localTarget * mRotateOY;
	target = (Vector3)(rotatedTarget * worldMatrix);
}

void Camera::Rotate_OZ(GLfloat direction)
{
	Vector4 localUp = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
	Matrix mRotateOZ;
	mRotateOZ.SetRotationZ(direction * rotateSpeed * deltaTime);
	Vector4 rotatedLocalUp = localUp * mRotateOZ;
	up = (Vector3)(rotatedLocalUp * worldMatrix);
}

void Camera::Update_axis()
{
	zAxis = -(target - position).Normalize();
	yAxis = up.Normalize();
	xAxis = zAxis.Cross(yAxis).Normalize();
}

void Camera::Update_world_view()
{
	Update_axis();
	Matrix rotation, translation;
	
	translation.SetTranslation(position);
	
	rotation.SetZero();
	rotation.m[0][0] = xAxis.x; rotation.m[0][1] = xAxis.y; rotation.m[0][2] = xAxis.z;
	rotation.m[1][0] = yAxis.x; rotation.m[1][1] = yAxis.y; rotation.m[1][2] = yAxis.z;
	rotation.m[2][0] = zAxis.x; rotation.m[2][1] = zAxis.y; rotation.m[2][2] = zAxis.z;
	rotation.m[3][3] = 1;

	worldMatrix = rotation * translation;

	translation.SetTranslation(-position);
	rotation.Transpose();

	viewMatrix = translation * rotation;
}

// Constructors
Camera::Camera()
{
	position = Vector3(0, 0, -5);
	target = Vector3(0, 0, 0);
	up = Vector3(0, 1, 0);
	moveSpeed = 0.7;
	rotateSpeed = 0.7;
	worldMatrix = Matrix().SetIdentity();
	viewMatrix = Matrix().SetIdentity();
	fov = PI / 4.0f;
	m_near = 0.2f;
	m_far = 100.0f;
	GLfloat aspect = (GLfloat)Globals::screenWidth / (GLfloat)Globals::screenHeight;
	perspectiveMatrix.SetPerspective(fov, aspect, m_near, m_far);
	//perspectiveMatrix.SetIdentity();
}

// Setters
void Camera::Set_position(Vector3 _position)
{
	position = _position;
}

void Camera::Set_target(Vector3 _target)
{
	target = _target;
}

void Camera::Set_up(Vector3 _up)
{
	up = _up;
}

void Camera::Set_moveSpeed(GLfloat _moveSpeed)
{
	moveSpeed = _moveSpeed;
}

void Camera::Set_rotateSpeed(GLfloat _rotateSpeed)
{
	rotateSpeed = _rotateSpeed;
}

void Camera::Set_near(GLfloat _near)
{
	m_near = _near;
}

void Camera::Set_far(GLfloat _far)
{
	m_far = _far;
}

void Camera::Set_fov(GLfloat _fov)
{
	fov = _fov;
}

void Camera::Set_deltaTime(GLfloat _deltaTime)
{
	deltaTime = _deltaTime;
}

void Camera::Set_xAxis(Vector3 _xAxis)
{
	xAxis = _xAxis;
}

void Camera::Set_yAxis(Vector3 _yAxis)
{
	yAxis = _yAxis;
}

void Camera::Set_zAxis(Vector3 _zAxis)
{
	zAxis = _zAxis;
}

void Camera::Set_viewMatrix(Matrix _viewMatrix)
{
	viewMatrix = _viewMatrix;
}

void Camera::Set_worldMatrix(Matrix _worldwMatrix)
{
	worldMatrix = _worldwMatrix;
}

// Getters
Vector3 Camera::Get_position()
{
	return position;
}

Vector3 Camera::Get_target()
{
	return target;
}

Vector3 Camera::Get_up()
{
	return up;
}

GLfloat Camera::Get_moveSpeed()
{
	return moveSpeed;
}

GLfloat Camera::Get_rotateSpeed()
{
	return rotateSpeed;
}

GLfloat Camera::Get_near()
{
	return m_near;
}

GLfloat Camera::Get_far()
{
	return m_far;
}

GLfloat Camera::Get_fov()
{
	return fov;
}

GLfloat Camera::Get_deltaTime()
{
	return deltaTime;
}

Vector3 Camera::Get_xAxis()
{
	return xAxis;
}

Vector3 Camera::Get_yAxis()
{
	return yAxis;
}

Vector3 Camera::Get_zAxis()
{
	return zAxis;
}

Matrix Camera::Get_viewMatrix()
{
	return viewMatrix;
}

Matrix Camera::Get_worldMatrix()
{
	return worldMatrix;
}

Matrix Camera::Get_perspectiveMatrix()
{
	return perspectiveMatrix;
}