#include <QPushButton>

class MyQButton: public QPushButton {

    Q_OBJECT

    public:
        MyQButton(QWidget* parent);

    public slots:
        void paint();
        void justpaint(QString color);
        void resetColor();
        void start();
    private:
        QString ColorBetis;

    signals:
        void SendColor(QString);
        void Trio();
        void c1(QString);
        void c2(QString);
        void c3(QString);
        void xd(QString*);

};

