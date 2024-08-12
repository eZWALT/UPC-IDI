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
  centreEsc = glm::vec3(15.f,2.f,10.f);
  radiEsc = sqrt(4 + pow(sqrt(10*10+15*15),2));
}

void MyGLWidget::enviaPosFocus()
{
  if(focusCamara){
    posFoc = glm::vec3(0,0,0);
  }
  else{
    posFoc = glm::vec3(View * glm::vec4(15.f,10.f,10.f,1.f));
  }
  glUniform3fv(posfocusLoc,1,&posFoc[0]);
}

void MyGLWidget::iniCamera ()
{
  ExamGLWidget::iniCamera();
  angleX = 0.5;
  angleY = 0.5;
}

void MyGLWidget::paintGL ()
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Pintem el terra
  glBindVertexArray (VAO_Terra);
  modelTransformTerra ();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  // Pintem el Patricio
  glBindVertexArray (VAO_Patr);
  modelTransformPatricio ();
  glDrawArrays(GL_TRIANGLES, 0, patr.faces().size()*3);

  // Pintem l'arbre
  pintaArbre (glm::vec3(10,0,10));
  pintaArbre (glm::vec3(20,0,5));
  pintaArbre (glm::vec3(25,0,15));

  glBindVertexArray(0);
}


void MyGLWidget::modelTransformPatricio ()
{
  TG = glm::mat4(1.f);

  TG = glm::translate(TG,glm::vec3(10,0,10));
  TG = glm::rotate(TG,anglePat,glm::vec3(0,1,0));
  TG = glm::translate(TG,glm::vec3(5,0,0));

  TG = glm::scale(TG, glm::vec3 (2.f*escala,2.f*escala,2.f*escala));
  TG = glm::translate(TG, -centreBasePat);

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::viewTransform ()
{
  if (!camPlanta){
    View = glm::mat4(1.f);
    View = glm::translate(View,glm::vec3(0,0,-2 * radiEsc));
    View = glm::rotate(View,angleX,glm::vec3(1,0,0));
    View = glm::rotate(View,angleY,glm::vec3(0,1,0));
    View = glm::translate(View,-centreEsc);
  }
  else{
    obs = glm::vec3(15.f,radiEsc,10.f);
    View = glm::lookAt(obs, glm::vec3(15.f,0.f,10.f) , glm::vec3(0.f,0.f,-1.f));
  }

  glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::projectTransform ()
{
  if (!camPlanta)
    ExamGLWidget::projectTransform();
  else
  {
    glm::mat4 proj = glm::ortho(-radiEsc,radiEsc,radiEsc,-radiEsc,0.5f,2.f*radiEsc);
    glUniformMatrix4fv(projLoc,1,GL_FALSE,&proj[0][0]);
  }
}

void MyGLWidget::resizeGL (int width, int heigth)
{
#ifdef __APPLE__
  // Aquest codi és necessari únicament per a MACs amb pantalla retina.
  GLint vp[4];
  glGetIntegerv (GL_VIEWPORT, vp);
  ample = vp[2];
  alt = vp[3];
#else
  ample = width ;
  alt = heigth;
#endif

  ra = float(ample)/float(alt);
  if(ra < 1) fov = 2 * atan( tan(M_PI/3.f/2.f) /ra);
  projectTransform();
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) 
{
  makeCurrent();
  switch (event->key()) {
  case Qt::Key_Up: {
      anglePat -= M_PI/16;
      emit step();
    break;
	}
  case Qt::Key_F: {
      focusCamara = !focusCamara;
      enviaPosFocus();
    break;
	}
  case Qt::Key_C: {
      camPlanta = not camPlanta;
      if(camPlanta) emit planta();
      else emit euler();
      viewTransform();
      projectTransform();
    break;
	}
  case Qt::Key_R: {
    anglePat = 0;
    focusCamara = true;
    camPlanta = false;
    ExamGLWidget::initializeGL();
    emit reset();
    break;
	}
  case Qt::Key_O:{
    ++obs[2];
    viewTransform();
    projectTransform();
    break;
  }
  default: ExamGLWidget::keyPressEvent(event); break;
  }
  update();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();
  if ((DoingInteractive == ROTATE) && !camPlanta)
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

void MyGLWidget::carlos(){
  makeCurrent();
  anglePat -= M_PI/16;
  update();
  setFocus();
}

void MyGLWidget::cambia_ortogonal(){
  makeCurrent();
  camPlanta = true;
  viewTransform();
  projectTransform();
  update();
  setFocus();
}

void MyGLWidget::cambia_perspectiva(){
  makeCurrent();
  camPlanta = false;
  viewTransform();
  projectTransform();
  update();
  setFocus();
}


