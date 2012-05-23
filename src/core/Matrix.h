#ifndef PROJ_MATRIX_H
#define PROJ_MATRIX_H

#include "stdafx.h"

/**
 * \class Matrix
 *
 * \brief Matrix class for graphics.
 *
 * This class manages matrix data using OpenGL.
 * This is done to guarrantee correctness; 
 * there are more efficient implementations.
 */
class Matrix
{
public:
    void makeIdentity();

    void makeOrthoProjection(
		float width, 
		float height, 
		float nearPlane, 
		float farPlane);

	virtual void makePerspectiveProjection(
		float verticalFieldOfViewInDegrees, 
		float aspectRatio, 
		float nearPlane, 
		float farPlane);

	virtual void makeTransform(
		float axisX, 
		float axisY, 
		float axisZ, 
		float angle, 
		float x, 
		float y, 
		float z);

	virtual void makeViewMatrix(
		float cameraAxisX, 
		float cameraAxisY, 
		float cameraAxisZ, 
		float cameraAngle, 
		float cameraX, 
		float cameraY, 
		float cameraZ);

    float matrix[16];

private:
	Matrix();
	~Matrix() { }
	Matrix(const Matrix &) { assert(false); }
	void operator=(const Matrix &) { assert(false); }

    friend class Graphics;  // To create matrices.
};

#endif
