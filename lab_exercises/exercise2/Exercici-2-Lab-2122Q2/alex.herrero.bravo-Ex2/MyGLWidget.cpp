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

MyGLWidget::~MyGLWidget()
{

}

void MyGLWidget::iniEscena()
{
  radiEscena = sqrt(149);
  centreEscena = glm::vec3(0,0,0);

  altPorter = 4;
  posPorter = glm::vec3(9.0, 0.0, 0.0);  // posició inicial del porter
  posPilota = glm::vec3(7.0, 0.0, 0.0);  // posició inicial de la pilota
  dirInicialPilota();    // direcció inicial de la pilota
}

void MyGLWidget::iniCamera()
{
  obs = glm::vec3(14, 4, 14);
  vrp = glm::vec3(0, 0, 0);
  up = glm::vec3(0, 1, 0);
  fov = float(M_PI)/3.0f;
  ra  = 1.0;
  znear =  10;
  zfar  = 40;

  viewTransform();
  projectTransform();

}

void MyGLWidget::paintGL()
{
  // descomentar per canviar paràmetres
  // glViewport (0, 0, ample, alt);

  // Esborrem el frame-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Patricio
  glBindVertexArray (VAO_Patr);
  patrTransform();
  glDrawArrays(GL_TRIANGLES, 0, patr.faces().size()*3);

  // Pilota
  glBindVertexArray (VAO_Pil);
  pilTransform();
  if (not es_gol) glDrawArrays(GL_TRIANGLES, 0, pil.faces().size()*3);

  // Cub

    glBindVertexArray (VAO_Cub); 
    for (unsigned int i = 0; i < 3; ++i) {

        glm::mat4 TG(1.0f);
        glm::vec3 pos_pared;
        glm::vec3 esc_pared;

        switch (i) {

            case 0:
                pos_pared = glm::vec3(0,0, -6.9);
                esc_pared = glm::vec3(20,2,0.2);
                break;
            
            case 1:
                pos_pared = glm::vec3(0,0,6.9);
                esc_pared = glm::vec3(20,2,0.2);
                break;

            case 2:
                pos_pared = glm::vec3(-9.9, 0 , 0);
                esc_pared = glm::vec3(0.2,2,14);
                break;

        }

        TG = glm::translate(TG, pos_pared);
        TG = glm::scale(TG, esc_pared);
        glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

  // Terra
    glBindVertexArray (VAO_Terra);
    identTransform();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  

  glBindVertexArray (0);
}


void MyGLWidget::patrTransform ()
{
  glm::mat4 TG(1.0f);
  TG = glm::translate(TG, posPorter);
  TG = glm::rotate(TG, float(M_PI/2.0), glm::vec3(0,-1,0));
  TG = glm::scale(TG, glm::vec3(altPorter*escalaPatr, altPorter*escalaPatr, altPorter*escalaPatr));
  TG = glm::translate(TG, -centreBasePatr);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::pilTransform ()
{
  glm::mat4 TG(1.f);

  TG = glm::translate(TG, posPilota);
  TG = glm::scale(TG, glm::vec3(escalaPil, escalaPil, escalaPil));
  TG = glm::translate(TG, -centreBasePil);

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}


void MyGLWidget::projectTransform ()
{
  glm::mat4 Proj(1.0f);
  if (not ortogonal) Proj = glm::perspective (fov, ra, znear, zfar);
  else Proj = glm::ortho(-radiEscena,radiEscena,-radiEscena,radiEscena,znear - 6,zfar);
  glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::viewTransform ()
{
  // Matriu de posició i orientació de l'observador
  glm::mat4 View(1.0f);
  if (not ortogonal){
  View = glm::translate(View, glm::vec3(0,0, -2*radiEscena));
  View = glm::rotate(View, giry, glm::vec3(0,1,0));
  View = glm::rotate(View, girx, glm::vec3(1,0,0));
  View = glm::translate(View, -vrp);
  }
  else View = glm::lookAt(glm::vec3(0,10,0), glm::vec3(0,0,0), glm::vec3(-1,0,0));

  glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);

}


void MyGLWidget::iniciPilota()
{
  timer.stop();
  posPilota = glm::vec3(7.0, 0.0, 0.0);
  es_gol = false;
  dirInicialPilota();    // direcció inicial de la pilota
}


void MyGLWidget::tractamentGol()
{
  es_gol = true;
  timer.stop();
} 


void MyGLWidget::keyPressEvent(QKeyEvent* event) 
{
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_Up: { // moviment de la pilota
      if (posPilota[0] == 7.0)
        mourePilota ();
      break;
    }
    case Qt::Key_I: { // reinicia posició pilota
      iniciPilota ();
      break;
    }
    case Qt::Key_Left:
            if (posPorter[2] > -(7-(altPorter/2))) posPorter[2] -= 0.5;
            break;
    case Qt::Key_Right:
            if (posPorter[2] < 7-(altPorter/2)) posPorter[2] += 0.5;
            break;
    case Qt::Key_C:
            ortogonal = not ortogonal;
            viewTransform();
            projectTransform();
                break;
    case Qt::Key_W: if (altPorter < 6) ++altPorter;
                break;
    case Qt::Key_S: if (altPorter > 2) --altPorter;
                break;
    case Qt::Key_R:
            altPorter = 4;
            ortogonal = not ortogonal;
            iniciPilota();
            posPorter = glm::vec3(9.0,0.0,0.0);
            ortogonal = false;
            girx = M_PI/4.0;
            giry = 0;
            viewTransform();
            projectTransform();
            break;
    default: event->ignore(); break;
  }
  update();
}



void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();

  girx += factorAngleX * (e ->y() - yClick);
  giry += factorAngleY * (e ->x() - xClick);
  viewTransform();
  xClick = e->x();
  yClick = e->y();

  update ();
}


void MyGLWidget::rebotaParets() 
{
    if (posPilota[0] < -9.0) dirPilota[0] = -dirPilota[0];
    if (abs(posPilota[2]) > 6.0) dirPilota[2] = -dirPilota[2];

} 


