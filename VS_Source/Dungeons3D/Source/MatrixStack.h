/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#pragma once

#include "Matrix.h"
#include <stack>

struct MatrixStack
{
	Mtx44 matrix;
	std::stack<Mtx44> stack;

	MatrixStack();

	void Push();
	void Pop();
};