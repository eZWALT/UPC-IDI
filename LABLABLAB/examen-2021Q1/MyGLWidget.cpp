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

void MyGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  glEnable(GL_DEPTH_TEST);
  carregaShaders();

  iniEscena ();
  iniCamera ();
}

MyGLWidget::~MyGLWidget() {
}

void MyGLWidget::paintGL ()   // Mètode que has de modificar
{
  // Esborrem el frame-buffer i el depth-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Pintem el terra
  glBindVertexArray (VAO_Terra);
  modelTransformTerra ();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  if (paintPatricio) {
    // Pintem el Patricio
    glBindVertexArray (VAO_Patr);
    modelTransformPatricio ();
    glDrawArrays(GL_TRIANGLES, 0, patr.faces().size()*3);
  }
  else {
    // Pintem el cub
    glBindVertexArray(VAO_Cub);
    modelTransformCub (2.5,baseAngle+2*M_PI/3);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    modelTransformCub (3,baseAngle+4*M_PI/3);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    modelTransformCub (2,baseAngle+2*M_PI);
    glDrawArrays(GL_TRIANGLES, 0, 36);
  }

  glBindVertexArray(0);
}

void MyGLWidget::modelTransformCub (float escala, float angle)
{
  ExamGLWidget::modelTransformCub (1.0, 0.0);

  TG = glm::rotate(glm::mat4(1.f),angle,glm::vec3(0,1,0));
  TG = glm::translate(TG,glm::vec3(5,0,0));
  TG = glm::scale(TG,glm::vec3(escala*2,escala*2,escala*2));

  glUniformMatrix4fv(transLoc,1,GL_FALSE,&TG[0][0]);
  // En aquest mètode has de substituir aquest codi per construir la
  // transformació geomètrica (TG) del cub usant els paràmetres adientment
}

void MyGLWidget::modelTransformPatricio ()    // Mètode que has de modificar
{
  //ExamGLWidget::modelTransformPatricio ();

  TG = glm::mat4(1.f);
  TG = glm::rotate(TG, anglePatricio, glm::vec3(0,1,0));
  TG = glm::translate(TG, glm::vec3(5.f, 0.0f, 0.0f));
  TG = glm::rotate(TG, float(-M_PI/2), glm::vec3(0,1,0));
  TG = glm::scale(TG, glm::vec3(escala*2.0f, escala*2.0f, escala*2.0f));
  TG = glm::translate(TG, -centreBasePat);

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);

}

void MyGLWidget::viewTransform ()    // Mètode que has de modificar
{
  if (!camPlanta)
    ExamGLWidget::viewTransform();
  else
  {
    // Codi per a la viewMatrix de la Càmera-2
    glm::mat4 View = glm::lookAt(glm::vec3(0,10,0), glm::vec3(0,0,0), glm::vec3(1,0,0));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &View[0][0]);
  }
}

void MyGLWidget::projectTransform ()
{
  if (!camPlanta)
    ExamGLWidget::projectTransform();
  else
  {
    // Codi per a la projectMatrix de la Càmera-2
    glm::mat4 Ortho = glm::ortho(-radiEsc,radiEsc,-radiEsc,radiEsc, 0.f, 2.f*radiEsc);

    glUniformMatrix4fv(projLoc, 1, GL_FALSE, &Ortho[0][0]);
  }
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) {
  makeCurrent();
  switch (event->key()) {
  case Qt::Key_V: {
      paintPatricio = !paintPatricio;
    break;
	}
  case Qt::Key_1: {
      anglePatricio =  M_PI/2;
      modelTransformPatricio();
    break;
	}
  case Qt::Key_2: {
    anglePatricio =  4*M_PI/3;
    modelTransformPatricio();
    break;
	}
  case Qt::Key_3: {
    anglePatricio =  2*M_PI;
    modelTransformPatricio();
    break;
	}
  case Qt::Key_F: {
      colorXD = !colorXD;
      if(not colorXD) colFoc = glm::vec3(1,1,1);
      else colFoc = glm::vec3(1,1,0);
      enviaColFocus();
    break;
	}
  case Qt::Key_C: {
      camPlanta = !camPlanta;
      if(camPlanta) emit ortogonal();
      else emit perspectiva();
    break;
	}
  case Qt::Key_Right: {
      baseAngle += 2*M_PI/3;
    break;
	}
  case Qt::Key_Left: {
      baseAngle -= 2*M_PI/3;
    break;
	}
  case Qt::Key_R: {
    baseAngle = 0;
    colFoc = glm::vec3(1.0,1.0,1.0);
    ExamGLWidget::enviaColFocus();
    cambiar_perspectiva();
    emit reiniciar();
    break;
	}
  default: ExamGLWidget::keyPressEvent(event); break;
  }
  update();
}

void MyGLWidget::cambiar_perspectiva(){
  makeCurrent();
  camPlanta = false;
  viewTransform();
  projectTransform();
  update();
  setFocus();
}

void MyGLWidget::cambiar_orto(){
  makeCurrent();
  camPlanta = true;
  viewTransform();
  projectTransform();
  update();
  setFocus();
}
