#version 120

// float : 1 seule composante
// vec2 : 2 composantes float
// vec3 : 3 ""  
// vec4 : 4 ""
// struct vec4 { float x, y, z, w };
// SIMD = Single Instruction 
// Multiple Data

// attribute = inputs du vertex shader
attribute vec2 a_Position;
attribute vec3 a_Color;

// uniform = constantes pour un appel de rendu (glDraw)

uniform float u_Time;

uniform mat4 u_TranslationMatrix;
uniform mat4 u_RotationMatrix;
uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ViewMatrix;

// varying = output du vertex shader

varying vec3 v_Color;

void main(void)
{
	v_Color = a_Color;

	// 1. sous forme vectorielle
	//vec2 translation =  vec2(cos(u_Time), sin(u_Time));	
	//vec2 position = a_Position + translation;
	//// la position 4D (NDC) du sommet
	//gl_Position = vec4(position, 0.0, 1.0);

	// 2.a sous forme matricielle
	/*mat4 T = mat4(
				vec4(1.0, 0.0, 0.0, 0.0),	// 1ere colonne
				vec4(0.0, 1.0, 0.0, 0.0), // 2eme colonne
				vec4(0.0, 0.0, 1.0, 0.0), // 3eme colonne
				vec4(cos(u_Time), sin(u_Time), 0.0, 1.0) // 4eme colonne
				);
	vec4 position = T * vec4(a_Position, 0.0, 1.0);*/

	// 2.b avec une matrice uniform

	vec4 position = u_TranslationMatrix * u_RotationMatrix * vec4(a_Position, 0.0, 1.0);

	vec4 finalPosition = u_ProjectionMatrix * u_ViewMatrix * position;

	gl_Position = finalPosition;

}