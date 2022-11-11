#version 330 core

in vec3 vertex;
in vec3 normal;

in vec3  matamb;
in vec3  matdiff;
in vec3  matspec;
in float matshin;

uniform mat4 TG;
uniform mat4 Proj;
uniform mat4 View;
uniform vec3 posicioPatricio;

out vec3  fmatamb;
out vec3  fmatdiff;
out vec3  fmatspec;
out float fmatshin;
out vec3  fvertex;
out vec3  fnormal;

out vec3 posicioEscenaSCO;
out vec3 posicioPatricioSCO;


void main()
{	

    mat3 NM = inverse(transpose(mat3(View*TG)));
    // Passem les dades al fragment shader
    fmatamb  = matamb;
    fmatdiff = matdiff;
    fmatspec = matspec;
    fmatshin = matshin;
    fvertex = (View*TG*vec4(vertex,1.0)).xyz;
    fnormal = NM*normal; // CALCULEU CORRECTAMENT
    posicioEscenaSCO = (View*vec4(10.0,3.0,5.0,1.0)).xyz;
    posicioPatricioSCO = (View*vec4(posicioPatricio,1.0)).xyz;

    gl_Position = Proj * View * TG * vec4 (vertex, 1.0);

}
