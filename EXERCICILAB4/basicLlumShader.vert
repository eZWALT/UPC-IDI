#version 330 core

in vec3 vertex;
in vec3 normal;

in vec3 matamb;
in vec3 matdiff;
in vec3 matspec;
in float matshin;
out vec3 vertPos;
out vec3 NormSCO;
out vec3 matamb2;
out vec3 matdiff2;
out vec3 matspec2;
out float matshin2;
out mat3 NormM;


uniform mat4 proj;
uniform mat4 view;
uniform mat4 TG;
uniform mat3 NM;
uniform vec3 light;
uniform vec3 colorF;


// Valors per als components que necessitem del focus de llum
vec3 colorFocus = vec3(0.8,0.8,0.8);
vec3 llumAmbient = colorF;
vec3 posFocus = light;  // en SCA


out vec3 fcolor;



void main()
{
    vec3 vertexSCO = (view * TG * vec4 (vertex, 1.0)).xyz;
    //vec3 posFocusSCO = (view* vec4(posFocus, 1)).xyz;
    NormM = (inverse(transpose(mat3(view*TG)))); 
    NormSCO = normalize(NormM*normal);
    
    vertPos = vertexSCO;
    
    matshin2 = matshin;
    matspec2 = matspec;
    matdiff2 = matdiff;
    matamb2 = matamb;
    gl_Position = proj * view * TG * vec4 (vertex, 1.0);
}
