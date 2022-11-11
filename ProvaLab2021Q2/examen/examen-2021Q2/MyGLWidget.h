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
    virtual void mouseMoveEvent (QMouseEvent *event);

    virtual void modelTransformPatricio ();
    virtual void enviaPosFocus ();
    virtual void iniEscena ();
    virtual void iniCamera ();
    virtual void projectTransform ();
    virtual void viewTransform ();
    void carregaShaders ();
    
    
    bool f = false;
    GLuint fLoc;
    float anglePat = 0.0f;

  private:
    int printOglError(const char file[], int line, const char func[]);
    
public slots:
    void GirPat(int g);
    void Persp();
    void Ortho();
    void changeFov(int x);
};
