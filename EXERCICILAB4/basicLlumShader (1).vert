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
uniform vec3 PosFocusPat;

out vec3  fmatamb;
out vec3  fmatdiff;
out vec3  fmatspec;
out float fmatshin;
out vec3  fvertex;
out vec3  fnormal;
out vec3 PosFocusPatSCO;
out vec3 PosFocusEs;


void main()
{	
    // Passem les dades al fragment shader
    mat3 NM = inverse(transpose(mat3(TG*View)));
    fmatamb  = matamb;
    fmatdiff = matdiff;
    fmatspec = matspec;
    fmatshin = matshin;
    fvertex = (View * TG * vec4 (vertex, 1.0)).xyz; // CALCULEU CORRECTAMENT
    fnormal = NM*normal; // CALCULEU CORRECTAMENT

    PosFocusPatSCO = (View * vec4 (PosFocusPat, 1.0)).xyz;
    PosFocusEs = (View * vec4(10.0, 3.0, 5.0, 1)).xyz;
    
    gl_Position = Proj * View * TG * vec4 (vertex, 1.0);
}
