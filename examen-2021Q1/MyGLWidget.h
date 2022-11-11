#include "ExamGLWidget.h"

class MyGLWidget:public ExamGLWidget
{
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : ExamGLWidget(parent) {}
    ~MyGLWidget();

  protected:
    virtual void paintGL ();
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void modelTransformCub (float escala, float angle);
    virtual void modelTransformPatricio ();
    virtual void projectTransform ();
    virtual void viewTransform ();
    virtual void initializeGL();

  private:
    int printOglError(const char file[], int line, const char func[]);
    float anglePatricio = M_PI/2;
    float baseAngle = 2*M_PI/3;
    bool paintPatricio = false;
    bool colorXD = false;
};
