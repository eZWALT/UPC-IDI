// MyGLWidget.h
#include "BL2GLWidget.h"
#include "model.h"

class MyGLWidget : public BL2GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : BL2GLWidget(parent) {}
    ~MyGLWidget();
    
  protected:
      
    virtual void initializeGL();
    virtual void carregaShaders();
    virtual void projectTransform();
    virtual void viewTransform();
    virtual void paintGL();
    virtual void carregaModel();
    virtual void keyPressEvent (QKeyEvent *event);
    virtual void modelTransform();
    
    
  private:
    int printOglError(const char file[], int line, const char func[]);
    GLuint projLoc;
    GLuint viewLoc;
    Model m;
    GLuint VAO_homer;
    float angle;
    GLuint VAO_terra;
};
