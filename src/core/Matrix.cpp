#include "stdafx.h"
#include "Matrix.h"
#include "Graphics.h"

/**
 * \brief Creates an identity matrix.
 */
Matrix::Matrix()
{
	//glMatrixMode(GL_PROJECTION);
 //   Graphics::checkOpenglError("Matrix::Matrix glMatrixMode Failed.");	    

	//glLoadIdentity();
 //   Graphics::checkOpenglError("Matrix::Matrix glLoadIdentity Failed.");	    

	//glGetFloatv(GL_PROJECTION_MATRIX, matrix);
 //   Graphics::checkOpenglError("Matrix::Matrix glGetFloatv Failed."); 
}

void Matrix::makeIdentity()
{
	//glMatrixMode(GL_PROJECTION);
 //   Graphics::checkOpenglError("Matrix::makeIdentity glMatrixMode Failed.");	    

	//glLoadIdentity();
 //   Graphics::checkOpenglError("Matrix::makeIdentity glLoadIdentity Failed.");	    

	//glGetFloatv(GL_PROJECTION_MATRIX, matrix);
 //   Graphics::checkOpenglError("Matrix::makeIdentity glGetFloatv Failed.");	    
}

void Matrix::makeOrthoProjection(
		float width, 
		float height, 
		float nearPlane, 
		float farPlane)
{
	//glMatrixMode(GL_PROJECTION);
 //   Graphics::checkOpenglError("Matrix::makeOrthoProjection glMatrixMode Failed.");	    

	//glLoadIdentity();
 //   Graphics::checkOpenglError("Matrix::makeOrthoProjection glLoadIdentity Failed.");	    
	//
	//glOrtho(-(width/2), (width/2), -(height/2), (height/2), nearPlane, farPlane);
	////glOrtho(0, width, 0, height, nearPlane, farPlane);
 //   Graphics::checkOpenglError("Matrix::makeOrthoProjection glOrtho Failed.");	    

	//glGetFloatv(GL_PROJECTION_MATRIX, matrix);
 //   Graphics::checkOpenglError("Matrix::makeOrthoProjection glGetFloatv Failed.");	    
}

void Matrix::makePerspectiveProjection(
		float verticalFieldOfViewInDegrees, 
		float aspectRatio, 
		float nearPlane,	
		float farPlane)
{
	//glMatrixMode(GL_PROJECTION);
 //   Graphics::checkOpenglError("Matrix::makePerspectiveProjection glMatrixMode Failed.");	    
	//
	//glLoadIdentity();
 //   Graphics::checkOpenglError("Matrix::makePerspectiveProjection glLoadIdentity Failed.");	    
	//
	//gluPerspective(verticalFieldOfViewInDegrees, aspectRatio, nearPlane, farPlane);
 //   Graphics::checkOpenglError("Matrix::makePerspectiveProjection gluPerspective Failed.");	    

	//glGetFloatv(GL_PROJECTION_MATRIX, matrix);
 //   Graphics::checkOpenglError("Matrix::makePerspectiveProjection gluPerspective Failed.");	    
}

void Matrix::makeTransform(float axisX, float axisY, float axisZ, float angle, float x, float y, float z)
{
	//glMatrixMode(GL_MODELVIEW);
 //   Graphics::checkOpenglError("Matrix::makeTransform glMatrixMode Failed.");	    

	//glLoadIdentity();
 //   Graphics::checkOpenglError("Matrix::makeTransform glLoadIdentity Failed.");	    
	//		
	//glRotatef(angle, axisX, axisY, axisZ);
 //   Graphics::checkOpenglError("Matrix::makeTransform glRotatef Failed.");
	//
	//glTranslatef(x, y, z);
 //   Graphics::checkOpenglError("Matrix::makeTransform glTranslatef Failed.");
	//
	//glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
 //   Graphics::checkOpenglError("Matrix::makeTransform glTranslatef Failed.");	    
}

void Matrix::makeViewMatrix(
			float cameraAxisX, 
			float cameraAxisY, 
			float cameraAxisZ, 
			float cameraAngle, 
			float cameraX, 
			float cameraY, 
			float cameraZ) 
{
	//glMatrixMode(GL_MODELVIEW);
 //   Graphics::checkOpenglError("Matrix::makeTransform glMatrixMode Failed.");	    

	//glLoadIdentity();
 //   Graphics::checkOpenglError("Matrix::makeTransform glLoadIdentity Failed.");	    

	//glTranslatef(-cameraX, -cameraY, -cameraZ);
 //   Graphics::checkOpenglError("Matrix::makeTransform glTranslatef Failed.");

	//glRotatef(-cameraAngle, cameraAxisX, cameraAxisY, cameraAxisZ);
 //   Graphics::checkOpenglError("Matrix::makeTransform glRotatef Failed.");
	//
	//glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
 //   Graphics::checkOpenglError("Matrix::makeTransform glTranslatef Failed.");	    
}
