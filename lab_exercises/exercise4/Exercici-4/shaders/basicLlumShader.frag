#version 330 core

in vec3  fmatamb;
in vec3  fmatdiff;
in vec3  fmatspec;
in float fmatshin;
in vec3  fvertex;
in vec3  fnormal;


in vec3 posicioEscenaSCO;
in vec3 posicioPatricioSCO;

const vec3 llumAmbient = vec3(0.2, 0.2, 0.2);

uniform vec3 posicioCamara;
uniform vec3 posicioEscena;
uniform vec3 posicioPatricio;
uniform vec3 colorCamara;
uniform vec3 colorEscena;
uniform vec3 colorPatricio;

uniform mat4 TG;
uniform mat4 Proj;
uniform mat4 View;


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
    vec3 norm = normalize(fnormal);
    vec3 Lcamara = normalize(-fvertex);
    vec3 Lescena = normalize(posicioEscenaSCO-fvertex);
    vec3 Lpatricio = normalize(posicioPatricioSCO-fvertex);
    //distancies calculades

    FragColor = vec4(Ambient() + Difus(norm,Lcamara,colorCamara) + Difus(norm,Lescena,colorEscena) + Difus(norm,Lpatricio,colorPatricio) + Especular(norm,Lcamara,fvertex,colorCamara) + Especular(norm,Lescena,fvertex,colorEscena) + Especular(norm,Lpatricio,fvertex,colorPatricio), 1.0);
    //FragColor = vec4(Ambient()+Difus(norm,Lcamara,vec3(0.9,0,0.9))+Especular(norm,Lcamara,fvertex,vec3(0.9,0,0.9))+Difus(norm,Lescena,vec3(0.9,0.9,0.9))+Especular(norm,Lescena,fvertex,vec3(0.9,0.9,0.9))+Difus(norm,Lpatricio,vec3(0.9,0.9,0.2))+ Especular(norm,Lpatricio,fvertex,vec3(0.9,0.9,0.2)),1);
}
