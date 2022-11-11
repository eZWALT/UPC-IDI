#include "ExamGLWidget.h"

class MyGLWidget:public ExamGLWidget
{
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : ExamGLWidget(parent) {}
    ~MyGLWidget();

  public slots:
      void cambiar_ortogonal();
      void cambiar_perspectiva();
      void cambiar3();
      void cambiar2();
      void cambiar1();

  signals:
      void reinicia();
      void cambioOrtogonal();
      void cambioPerspectiva();

  protected:
    virtual void paintGL ();
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void modelTransformCub (float escala, float angle);
    virtual void modelTransformPatricio ();
    virtual void projectTransform ();
    virtual void viewTransform ();

  private:
    int printOglError(const char file[], int line, const char func[]);
    float angle_patricio = 0;
    float angulo_base = 0;
    bool pintar_patricio = false;
    bool camPlanta = false;
    bool amarillo = false;
};
