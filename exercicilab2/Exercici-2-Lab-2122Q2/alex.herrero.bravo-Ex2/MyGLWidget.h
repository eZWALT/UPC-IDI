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
    virtual void iniEscena();
    virtual void iniCamera();
    virtual void paintGL();
    virtual void patrTransform();
    virtual void pilTransform();
    virtual void projectTransform();
    virtual void viewTransform();
    virtual void iniciPilota();
    virtual void tractamentGol();
    virtual void rebotaParets();
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* e);
    bool ortogonal = false;
    bool es_gol = false;
    float girx = M_PI/4.0, giry = 0;
};
