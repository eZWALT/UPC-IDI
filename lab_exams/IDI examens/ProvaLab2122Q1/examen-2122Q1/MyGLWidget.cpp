// MyGLWidget.cpp
#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>

#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__,__FUNCTION__)
#define DEBUG() std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl;

int MyGLWidget::printOglError(const char file[], int line, const char func[]) 
{
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    const char * error = 0;
    switch (glErr)
    {
        case 0x0500:
            error = "GL_INVALID_ENUM";
            break;
        case 0x501:
            error = "GL_INVALID_VALUE";
            break;
        case 0x502: 
            error = "GL_INVALID_OPERATION";
            break;
        case 0x503:
            error = "GL_STACK_OVERFLOW";
            break;
        case 0x504:
            error = "GL_STACK_UNDERFLOW";
            break;
        case 0x505:
            error = "GL_OUT_OF_MEMORY";
            break;
        default:
            error = "unknown error!";
    }
    if (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s function: %s\n",
                             file, line, error, func);
        retCode = 1;
    }
    return retCode;
}

MyGLWidget::~MyGLWidget() {
}

void MyGLWidget::iniEscena ()
{
  ExamGLWidget::iniEscena();
  centreEsc = glm::vec3(15.f,1.25,12.f);
  radiEsc = sqrt(1.25*1.25 + pow(sqrt(12*12+15*15),2));
}

void MyGLWidget::iniMaterialTerra()
{
  amb = glm::vec3(0,0.8,0.8);
  diff = glm::vec3(0,1,1);
  spec = glm::vec3(1,1,1);
  shin = 500;
}

void MyGLWidget::enviaPosFocus()
{
  if(iluminaculavio){
    modelTransformAvio();
    glm::vec3 pos = (0.5f)*(capsaAvioMax + capsaAvioMin);
    pos.z = capsaAvioMin.z;
    glm::vec4 xd = View * TGAvio * glm::vec4(pos,1.0);
    posFoc = glm::vec3(xd[0], xd[1], xd[2]);

  }
  else{
    posFoc = glm::vec3(0.f,0.f,0.f);
  }
  glUniform3fv(posfocusLoc,1,&posFoc[0]);
}

void MyGLWidget::iniCamera ()
{
  angleY = 0.5;
  angleX = 0.5;
  camera2 = false;
  ra = float(width())/height();
  fov = float(M_PI/3.0);
  zn = 15;
  zf = 65;

  projectTransform ();
  viewTransform ();
}

void MyGLWidget::paintGL ()
{
  ExamGLWidget::paintGL();
}

void MyGLWidget::resizeGL(int w, int h){
#ifdef __APPLE__
  // Aquest codi és necessari únicament per a MACs amb pantalla retina.
  GLint vp[4];
  glGetIntegerv (GL_VIEWPORT, vp);
  ample = vp[2];
  alt = vp[3];
#else
  ample = w;
  alt = h;
#endif

  ra = float(ample)/float(alt);
  if(ra < 1) fov = 2 * glm::atan(glm::tan(M_PI/3/2)/ra);
  projectTransform();
}

void MyGLWidget::modelTransformPatricio ()
{
  TGpatricio = glm::mat4 (1.f);
  TGpatricio = glm::translate(TGpatricio,glm::vec3(15,0,12));
  TGpatricio = glm::rotate(TGpatricio,glm::radians(-90.0f),glm::vec3(0,1,0));
  TGpatricio = glm::scale(TGpatricio, glm::vec3 (escalaPat*2, escalaPat*2, escalaPat*2));
  TGpatricio = glm::translate(TGpatricio, -centreBasePat);

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TGpatricio[0][0]);
}

void MyGLWidget::modelTransformAvio ()
{
  TGAvio = glm::mat4(1.f);

  TGAvio = glm::translate(TGAvio,glm::vec3(15,alturaAvio,12));
  TGAvio = glm::rotate(TGAvio,angleAvio,glm::vec3(0,-1,0));
  TGAvio = glm::translate(TGAvio, glm::vec3(10,0,0));

  TGAvio = glm::scale(TGAvio, glm::vec3 (1.5*escalaAvio, 1.5*escalaAvio, 1.5*escalaAvio));
  TGAvio = glm::translate(TGAvio, -centreBaseAvio);

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TGAvio[0][0]);
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();
  if ((DoingInteractive == ROTATE) && !camera2)
  {
    // Fem la rotació
    angleY += (e->x() - xClick) * M_PI / ample;
    angleX += (e->y() - yClick) * M_PI / ample;
    viewTransform ();
  }

  xClick = e->x();
  yClick = e->y();

  update ();
}

void MyGLWidget::viewTransform ()
{
  if (!camera2){
    View = translate(glm::mat4(1.f),glm::vec3(0,0,-2*radiEsc));
    View = rotate(View,angleX,glm::vec3(1,0,0));
    View = rotate(View,angleY,glm::vec3(0,1,0));
    View = translate(View,-centreEsc);
  }
  else
  {
    glm::vec3 obs = glm::vec3(15.f,3.f,12.f);
    glm::vec3 vrp = glm::vec3(7.5f,3.f,12.f);
    glm::vec3 up = glm::vec3(0.f,1.f,0.f);
    View = glm::lookAt(obs,vrp,up);
  }
  glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);

}

void MyGLWidget::projectTransform ()
{
  if (!camera2)
    ExamGLWidget::projectTransform();
  else
  {
    glm::mat4 Proj;
    Proj = glm::perspective(float(M_PI/2.f),ra,0.1f,2.f*radiEsc);
    glUniformMatrix4fv(projLoc,1,GL_FALSE,&Proj[0][0]);
  }
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) 
{
  makeCurrent();
  switch (event->key()) {
  case Qt::Key_Up: {
      if(alturaAvio < 5) ++alturaAvio;
      emit cambia_altura(alturaAvio);
    break;
	}
  case Qt::Key_Down: {
      if(alturaAvio > 0) --alturaAvio;
      emit cambia_altura(alturaAvio);
    break;
	}
  case Qt::Key_Right: {
      angleAvio += M_PI/16;
    break;
	}
  case Qt::Key_F: {
      iluminaculavio = !iluminaculavio;
      enviaPosFocus();
    break;
	}
  case Qt::Key_C: {
      camera2 = not camera2;
      if(camera2) emit posa_camara2();
      else emit posa_camara1();

      viewTransform();
      projectTransform();
    break;
	}
  case Qt::Key_R: {

    emit posa_camara1();
    emit cambia_altura(0);
    iluminaculavio = false;
    camera2 = false;
    angleAvio = 0.f;
    alturaAvio = 0;
    ExamGLWidget::initializeGL();
    break;
	}
  default: ExamGLWidget::keyPressEvent(event); break;
  }
  update();
}


void MyGLWidget::carregaShaders()
{
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs (QOpenGLShader::Fragment, this);
  QOpenGLShader vs (QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  fs.compileSourceFile("./shaders/basicLlumShader.frag");
  vs.compileSourceFile("./shaders/basicLlumShader.vert");
  // Creem el program
  program = new QOpenGLShaderProgram(this);
  // Li afegim els shaders corresponents
  program->addShader(&fs);
  program->addShader(&vs);
  // Linkem el program
  program->link();
  // Indiquem que aquest és el program que volem usar
  program->bind();

  // Obtenim identificador per a l'atribut “vertex” del vertex shader
  vertexLoc = glGetAttribLocation (program->programId(), "vertex");
  // Obtenim identificador per a l'atribut “normal” del vertex shader
  normalLoc = glGetAttribLocation (program->programId(), "normal");
  // Obtenim identificador per a l'atribut “matamb” del vertex shader
  matambLoc = glGetAttribLocation (program->programId(), "matamb");
  // Obtenim identificador per a l'atribut “matdiff” del vertex shader
  matdiffLoc = glGetAttribLocation (program->programId(), "matdiff");
  // Obtenim identificador per a l'atribut “matspec” del vertex shader
  matspecLoc = glGetAttribLocation (program->programId(), "matspec");
  // Obtenim identificador per a l'atribut “matshin” del vertex shader
  matshinLoc = glGetAttribLocation (program->programId(), "matshin");

  // Demanem identificadors per als uniforms dels shaders
  transLoc = glGetUniformLocation (program->programId(), "TGpatricio");
  projLoc = glGetUniformLocation (program->programId(), "proj");
  viewLoc = glGetUniformLocation (program->programId(), "view");
  posfocusLoc = glGetUniformLocation (program->programId(), "posFocus");
}

void MyGLWidget::rep_altura(int a){
  makeCurrent();
  alturaAvio = a;
  update();
  setFocus();
}

void MyGLWidget::camaraAvio(){
  makeCurrent();
  camera2 = false;
  viewTransform();
  projectTransform();
  update();
  setFocus();
}

void MyGLWidget::camaraPatricio(){
  makeCurrent();
  camera2 = true;
  viewTransform();
  projectTransform();
  update();
  setFocus();
}
