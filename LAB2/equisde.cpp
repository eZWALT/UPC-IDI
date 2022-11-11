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

void MyGLWidget::paintGL ()
{
// En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
// useu els paràmetres que considereu (els que hi ha són els de per defecte)
//  glViewport (0, 0, ample, alt);

  // Esborrem el frame-buffer
  glClear (GL_COLOR_BUFFER_BIT);

  // Carreguem la transformació de model
  modelTransform ();

  // Activem el VAO per a pintar la caseta
  glBindVertexArray (VAO_homer);
  glDrawArrays (GL_TRIANGLES, 0, m.faces ().size () * 3);

  // pintem
  //glDrawArrays(GL_TRIANGLES, 0, 9);

  glm::mat4 TG = glm::translate(glm::mat4(1.), glm::vec3(0, -0.5, 0));
  TG = glm::scale(TG, glm::vec3(2., 1., 2.));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
  glBindVertexArray (VAO_terra);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray (0);
}

void MyGLWidget::carregaModel() {
    m.load("../models/HomerProves.obj");
    glGenVertexArrays(1, &VAO_homer);
    glBindVertexArray(VAO_homer);

    GLuint VBO_homer[2];
    glGenBuffers(2, VBO_homer);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_homer[0]);
    glBufferData (GL_ARRAY_BUFFER,sizeof(GLfloat) * m.faces ().size () * 3 * 3,m.VBO_vertices (), GL_STATIC_DRAW);
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_homer[1]);
    glBufferData (GL_ARRAY_BUFFER, sizeof(GLfloat) * m.faces ().size () * 3 * 3, m.VBO_matdiff (), GL_STATIC_DRAW);

    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorLoc);

    glm::vec3 terra[6] = {
        glm::vec3(1.0, -0.5, -1.0),
        glm::vec3(-1.0, -0.5, 1.0),
        glm::vec3(-1.0, -0.5, -1.0),
        glm::vec3(1.0, -0.5, 1.0),
        glm::vec3(1.0, -0.5, -1.0),
        glm::vec3(-1.0, -0.5, 1.0),
    };


    glGenVertexArrays(1, &VAO_terra);
    glBindVertexArray(VAO_terra);
    GLuint VBO_terra;
    glGenBuffers(1, &VBO_terra);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_terra);
    glBufferData (GL_ARRAY_BUFFER, sizeof(terra), terra, GL_STATIC_DRAW);
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);

}

void MyGLWidget::keyPressEvent (QKeyEvent *event) {
    makeCurrent();
    switch (event->key()) {
    case Qt::Key_Left: { // escalar a més gran
      angle += 0.05;
      break;
    }
    case Qt::Key_Right: { // escalar a més petit
      angle -= 0.05;
      break;
    }
    case Qt::Key_S: { // escalar a més gran
      escala += 0.05;
      break;
    }
    case Qt::Key_D: { // escalar a més petit
      escala -= 0.05;
      break;
    }
    default: event->ignore(); break;
  }
  update();
}

void MyGLWidget::modelTransform() {
    glm::mat4 TG = glm::rotate(glm::mat4(1.), angle, glm::vec3(0., 1., 0.));
    TG = glm::scale(TG, glm::vec3(escala));
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::initializeGL(){
    BL2GLWidget::initializeGL();
    projectTransform();
    carregaModel();
    viewTransform();
    glEnable (GL_DEPTH_TEST);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MyGLWidget::viewTransform () {
    glm::mat4 View = glm::lookAt (OBS,VRP,UP);
    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::projectTransform () {
    glm::mat4 Proj = glm::perspective (FOV, RA,ZNEAR, ZFAR);
    glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}
void MyGLWidget::carregaShaders() {
    BL2GLWidget::carregaShaders();
    projLoc = glGetUniformLocation (program->programId(), "PM");
    viewLoc = glGetUniformLocation (program->programId(), "VM");
}

MyGLWidget::~MyGLWidget() {
}
