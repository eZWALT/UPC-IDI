#include "ExamGLWidget.h"

class MyGLWidget:public ExamGLWidget
{
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : ExamGLWidget(parent) {}
    ~MyGLWidget();

signals:
  void step();
  void euler();
  void planta();
  void reset();

public slots:
  void carlos();
  void cambia_ortogonal();
  void cambia_perspectiva();

  protected:
    virtual void paintGL ();
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void mouseMoveEvent (QMouseEvent *event);
    virtual void resizeGL(int width,int height);

    virtual void modelTransformPatricio ();
    virtual void enviaPosFocus ();
    virtual void iniEscena ();
    virtual void iniCamera ();
    virtual void projectTransform ();
    virtual void viewTransform ();

    bool focusCamara = true;
    glm::vec3 obs;
    float anglePat = 0;

  private:
    int printOglError(const char file[], int line, const char func[]);
};
