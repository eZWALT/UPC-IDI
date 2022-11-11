#version 330 core

//APUNTS IMPORTANTS: LES NORMALS S'INTERPOLEN TAMBE, PERO NO ES NORMALITZEN!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//if(false or true) 17;

in vec3 fcolor;
in vec3 matamb2;
in vec3 matdiff2;
in vec3 matspec2;
in float matshin2;
in vec3 NormSCO;
in vec3 vertSCO;


out vec4 FragColor;
vec3 llumAmbient = vec3(0.2, 0.2, 0.2);



uniform vec3 posFocus;
uniform vec3 colorFocus;
uniform bool SCObool;
uniform mat4 view;

vec3 Ambient() {
    return llumAmbient * matamb2;
}

vec3 Difus (vec3 NormSCO, vec3 L, vec3 colFocus)
{
    // Fixeu-vos que SOLS es retorna el terme difús
    // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats
    vec3 colRes = vec3(0);
    // Càlcul component difusa, si n'hi ha
    if (dot (L, NormSCO) > 0)
      colRes = colFocus * matdiff2 * dot (L, NormSCO);
    return (colRes);
}

vec3 Especular (vec3 NormSCO, vec3 L, vec4 vertSCO, vec3 colFocus)
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
    vec3 L;
    vec3 nnn = normalize(NormSCO);
    if(SCObool) L = normalize((view * vec4(posFocus,1.0)).xyz - vertSCO);
    else L = normalize(posFocus - vertSCO);
	FragColor = vec4(Ambient() + Difus(nnn,L,colorFocus) + Especular(nnn,L,vec4(vertSCO,1.0),colorFocus),1.0); 
}
