#include "LL2GLWidget.h"

#include "model.h"

class MyGLWidget : public LL2GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : LL2GLWidget(parent) {}
    ~MyGLWidget();

  private:
    int printOglError(const char file[], int line, const char func[]);

  protected:
    virtual void patrTransform();
    virtual void paintGL();
    virtual void iniCamera();
    virtual void iniEscena();

    virtual void viewTransform();
    virtual void projectTransform();
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void keyPressEvent(QKeyEvent* event);

    virtual void iniciPilota();
    virtual void tractamentGol();

    virtual void rebotaParets();

    float theta = M_PI/4.0, psi = 0;
    bool gol = false;
    bool orto = false;

};
