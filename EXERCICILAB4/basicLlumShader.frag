#version 330 core

in vec3 fcolor;
out vec4 FragColor;

in vec3 vertPos;
in vec3 NormSCO;
in vec3 matamb2;
in vec3 matdiff2;
in vec3 matspec2;
in float matshin2;

uniform vec3 light;
uniform vec3 colorF;
uniform mat4 view;
uniform vec3 colorF2;

vec3 colorFocus = colorF;
vec3 colorFocus2 = colorF2;
vec3 llumAmbient = vec3(0.2, 0.2, 0.2);
vec3 posFocus = light;  // en SCA
vec3 llumCam = vec3(0, 0, 0);


vec3 Ambient() {
    return llumAmbient * matamb2;
}

vec3 Difus (vec3 NormS, vec3 L, vec3 colFocus) 
{
    // Fixeu-vos que SOLS es retorna el terme difús
    // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats
    vec3 colRes = vec3(0);
    // Càlcul component difusa, si n'hi ha
    if (dot (L, NormSCO) > 0)
      colRes = colFocus * matdiff2 * dot (L, NormSCO);
    return (colRes);
}

vec3 Especular (vec3 NormS, vec3 L, vec4 vertSCO, vec3 colFocus) 
{
    // Fixeu-vos que SOLS es retorna el terme especular!
    // Assumim que els vectors estan normalitzats
    vec3 colRes = vec3 (0);
    // Si la llum ve de darrera o el material és mate no fem res
    if ((dot(NormSCO,L) < 0) || (matshin2 == 0))
      return colRes;  // no hi ha component especular

    // Calculem R i V
    vec3 R = reflect(-L, NormSCO); // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
    vec3 V = normalize(-vertSCO.xyz); // perquè la càmera està a (0,0,0) en SCO

    if (dot(R, V) < 0)
      return colRes;  // no hi ha component especular
    
    float shine = pow(max(0.0, dot(R, V)), matshin2);
    return (matspec2 * colFocus * shine); 
}

void main()
{	
    vec3 posFocusSCO = (view* vec4(posFocus, 1)).xyz;
    vec3 L = normalize(posFocusSCO - vertPos);
    vec3 Lcam = normalize(- vertPos);
    
    vec3 Norm = normalize(NormSCO);
    vec3 Color = Ambient() + Difus(Norm, L, colorFocus) + Especular(Norm, L, vec4(vertPos, 1), colorFocus) + Difus(Norm, Lcam, colorFocus2) + Especular(Norm, Lcam, vec4(vertPos, 1), colorFocus2);
    FragColor = vec4(Color, 1);
    }
