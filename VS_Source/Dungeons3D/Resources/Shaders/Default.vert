#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

uniform mat4 perspectiveMatrix;

smooth out vec4 interpColor;


void main()
{
	gl_Position = perspectiveMatrix * (position + vec4(0.0, 1.0, -3.0, 0.0));
	interpColor = color;
}
