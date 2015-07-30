#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 diffuseColor;
layout(location = 2) in vec3 normal;

smooth out vec4 interpColor;

uniform vec3 lightDirection;
uniform vec4 lightIntensity;

uniform mat4 modelToCameraMatrix;
uniform mat3 normalModelToCameraMatrix;

uniform mat4 cameraToClipMatrix;


void main()
{
	gl_Position = cameraToClipMatrix * modelToCameraMatrix * vec4(position, 1.0);

	vec3 cameraNormal = normalize(normalModelToCameraMatrix * normal);
	float cosAngle = clamp(dot(cameraNormal, lightDirection), 0, 1);
	interpColor = lightIntensity * diffuseColor * cosAngle;
}
