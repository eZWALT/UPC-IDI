#include <QLCDNumber>

class MyQGLCD: public QLCDNumber{

    Q_OBJECT

    public:
        MyQGLCD(QWidget* parent);
        void checkTrio();

    public slots:
    void RRReset();
    void button1(QString color1);
    void button2(QString color2);
    void button3(QString color3);
    void start(QString *color);
    void MUDAMUDA();

    private:
        int trios = 0;
        QString cols[3] = {"idi","esta finarda", "ironia"};

    signals:

};
