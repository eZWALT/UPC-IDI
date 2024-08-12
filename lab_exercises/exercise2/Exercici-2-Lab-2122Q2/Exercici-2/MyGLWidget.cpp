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
  // Esborrem el frame-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Patricio
  glBindVertexArray (VAO_Patr);
  patrTransform();
  glDrawArrays(GL_TRIANGLES, 0, patr.faces().size()*3);

  // Pilota
  glBindVertexArray (VAO_Pil);
  pilTransform();

  glDrawArrays(GL_TRIANGLES, 0, pil.faces().size()*3);

  // PARETS
  glBindVertexArray (VAO_Cub);

}

void MyGLWidget::iniEscena(){
  radiEscena = sqrt(150);
  centreEscena = glm::vec3(0,0,0);

  altPorter = 4;
  posPorter = glm::vec3(9.0, 0.0, 0.0);
  posPilota = glm::vec3(7.0, 0.0, 0.0);
  dirInicialPilota();    // direcció inicial de la pilota
}

void MyGLWidget::iniCamera(){
  znear =  10;
  zfar  = 40;
  vrp = glm::vec3(0, 0, 0);
  up = glm::vec3(0, 1, 0);
  obs = glm::vec3(14, 4, 14);
  fov = float(M_PI)/3.0;
  ra  = 1.0;

  viewTransform();
  projectTransform();
}

void MyGLWidget::viewTransform(){

    glm::mat4 VM(1.0);
    if(orto){
      VM = glm::lookAt(glm::vec3(0,10,0),glm::vec3(0,0,0),glm::vec3(-1,0,0));
    }
    else{
      VM = glm::translate(VM,glm::vec3(0,0,-radiEscena*2));
      VM = glm::rotate(VM,theta,glm::vec3(1,0,0));
      VM = glm::rotate(VM,-psi,glm::vec3(0,1,0));
      VM = glm::translate(VM,-vrp);
    }
    glUniformMatrix4fv(viewLoc,1,GL_FALSE,&VM[0][0]);
}

void MyGLWidget::projectTransform(){
    glm::mat4 PM(1.0);
    if(orto) PM = glm::ortho(-radiEscena,radiEscena,-radiEscena,radiEscena,znear-6,zfar);
    else PM = glm::perspective(fov,ra,znear,zfar);
    glUniformMatrix4fv(projLoc,1,GL_FALSE,&PM[0][0]);
}

void MyGLWidget::paintGL(){
  // Esborrem el frame-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Patricio
  glBindVertexArray (VAO_Patr);
  patrTransform();
  glDrawArrays(GL_TRIANGLES, 0, patr.faces().size()*3);
  // Pilota
  if(not gol){
    glBindVertexArray (VAO_Pil);
    pilTransform();
    glDrawArrays(GL_TRIANGLES, 0, pil.faces().size()*3);
  }

  // PARETS
  glBindVertexArray (VAO_Cub);
  for(int k = 0; k < 3; ++k){
    glm::mat4 TG(1.0);
    if(k == 0){
        TG = glm::translate(TG,glm::vec3(0,0,-6.9));
        TG = glm::scale(TG,glm::vec3(20,2,0.2));

    }
    else if(k == 1){
        TG = glm::translate(TG,glm::vec3(0,0,6.9));
        TG = glm::scale(TG,glm::vec3(20,2,0.2));
    }
    else{
        TG = glm::translate(TG,glm::vec3(-9.9,0,0));
        TG = glm::scale(TG,glm::vec3(0.2,2,14));
    }
    glUniformMatrix4fv(transLoc,1,GL_FALSE,&TG[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, 36);
  }

  // Terra
  glBindVertexArray (VAO_Terra);
  identTransform();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glBindVertexArray (0);
}

void MyGLWidget::patrTransform(){
    glm::mat4 TG(1.0);
    TG = glm::translate(TG,posPorter);
    TG = glm::rotate(TG,float(-M_PI/2.0),glm::vec3(0,1,0));
    TG = glm::scale(TG,glm::vec3(escalaPatr*altPorter, altPorter*escalaPatr, altPorter*escalaPatr));
    TG = glm::translate(TG,-centreBasePatr);

    glUniformMatrix4fv(transLoc,1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::rebotaParets(){
    if(abs(posPilota[2]) >= 6) dirPilota[2] = -dirPilota[2]; //XOC LATERAL
    if(posPilota[0] <= -9) dirPilota[0] = -dirPilota[0]; //XOC FRONTAL
    //if(posPilota[0] >= 9) dirPilota[0] = -dirPilota[0]; //XDD
}

void MyGLWidget::iniciPilota()
{
  timer.stop();
  posPilota = glm::vec3(7.0, 0.0, 0.0);
  dirInicialPilota();    // direcció inicial de la pilota
  gol = false;
}

void MyGLWidget::tractamentGol()
{
  timer.stop();
  gol = true;
}


void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();

  theta += factorAngleX * (e ->y() - yClick);
  psi += factorAngleY * (e ->x() - xClick);
  viewTransform();
  xClick = e->x();
  yClick = e->y();

  update ();
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
    case Qt::Key_Right: {
        float limit = 7-(altPorter/2.0);
        if(posPorter[2] > -limit) posPorter[2] -= 0.5;
        break;
    }
    case Qt::Key_Left: {
        float limit = 7-(altPorter/2.0);
        if(posPorter[2] < limit) posPorter[2] += 0.5;
        break;
    }
    case Qt::Key_C: {
      orto = !orto;
      viewTransform();
      projectTransform();
      break;
    }
    case Qt::Key_W: {
      if(altPorter < 6) ++altPorter;
      break;
    }
    case Qt::Key_S: {
      if(altPorter > 2) --altPorter;
      break;
    }
    case Qt::Key_R:{
      iniciPilota();
      posPorter = glm::vec3(9.0, 0.0, 0.0);
      orto = false;
      psi = 0;
      altPorter = 4;
      theta = M_PI/4;

      viewTransform();
      projectTransform();
      break;
    }
    default: event->ignore(); break;
  }
  update();
}

