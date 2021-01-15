#version 120

// float : 1 seule composante
// vec2 : 2 composantes float
// vec3 : 3 ""  
// vec4 : 4 ""
// struct vec4 { float x, y, z, w };
// SIMD = Single Instruction 
// Multiple Data

// attribute = inputs du vertex shader
attribute vec3 a_Position;
attribute vec3 a_Normales;
attribute vec3 a_Textcoords;
attribute vec3 a_Color;

// uniform = constantes pour un appel de rendu (glDraw)

uniform float u_Time;

uniform mat4 u_TranslationMatrix;
uniform mat4 u_RotationMatrix;
uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ViewMatrix;

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