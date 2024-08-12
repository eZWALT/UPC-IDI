#include "ExamGLWidget.h"

class MyGLWidget:public ExamGLWidget
{
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : ExamGLWidget(parent) {}
    ~MyGLWidget();

  public slots:
   void rep_altura(int a);
   void camaraAvio();
   void camaraPatricio();

  signals:
    void posa_camara1();
    void posa_camara2();
    void cambia_altura(int a);

  protected:
    virtual void paintGL ();
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void mouseMoveEvent (QMouseEvent *event);

    virtual void resizeGL(int w,int h);
    virtual void modelTransformPatricio ();
    virtual void modelTransformAvio ();
    virtual void iniEscena ();
    virtual void iniCamera ();
    virtual void projectTransform ();
    virtual void viewTransform ();
    virtual void enviaPosFocus ();
    virtual void iniMaterialTerra ();

    void carregaShaders();

    bool iluminaculavio = false;
    bool camara2 = false;
    glm::mat4 TGpatricio;
    float angleAvio = 0;
    int alturaAvio = 0;

  private:
    int printOglError(const char file[], int line, const char func[]);
};
