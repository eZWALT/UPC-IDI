#include "MyGLWidget.h"

#include <iostream>


MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL)
{
  setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
}

MyGLWidget::~MyGLWidget ()
{
  if (program != NULL)
    delete program;
}

void MyGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();
  
  glClearColor (0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  creaBuffersQuadrat();
  creaBuffersTriangle();
}

void MyGLWidget::pintaMuntanya ()  // Caldrà modificar aquest mètode per pintar la muntanya
{

  glm::vec3 color = glm::vec3(0.5,0.3,0.1);
  glUniform3fv(colorLoc,1,&color[0]);

  glm::mat4 TG = glm::mat4(1.0);
  TG = translate(TG, glm::vec3(-1,-1,0));
  TG = scale(TG, glm::vec3(1.6,1.8,1.0));

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
  glBindVertexArray(VAOTriangle);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  TG = glm::mat4(1.0);
  TG = translate(TG,glm::vec3(-0.4,0.4,0));
  TG = scale(TG,glm::vec3(0.4,0.4,1.0));
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);

  color = glm::vec3(1,1,1);
  glUniform3fv(colorLoc,1,&color[0]);
  // pintem un triangle
  glBindVertexArray(VAOTriangle);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  TG = glm::mat4(1.0);
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
  color = glm::vec3(0);
  glUniform3fv(colorLoc,1,&color[0]);
}

void MyGLWidget::pintaBaseGronxador(){
  glm::mat4 TG = glm::mat4(1.0);
  TG = translate(TG,glm::vec3(-0.1,-1,0));
  TG = scale(TG,glm::vec3(0.2,0.3,1.0));
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);

  glm::vec3 color = glm::vec3(0.7,0,0);
  glUniform3fv(colorLoc,1,&color[0]);
  // pintem un triangle
  glBindVertexArray(VAOTriangle);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  //RESETEJEM TOT A DEFAULT
  color = glm::vec3(0,0,0);
  glUniform3fv(colorLoc,1,&color[0]);
  TG = glm::mat4(1.0);
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);


}

void MyGLWidget::pintaGronxador ()  
{ // Caldrà modificar aquest mètode per pintar el gronxador sencer, la barra i els dos seients
  // pintem un quadrat

  glm::mat4 TG = glm::mat4(1.0);
  TG = translate(TG, glm::vec3(0,-0.7,0));
  TG *= GirGronxador;
  TG = translate(TG, glm::vec3(0.7,0.2,0));
  TG = scale(TG, glm::vec3(2.8,0.4,1.0));
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);

  glm::vec3 color = glm::vec3(0.2,0.7,0.2);
  glUniform3fv(colorLoc,1,&color[0]);

  glBindVertexArray(VAOQuadrat);
  glDrawArrays(GL_TRIANGLES, 0, 6);

  color = glm::vec3(0.4,0.4,0.4);
  glUniform3fv(colorLoc,1,&color[0]);

//PARA LA PROXIMA HACER DIBUJOS CONRADOARBOL CONRADOARBOL CONRADOARBOL CONRADOARBOL CONRADOARBOL CONRADOARBOL CONRADOARBOL CONRADOARBOL CONRADOARBOL CONRADOARBOL CONRADOARBOLCONRADOARBOL

  TG = glm::mat4(1.0);
  TG = translate(TG, glm::vec3(0,-0.7,0));
 // TG = translate(TG, glm::vec3(-0.5,-0.4,0));
  TG *= GirGronxador;
  TG = translate(TG,glm::vec3(0.7,0.3,0));
  TG = scale(TG, glm::vec3(0.4,0.2,1.0));
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
  glDrawArrays(GL_TRIANGLES, 0, 6);

  TG = glm::mat4(1.0);
  TG = translate(TG, glm::vec3(0,-0.7,0));
  TG *= GirGronxador;
  TG = translate(TG, glm::vec3(-0.5,0.3,0));
  TG = scale(TG, glm::vec3(0.4,0.2,1.0));
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
  glDrawArrays(GL_TRIANGLES, 0, 6);


  //RESETEJEM TOT A DEFAULT
  color = glm::vec3(0,0,0);
  glUniform3fv(colorLoc,1,&color[0]);
  TG = glm::mat4(1.0);
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);


}

void MyGLWidget::paintGL ()
{
// En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
// useu els paràmetres que considereu (els que hi ha són els de per defecte)
//  glViewport (0, 0, ample, alt);
  
  glClear (GL_COLOR_BUFFER_BIT);  // Esborrem el frame-buffer

  // Pintem muntanya
  pintaMuntanya();
  pintaBaseGronxador();
  transformGirGronxador();
  pintaGronxador();
  
  // Desactivem el VAO
  glBindVertexArray(0);
}

void MyGLWidget::resizeGL (int w, int h)
{
// Aquest codi és necessari únicament per a MACs amb pantalla retina.
#ifdef __APPLE__
  GLint vp[4];
  glGetIntegerv (GL_VIEWPORT, vp);
  ample = vp[2];
  alt = vp[3];
#else
  ample = w;
  alt = h;
#endif
}

void MyGLWidget::keyPressEvent(QKeyEvent* event)
{
  makeCurrent();
  switch (event->key()) {
      case Qt::Key_Right :
           angleGir -= 5;
           //glUniform1f
           break;

      case Qt::Key_Left :
          angleGir += 5;
          break;

      default: event->ignore(); break;
  }
  if(angleGir > 25) angleGir = 25;
  if(angleGir < -25) angleGir = -25; //comprovem que no pasi dels 25 graus esmentats
  update();
}

void MyGLWidget::transformGirGronxador ()
{
  GirGronxador = glm::mat4(1.0);
  GirGronxador = glm::rotate(GirGronxador, glm::radians(angleGir), glm::vec3(0,0,1)); //gir * R
}

void MyGLWidget::creaBuffersQuadrat ()
{
  glm::vec3 Vertices[6];  // vèrtexs amb X, Y i Z
  Vertices[0] = glm::vec3(-0.5, -0.5, 0);
  Vertices[1] = glm::vec3( 0, -0.5, 0);
  Vertices[2] = glm::vec3(-0.5, 0, 0);
  Vertices[3] = glm::vec3( 0, -0.5, 0);
  Vertices[4] = glm::vec3( 0, 0, 0);
  Vertices[5] = glm::vec3( -0.5, 0, 0);
  
  // Creació del Vertex Array Object (VAO) que usarem per pintar el tronc
  glGenVertexArrays(1, &VAOQuadrat);
  glBindVertexArray(VAOQuadrat);

  // Creació del buffer amb les dades dels vèrtexs
  GLuint VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
  // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)	
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Desactivem el VAO
  glBindVertexArray(0);
}

void MyGLWidget::creaBuffersTriangle ()
{
  glm::vec3 Vertices[3];  // Quatre vèrtexs amb X, Y i Z
  Vertices[0] = glm::vec3( 0, 0, 0);
  Vertices[1] = glm::vec3( 1, 0, 0);
  Vertices[2] = glm::vec3( 0.5, 1, 0);

  // Creació del Vertex Array Object (VAO) que usarem per pintar el tronc
  glGenVertexArrays(1, &VAOTriangle);
  glBindVertexArray(VAOTriangle);

  // Creació del buffer amb les dades dels vèrtexs
  GLuint VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
  // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Desactivem el VAO
  glBindVertexArray(0);
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
  transLoc = glGetUniformLocation(program->programId(), "TG");
  colorLoc = glGetUniformLocation(program->programId(), "color");
  // Obtenim els identificadors dels uniforms
  //...
}
