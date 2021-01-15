#version 120

// varying = input du fragment shader


uniform vec3 u_BaseColor;
varying vec3 v_Color;


void main(void)
{
// la couleur finale RGBA (en theorie) du pixel
	gl_FragColor = vec4(u_BaseColor + v_Color, 1.0);
}