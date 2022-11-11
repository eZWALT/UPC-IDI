// MyGLWidget.h
#include "LL4GLWidget.h"

class MyGLWidget : public LL4GLWidget {
  Q_OBJECT
  public:
    MyGLWidget(QWidget *parent=0) : LL4GLWidget(parent) {}
    ~MyGLWidget();
  protected:
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void paintGL();
    virtual void carregaShaders();
    virtual void llums();
    virtual void modelTransformPatricio();
    virtual void initializeGL();


    //EL 0 ES CAMARA
    //EL 1 ES ESCENA
    //EL 2 ES PATRICIO

    glm::vec3 posicioCamara = glm::vec3(0,0,0);
    glm::vec3 posicioEscena = glm::vec3(10,3,5);
    glm::vec3 posicioPatricio = glm::vec3(centreBasePatr[0],maxYPat,centreBasePatr[2]);
    glm::vec3 colorCamara = glm::vec3(0.9,0,0.9);
    glm::vec3 colorEscena = glm::vec3(0.9,0.9,0.9);
    glm::vec3 colorPatricio = glm::vec3(0.9,0.9,0.2);
    GLuint posLoc[3];
    GLuint colorLoc[3];
    bool off[3] = {false,false,false};
    float angleXD = 0;



  private:
    int printOglError(const char file[], int line, const char func[]);
};
