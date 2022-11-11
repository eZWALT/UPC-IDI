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

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();
  // Aqui cal que es calculi i s'apliqui la rotacio o el zoom com s'escaigui...
  if (DoingInteractive == ROTATE)
  {
    // Fem la rotació
    angleY += (e->x() - xClick) * M_PI / ample;
    viewTransform ();
  }

  xClick = e->x();
  yClick = e->y();

  update ();
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) {
  makeCurrent();
  switch (event->key()) {
  case Qt::Key_C: {
      off[0] = not off[0];
      if(off[0]) colorCamara = glm::vec3(0,0,0);
      else colorCamara = glm::vec3(0.9,0,0.9);
      llums();
    break;
	}
  case Qt::Key_E: {
      off[1] = not off[1];
      if(off[1]) colorEscena = glm::vec3(0,0,0);
      else colorEscena = glm::vec3(0.9,0.9,0.9);
      llums();
    break;
	}
  case Qt::Key_P: {
      off[2] = not off[2];
      if(off[2]) colorPatricio = glm::vec3(0,0,0);
      else colorPatricio = glm::vec3(0.9,0.9,0.2);
      llums();
    break;
	}
  case Qt::Key_Right: {
      angleXD += float(M_PI/6.f);
      modelTransformPatricio();
    break;
	}
  case Qt::Key_Left: {
      angleXD -= float(M_PI/6.f);
      modelTransformPatricio();
    break;
	}
  default: LL4GLWidget::keyPressEvent(event); break;
  }
  update();
}

void MyGLWidget::llums(){

    glUniform3fv(colorLoc[0], 1, &colorCamara[0]);
    glUniform3fv(colorLoc[1], 1, &colorEscena[0]);
    glUniform3fv(colorLoc[2], 1, &colorPatricio[0]);
    glUniform3fv(posLoc[0], 1, &posicioCamara[0]);
    glUniform3fv(posLoc[1], 1, &posicioEscena[0]);
    glUniform3fv(posLoc[2], 1, &posicioPatricio[0]);
}


void MyGLWidget::paintGL ()
{
  // En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
  // useu els paràmetres que considereu (els que hi ha són els de per defecte)
  // glViewport (0, 0, ample, alt);

  // Esborrem el frame-buffer i el depth-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Activem el VAO per a pintar el terra
  glBindVertexArray (VAO_Terra);

  modelTransformTerra ();

  // pintem
  glDrawArrays(GL_TRIANGLES, 0, 12);

  // Activem el VAO per a pintar el Patricio
  glBindVertexArray (VAO_Patr);

  llums();
  modelTransformPatricio ();

  // Pintem l'escena
  glDrawArrays(GL_TRIANGLES, 0, patr.faces().size()*3);

  glBindVertexArray(0);

}

void MyGLWidget::modelTransformPatricio ()
{
  TG = glm::mat4(1.f);
  TG = glm::translate(TG, glm::vec3(5,0,5));
  TG = glm::rotate(TG,angleXD,glm::vec3(0,1,0));
  TG = glm::translate(TG, glm::vec3(0,0,-3));
  TG = glm::scale(TG, glm::vec3(escala, escala, escala));
  TG = glm::rotate(TG,-angleXD,glm::vec3(0,1,0));
  TG = glm::translate(TG, -centreBasePatr);

  posicioPatricio = glm::vec3(centreBasePatr[0],maxYPat,centreBasePatr[2]);
  posicioPatricio = TG*glm::vec4(posicioPatricio, 1);

  glUniform3fv(posLoc[2], 1, &posicioPatricio[0]);

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::initializeGL(){
  LL4GLWidget::initializeGL();
  angleXD = 0;
  posLoc[0] = glGetUniformLocation(program->programId(), "posicioCamara");
  posLoc[1] = glGetUniformLocation(program->programId(), "posicioEscena");
  posLoc[2] = glGetUniformLocation(program->programId(), "posicioPatricio");

  colorLoc[0] = glGetUniformLocation(program->programId(), "colorCamara");
  colorLoc[1] = glGetUniformLocation(program->programId(), "colorEscena");
  colorLoc[2] = glGetUniformLocation(program->programId(), "colorPatricio");

  for(unsigned int i = 0; i < sizeof(off)/sizeof(bool); ++i) off[i] = false;
  llums();


}

void MyGLWidget::carregaShaders()
{
  LL4GLWidget::carregaShaders();
  posLoc[0] = glGetUniformLocation(program->programId(), "posicioCamara");
  posLoc[1] = glGetUniformLocation(program->programId(), "posicioEscena");
  posLoc[2] = glGetUniformLocation(program->programId(), "posicioPatricio");

  colorLoc[0] = glGetUniformLocation(program->programId(), "colorCamara");
  colorLoc[1] = glGetUniformLocation(program->programId(), "colorEscena");
  colorLoc[2] = glGetUniformLocation(program->programId(), "colorPatricio");
}
