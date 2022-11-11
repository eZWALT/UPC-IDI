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

/*

void MyGLWidget::carregaShaders(){
    BL2GLWidget::carregaShaders();
    viewLoc = glGetUniformLocation(program->programId(),"view");
    projLoc = glGetUniformLocation(program->programId(),"proj");

}

*/


void MyGLWidget::keyPressEvent (QKeyEvent *event) {
    makeCurrent();
    switch (event->key()) {
    case Qt::Key_Left: { // escalar a més gran
      angle += 0.2;
      break;
    }
    case Qt::Key_Right: { // escalar a més petit
      angle -= 0.2;
      break;
    }
    case Qt::Key_S: { // escalar a més gran
      scaleFactor += 0.05;
      break;
    }
    case Qt::Key_D: { // escalar a més petit
      scaleFactor -= 0.05;
      break;
    }
    default: event->ignore(); break;
  }
  update();
}

void MyGLWidget::projectTransform(){
    glm::mat4 Proj = glm::perspective(FOV,RA,ZNEAR,ZFAR);
    glUniformMatrix4fv(projLoc,1,GL_FALSE,&Proj[0][0]);
}

void MyGLWidget::viewTransform(){
   glm::mat4 View = glm::lookAt(OBS,VRP,UP);
   glUniformMatrix4fv(viewLoc,1,GL_FALSE,&View[0][0]);
}

void MyGLWidget::modelTransform(){
    glm::mat4 TG = glm::rotate(glm::mat4(1.0), angle, glm::vec3(0,1,0));
    TG = glm::scale(TG,glm::vec3(scaleFactor));
    glUniformMatrix4fv(transLoc,1,GL_FALSE,&TG[0][0]);
}

void MyGLWidget::ini_camera(glm::vec3 obs,glm::vec3 vrp, glm::vec3 up , GLfloat fov ,GLfloat ra, GLfloat znear, GLfloat zfar){
    OBS = obs;
    VRP = vrp;
    UP = up;
    RA = ra;
    FOV = fov;
    ZNEAR = znear;
    ZFAR = zfar;
    projectTransform();
    viewTransform();
}

void MyGLWidget::initializeGL(){
    BL2GLWidget::initializeGL();
    inicialitzaModel();

    ini_camera(glm::vec3(0,0,1), glm::vec3(0,0,0), glm::vec3(0,1,0),float(M_PI)/2.0f,1.0f, 0.4f, 3.0f);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
}


void MyGLWidget::paintGL(){


    glClear (GL_COLOR_BUFFER_BIT);
    modelTransform();
    glBindVertexArray(VAO_MOSQUIS);
    glDrawArrays(GL_TRIANGLES, 0 , homer.faces().size() * 3);


    glm::mat4 TG = glm::translate(glm::mat4(1.0),glm::vec3(0,-0.5,0));
    glUniformMatrix4fv(transLoc,1,GL_FALSE,&TG[0][0]);
    glBindVertexArray(VAO_GESPA);
    glDrawArrays(GL_TRIANGLES,0,6);
    glBindVertexArray(0);

}

void MyGLWidget::inicialitzaModel(){
    homer.load("/home/walterjtv/Escritorio/Assignatures/IDI/models3d/HomerProves.obj");
    glGenVertexArrays(1,&VAO_MOSQUIS);
    glBindVertexArray(VAO_MOSQUIS);

    GLuint VBOS[2];
    GLuint VBOSGESPA[2];
    //MODEL
    glGenBuffers(2,VBOS);
    glBindBuffer(GL_ARRAY_BUFFER,VBOS[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * homer.faces().size() * 3 * 3,homer.VBO_vertices(),GL_STATIC_DRAW);
    glVertexAttribPointer(vertexLoc,3,GL_FLOAT,GL_FALSE,0,0);
    glEnableVertexAttribArray(vertexLoc);
    //COLOR

    glBindBuffer(GL_ARRAY_BUFFER,VBOS[1]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat) * homer.faces().size() * 3 * 3, homer.VBO_matdiff(), GL_STATIC_DRAW);
    glVertexAttribPointer(colorLoc,3,GL_FLOAT,GL_FALSE,0,0);
    glEnableVertexAttribArray(colorLoc);

    glGenVertexArrays(1,&VAO_GESPA);
    glBindVertexArray(VAO_GESPA);
    glGenBuffers(2,VBOSGESPA);
    glBindBuffer(GL_ARRAY_BUFFER,VBOSGESPA[0]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(gespa),gespa,GL_STATIC_DRAW);
    glVertexAttribPointer(vertexLoc,3,GL_FLOAT,GL_FALSE,0,0);
    glEnableVertexAttribArray(vertexLoc);

    glBindBuffer(GL_ARRAY_BUFFER,VBOSGESPA[1]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(gespa),gespa,GL_STATIC_DRAW);
    glVertexAttribPointer(colorLoc,3,GL_FLOAT,GL_FALSE,0,0);
    glEnableVertexAttribArray(colorLoc);


}


void MyGLWidget::carregaShaders()
{
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs (QOpenGLShader::Fragment, this);
  QOpenGLShader vs (QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  fs.compileSourceFile("shaders/basicShader.frag");
  vs.compileSourceFile("shaders/basicShader.vert");
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
  // Obtenim identificador per a l'atribut “color” del vertex shader
  colorLoc = glGetAttribLocation (program->programId(), "color");
  // Uniform locations
  transLoc = glGetUniformLocation(program->programId(), "TG");

  viewLoc = glGetUniformLocation(program->programId(), "view");

  projLoc = glGetUniformLocation(program->programId(), "proj");
}
