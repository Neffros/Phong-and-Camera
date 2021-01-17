#version 430 core

// varying = input du fragment shader


in vec3 v_normales;
in vec3 v_position;
layout(location=5)  uniform vec3 u_Color;
layout(location=6)  uniform vec3 u_viewPos;


void main(void)
{
    vec3 lightColor = vec3(1,1,0);
    // AMBIANT : 
    /* c'est la lumière qui émane de l'objet. */
    float strength = 0.1;
    vec3 ambient = strength * lightColor;

    // DIFFUSE :
    /* c'est la lumière qui est réfléchits sur l'objet. */
    vec3 norm = normalize(v_normales);
    vec3 lightDir = normalize(vec3(20,10,0) - v_position); // lumière en position 20,10,0
    float side = max(dot(norm, lightDir), 0.0); // pour savoir de quel côté on éclaire 
    vec3 diffuse = side * lightColor;

    // SPECULAR :
    /* c'est le halo de lumière sur les objets brillants. */
    strength = 0.8;
    vec3 viewDir = normalize(u_viewPos - v_position);
    vec3 reflectDir = reflect(-lightDir, norm); 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
    vec3  specular= strength * spec * lightColor; 

    vec3 result = (ambient+diffuse+specular) * u_Color;
    gl_FragColor = vec4(result, 1.0);
}