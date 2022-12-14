#version 330 core

in vec3  fmatamb;
in vec3  fmatdiff;
in vec3  fmatspec;
in float fmatshin;
in vec3  fvertex;
in vec3  fnormal;
in vec3  PosFocusPatSCO;
in vec3  PosFocusEs;

const vec3 llumAmbient = vec3(0.2, 0.2, 0.2);

uniform mat4 TG;
uniform mat4 Proj;
uniform mat4 View;
uniform vec3 PosFocusPat;

uniform vec3 colFocusCam;
uniform vec3 colFocusEs;
uniform vec3 colFocusPat;

vec3 colFE = colFocusEs;
vec3 colFC = colFocusCam;
vec3 colFP = colFocusPat;

out vec4 FragColor;


vec3 Ambient() {
  return llumAmbient*fmatamb;
}

vec3 Difus (vec3 NormSCO, vec3 L, vec3 colFocus)
{
  // Fixeu-vos que SOLS es retorna el terme de Lambert!
  // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats
  vec3 colRes = vec3(0);
  if (dot (L, NormSCO) > 0)
    colRes = colFocus * fmatdiff * dot (L, NormSCO);
  return (colRes);
}

vec3 Especular (vec3 NormSCO, vec3 L, vec3 vertSCO, vec3 colFocus)
{
  // Fixeu-vos que SOLS es retorna el terme especular!
  // Assumim que els vectors estan normalitzats
  vec3 colRes = vec3 (0);
  // Si la llum ve de darrera o el material és mate no fem res
  if ((dot(NormSCO,L) < 0) || (fmatshin == 0))
    return colRes;  // no hi ha component especular

  vec3 R = reflect(-L, NormSCO); // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
  vec3 V = normalize(-vertSCO); // perquè la càmera està a (0,0,0) en SCO

  if (dot(R, V) < 0)
    return colRes;  // no hi ha component especular

  float shine = pow(max(0.0, dot(R, V)), fmatshin);
  return (colRes + fmatspec * colFocus * shine);
}

void main()
{
    vec3 Norm = normalize(fnormal);
    vec3 LCam = normalize(-fvertex);
    vec3 LEs = normalize(PosFocusEs - fvertex);
    vec3 temp = (View * vec4(5, 3, 2, 1)).xyz;
    vec3 LPat = normalize(PosFocusPatSCO - fvertex);


    FragColor = vec4(Ambient() + Especular(Norm, LEs, fvertex, colFE) + Difus(Norm, LEs, colFE) + Especular(Norm, LCam, fvertex, colFC) + Difus(Norm, LCam, colFC) + Especular(Norm, LPat, fvertex, colFP) + Difus(Norm, LPat, colFP), 1);
}
