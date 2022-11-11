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

void MyGLWidget::paintGL ()   // Mètode que has de modificar
{
  
  // Esborrem el frame-buffer i el depth-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Pintem el terra
  glBindVertexArray (VAO_Terra);
  modelTransformTerra ();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  // Pintem el Patricio
  glBindVertexArray (VAO_Patr);
  if (pintar_patricio) {
  modelTransformPatricio ();
  glDrawArrays(GL_TRIANGLES, 0, patr.faces().size()*3);
  }

  // Pintem el cub
  else {
  glBindVertexArray(VAO_Cub);
  modelTransformCub (2, angulo_base);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  modelTransformCub (2.5, angulo_base + 2*M_PI/3.0);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  modelTransformCub (3.0, angulo_base -2*M_PI/3.0);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  }
  glBindVertexArray(0);
}

void MyGLWidget::modelTransformCub (float escala, float angle) 
{
    glm::mat4 TG(1.f);
    escala *= 2;
    TG = glm::rotate(TG, angle, glm::vec3(0,1,0));
    TG = glm::translate(TG, glm::vec3(5,0,0));
    TG = glm::scale(TG, glm::vec3(escala, escala, escala));
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);

}

void MyGLWidget::modelTransformPatricio ()    // Mètode que has de modificar
{
    glm::mat4 TG(1.f);
    TG = glm::rotate(TG, angle_patricio, glm::vec3(0,1,0));
    TG = glm::translate(TG, glm::vec3(5,0,0));
    TG = glm::rotate(TG, (float) glm::radians(90.0), glm::vec3(0,-1,0));
    TG = glm::scale(TG, glm::vec3(2*escala, 2*escala, 2*escala));
    TG = glm::translate(TG, -centreBasePat);
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::viewTransform ()    // Mètode que has de modificar
{
  if (!camPlanta)
    ExamGLWidget::viewTransform();
  else
  {
      glm::mat4 View = glm::lookAt(glm::vec3(0,radiEsc,0), glm::vec3(0,0,0), glm::vec3(1,0,0));
      glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
  }
}

void MyGLWidget::projectTransform ()
{
  if (!camPlanta)
    ExamGLWidget::projectTransform();
  else
  {
      glm::mat4 Proj = glm::ortho(-radiEsc, radiEsc, -radiEsc, radiEsc, 0.0f, 2.0f*radiEsc);
      glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
  }
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) {
  makeCurrent();
  switch (event->key()) {
  case Qt::Key_V: {
    pintar_patricio = not pintar_patricio;
    break;
	}
  case Qt::Key_1: {
    angle_patricio = 0;
    break;
	}
  case Qt::Key_2: {
    angle_patricio = 2*M_PI/3.0; 
    break;
	}
  case Qt::Key_3: {
    angle_patricio = -2*M_PI/3.0; 
    break;
	}
  case Qt::Key_F: {
	  amarillo = not amarillo;
	  glm::vec3 color;

	  if (amarillo) colFoc = glm::vec3(1,1,0);
	  else colFoc = glm::vec3(1,1,1);
	  ExamGLWidget::enviaColFocus();
    break;
	}
  case Qt::Key_C: {
    camPlanta = not camPlanta;
    if (camPlanta) emit cambioOrtogonal();
    else emit cambioPerspectiva();
    break;
	}
  case Qt::Key_Right: {
    angle_patricio -= 2*M_PI/3.0; 
    angulo_base-= 2*M_PI/3.0; 
    break; 
    }
  case Qt::Key_Left: {
    angle_patricio += 2*M_PI/3.0; 
    angulo_base += 2*M_PI/3.0; 
    break;
    }
  case Qt::Key_R: {
    angulo_base = 0.0;
    colFoc = glm::vec3 (1.0,1.0,1.0);
    ExamGLWidget::enviaColFocus();
    emit reinicia();
    break;
	}
  default: ExamGLWidget::keyPressEvent(event); break;
  }
  update();
}



void MyGLWidget::cambiar_perspectiva() {

    makeCurrent();
    camPlanta = false;
    viewTransform();
    projectTransform();
    update();
    setFocus();

}

void MyGLWidget::cambiar_ortogonal() {

    makeCurrent();
    camPlanta = true;
    viewTransform();
    projectTransform();
    update();
    setFocus();

}


void MyGLWidget::cambiar3() {
    makeCurrent();
    angle_patricio = angulo_base - 2*M_PI/3.0;
    update();
    setFocus();

}
void MyGLWidget::cambiar2() {
    makeCurrent();
    angle_patricio =angulo_base + 2*M_PI/3.0;
    update();
    setFocus();
}

void MyGLWidget::cambiar1() {
    makeCurrent();
    angle_patricio = angulo_base;
    update();
    setFocus();
}
