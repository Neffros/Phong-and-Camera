#version 430 core
// float : 1 seule composante
// vec2 : 2 composantes float
// vec3 : 3 ""  
// vec4 : 4 ""
// struct vec4 { float x, y, z, w };
// SIMD = Single Instruction 
// Multiple Data

// attribute = inputs du vertex shader
layout(location=0) in vec3 a_Position;
layout(location=1) in vec3 a_Normales;
layout(location=2) in vec3 a_Textcoords;
layout(location=3) in vec3 a_Color;

// uniform = constantes pour un appel de rendu (glDraw)

layout(location=0)  uniform float u_Time;

layout(location=1)  uniform mat4 u_TranslationMatrix;
layout(location=2)  uniform mat4 u_RotationMatrix;
layout(location=3)  uniform mat4 u_ProjectionMatrix;
layout(location=4)  uniform mat4 u_ViewMatrix;

// varying = output du vertex shader

varying vec3 v_Color;
varying vec3 v_normales;
varying vec3 v_textcoords;

void main(void)
{
	v_Color = a_Color;

	

	vec4 position = u_TranslationMatrix * u_RotationMatrix * vec4(a_Position, 1.0) ;

	vec4 finalPosition = u_ProjectionMatrix * u_ViewMatrix * position;

	gl_Position = finalPosition;

	v_normales = a_Normales;
	v_textcoords = a_Textcoords;

}