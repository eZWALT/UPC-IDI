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

void MyGLWidget::resizeGL (int w, int h)
{
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

  if (ra < 1) fov = 2 * glm::atan( glm::tan(M_PI / 6.0f) / ra);

  projectTransform();
}

void MyGLWidget::iniEscena ()
{
    creaBuffersPatricio();
    creaBuffersTerra();
    creaBuffersCub();
    creaBuffersEsfera();

    // Paràmetres de l'escena - arbitraris
    centreEsc = glm::vec3 (15, 2, 10);
    radiEsc = sqrt(15*15+10*10+2*2);

    enviaPosFocus();

}

void MyGLWidget::enviaPosFocus()
{
    if (!focus2)
    {
        ExamGLWidget::enviaPosFocus();
    } else {
        glm::vec4 pos = glm::vec4(15.0f, 10.0f, 10.0f, 1.f);
        glm::vec3 posOBS = glm::vec3(View * pos);
        glUniform3fv (posfocusLoc, 1, &posOBS[0]);
    }
}

void MyGLWidget::iniCamera ()
{
    angleY = 0.5;
    angleX = 0.5;
    camPlanta = false;
    focus2 = false;
    ra = float(width())/height();
    fov = float(M_PI/3.0);
    zn = 15;
    zf = 65;

    projectTransform ();
    viewTransform ();
}

void MyGLWidget::paintGL ()
{
    // En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
    // useu els paràmetres que considereu (els que hi ha són els de per defecte)
    //  glViewport (0, 0, ample, alt);

      // Esborrem el frame-buffer i el depth-buffer
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
    TG = translate(TG, glm::vec3(10,0,10));
    TG = glm::rotate(TG, angleP, glm::vec3(0,-1,0));
    TG = glm::translate(TG, glm::vec3(5,0,0));
    //TG = glm::translate(TG, glm::vec3(15,0,10));
    TG = glm::scale(TG, glm::vec3 (2*escala, 2*escala, 2*escala));
    TG = glm::translate(TG, -centreBasePat);

    glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::viewTransform ()
{
  if (!camPlanta)
    {
        View = glm::mat4(1.0f);

        View = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -2*radiEsc));
        View = glm::rotate(View, angleX, glm::vec3(1, 0, 0));
        View = glm::rotate(View, angleY, glm::vec3(0, 1, 0));
        View = glm::translate(View, glm::vec3(-centreEsc.x, -centreEsc.y, -centreEsc.z));

        glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
    }
  else
  {
    // Codi per a la viewMatrix de la Càmera-2
    View = glm::lookAt(glm::vec3(centreEsc.x, 2*radiEsc, centreEsc.z), glm::vec3(centreEsc.x, 0, centreEsc.z), glm::vec3(0, 0, -1));

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &View[0][0]);
  }
}

void MyGLWidget::projectTransform ()
{
  if (!camPlanta)
    {
        ExamGLWidget::projectTransform();

    }
  else
  {
    // Codi per a la projectMatrix de la Càmera-2
    glm::mat4 Proj;
    Proj = glm::ortho(-15.f, 15.f, -10.f, +10.f, 0.1f, 3*radiEsc);

    glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
  }
}

void MyGLWidget::reset()
{
    focus2 = false;
    angleP = 0.0f;
    emit sendEuler(true);
    emit sendPlanta(false);
    emit sendP(0);
    ExamGLWidget::initializeGL();
}

void MyGLWidget::camEuler(){
    makeCurrent();

    camPlanta = false;

    viewTransform();
    projectTransform();

    update();
}

void MyGLWidget::changeInt(int p)
{
    makeCurrent();
    pasos = (p % 32);

    angleP = float(pasos * M_PI / 16.0f);
    update();
}

void MyGLWidget::camP(){
    makeCurrent();

    camPlanta = true;

    viewTransform();
    projectTransform();

    update();
}

void MyGLWidget::keyPressEvent(QKeyEvent* event)
{
    makeCurrent();

  switch (event->key()) {
  case Qt::Key_Up: {
    angleP += float(M_PI / 16.0f);
    if (angleP >= float(2*M_PI)) angleP -= float(2*M_PI);

    pasos = (pasos + 1) % 32;

    emit sendP(pasos);

    modelTransformPatricio();
    break;
	}
  case Qt::Key_F: {
     focus2 = !focus2;
     enviaPosFocus();
    break;
	}
  case Qt::Key_C: {
    camPlanta = !camPlanta;
    emit sendEuler(!camPlanta);
    emit sendPlanta(camPlanta);
    viewTransform();
    projectTransform();
    break;
	}
  case Qt::Key_R: {
    reset();
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
