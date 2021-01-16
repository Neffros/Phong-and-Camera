#version 430 core

// varying = input du fragment shader


in vec3 v_normales;
in vec3 v_position;
layout(location=5)  uniform vec3 u_Color;


void main(void)
{
    // AMBIANT : 
    /* c'est la lumière qui émane de l'objet. */
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * vec3(1,1,0);

    // DIFFUSE :
    /* c'est la lumière qui est réfléchits sur l'objet. */
    vec3 norm = normalize(v_normales);
    vec3 lightDir = normalize(vec3(20,10,0) - v_position);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1,1,0);

    // SPECULAR :
    /* c'est le halo de lumière sur les objets brillants. */


    vec3 result = (ambient+diffuse) * u_Color;
    gl_FragColor = vec4(result, 1.0);
}