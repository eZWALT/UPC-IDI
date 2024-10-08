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

void MyGLWidget::viewTransform ()
{

    changeLights();

  View = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -2*radiEsc));
  View = glm::rotate(View, +angleY, glm::vec3(0, 1, 0));
  View = glm::rotate(View, +angleX, glm::vec3(1,0,0));

  glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::carregaShaders()
{
    BL3GLWidget::carregaShaders();
    
    SCO_Loc = glGetUniformLocation(program->programId(), "SCObool");
    CF_Loc = glGetUniformLocation (program->programId(), "colorFocus");
    PF_Loc = glGetUniformLocation (program->programId(), "posFocus");
}

void MyGLWidget::initializeGL(){
    BL3GLWidget::initializeGL();

    colorFocus = glm::vec3(0.8f, 0.8f, 0.8f);
    posFocus = glm::vec3(1.f,0.f,1.f); // En SCA

    changeLights();
}

void MyGLWidget::changeLights(){
    //std::cout << colorFocus.x << colorFocus.y << colorFocus.z << std::endl;
    glUniform3fv(CF_Loc, 1, &colorFocus[0]);
    glUniform3fv(PF_Loc, 1, &posFocus[0]);
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();
  // Aqui cal que es calculi i s'apliqui la rotacio o el zoom com s'escaigui...
  if (DoingInteractive == ROTATE)
  {
    // Fem la rotació
    angleY += (e->x() - xClick) * M_PI / ample;
    angleX += (e->y() - yClick) * M_PI / alt;
    viewTransform ();
  }

  xClick = e->x();
  yClick = e->y();

  update ();
}


void MyGLWidget::iniMaterialTerra ()
{
  // Donem valors al material del terra
  amb = glm::vec3(0.2,0,0.2);
  diff = glm::vec3(0,0,0.8);
  spec = glm::vec3(1,1,1);
  shin = 100;
}


void MyGLWidget::keyPressEvent(QKeyEvent* event) {
  makeCurrent();
  switch (event->key()) {
      case Qt::Key_K:
        posFocus = glm::vec3(posFocus.x - .5f, posFocus.y, posFocus.z);
        changeLights();
        break;
      case Qt::Key_L:
        posFocus = glm::vec3(posFocus.x + .5f, posFocus.y, posFocus.z);
        changeLights();
        break;
      case Qt::Key_F:
        SCO = not SCO;
        glUniform1i(SCO_Loc,SCO);
        if(SCO) posFocus = glm::vec3(1,1,1);
        else posFocus = glm::vec3(0,0,0);
        break;
          
    default: BL3GLWidget::keyPressEvent(event); break;
  }
  update();
}
