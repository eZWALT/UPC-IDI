#include "ExamGLWidget.h"

class MyGLWidget:public ExamGLWidget
{
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : ExamGLWidget(parent) {}
    ~MyGLWidget();

  public slots:

    void camEuler();
    void camP();
    void changeInt(int p);

  signals:
    void sendP(const int& p);
    void sendEuler(const bool& b);
    void sendPlanta(const bool& b);

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

    virtual void resizeGL(int w, int h);

    void reset();

    bool focus2;
    float angleP = 0.0f;
    int pasos = 0;

  private:
    int printOglError(const char file[], int line, const char func[]);
};
