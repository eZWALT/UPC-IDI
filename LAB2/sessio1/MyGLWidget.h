// MyGLWidget.h
#include "BL2GLWidget.h"
#include "model.h"

class MyGLWidget : public BL2GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : BL2GLWidget(parent) {}
    ~MyGLWidget();
    
    virtual void carregaShaders();
    
    virtual void initializeGL();
    
    virtual void projectTransform();
    
    virtual void viewTransform();

    virtual void modelTransform();
    
    virtual void ini_camera(glm::vec3 obs,glm::vec3 vrp, glm::vec3 up,GLfloat fov, GLfloat ra, GLfloat znear, GLfloat zfar);

    virtual void paintGL();

    virtual void inicialitzaModel();

    virtual void keyPressEvent (QKeyEvent *event);
    
    

  private:
    int printOglError(const char file[], int line, const char func[]);
    
    GLuint vertexLoc,colorLoc,viewLoc,projLoc,transLoc; //LOCATIONS
    GLuint VAO_MOSQUIS,VAO_GESPA;
    glm::vec3 gespa[6] = {
      glm::vec3(1.0,-0.5,-1.0),
      glm::vec3(-1.0,-0.5,1.0),
      glm::vec3(-1.0,-0.5,-1.0),
      glm::vec3(1.0,-0.5,1.0),
      glm::vec3(1.0,-0.5,-1.0),
      glm::vec3(-1.0,-0.5,1.0),
    };
    
    GLfloat FOV,RA,ZNEAR,ZFAR;
    glm::vec3 OBS,VRP,UP;
    GLfloat scaleFactor = 1,angle = 0;

    Model homer;
    Model floppa;
    
    
};
