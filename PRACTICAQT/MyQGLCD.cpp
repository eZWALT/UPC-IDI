#include "MyQGLCD.h"

MyQGLCD::MyQGLCD(QWidget* parent): QLCDNumber(parent){
    display(0);
}

void MyQGLCD::MUDAMUDA(){
    ++trios;
    display(trios);
}

void MyQGLCD::checkTrio(){
    if(cols[2] == cols[1] and cols[1] == cols[0]){
        trios += 1;
        display(trios);
    }
}
//CADA FUNCIO ES PER CADA BOTO INIVIDUAL
void MyQGLCD::button1(QString color1){
    cols[0] = color1;
    checkTrio();
}

void MyQGLCD::button2(QString color2){
    cols[1] = color2;
    checkTrio();
}

void MyQGLCD::button3(QString color3){
    cols[2] = color3;
    checkTrio();
}

void MyQGLCD::start(QString *color){
    for(int i = 0; i < 3; ++i) cols[i] = *(color+i);
}
void MyQGLCD::RRReset(){
    trios = 0;
    display(trios);
}
