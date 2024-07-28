#version 330 core

out vec4 FragColor;

uniform vec4 modelColor;

 void main ()
 {
	//FragColor = vec4 (126.0f/254.0f, 194.0f/254.0f, 254.0f/254.0f, 1.0f);
	FragColor = modelColor;
 }