/*****************************************************************************************
  Project      : 3D Game Engine
  Author       : Sam Tian
  Contributors :
******************************************************************************************/
#include "MatrixStack.h"

MatrixStack::MatrixStack()
{
	matrix = Mtx44::Identity();
	stack.push(matrix);
}

void MatrixStack::Push()
{
	stack.push(matrix);
}

void MatrixStack::Pop()
{
	matrix = stack.top();
	stack.pop();
}