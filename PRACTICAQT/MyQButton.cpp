#include "MyQButton.h"

MyQButton::MyQButton(QWidget * parent): QPushButton(parent){
    setStyleSheet("QPushButton {background-color: gray}");

}

void MyQButton::justpaint(QString color){
    setStyleSheet("QPushButton {background-color: " + color + "}");
    setAutoFillBackground(true);
}

void MyQButton::paint(){
    short random = rand()%4;
    if(random == 0) ColorBetis = "blue";
    else if(random == 1) ColorBetis = "green";
    else if(random == 2) ColorBetis = "yellow";
    else ColorBetis = "red";
    setStyleSheet("QPushButton {background-color: " + ColorBetis + "}");
    setAutoFillBackground(true);
    emit SendColor(ColorBetis);
}

void MyQButton::resetColor(){
    setStyleSheet("QPushButton {background-color: gray}");
}
void MyQButton::start(){
    int r[3] = {rand()%4,rand()%4,rand()%4};
    QString colors[3];
    if(r[0] == r[1] and r[1] == r[2]) emit Trio();

    if(r[0] == 0) colors[0] = "blue";
    else if(r[0] == 1) colors[0] = "green";
    else if(r[0] == 2) colors[0] = "yellow";
    else if (r[0] == 3) colors[0] = "red";

    if(r[1] == 0) colors[1] = "blue";
    else if(r[1] == 1) colors[1] = "green";
    else if(r[1] == 2) colors[1] = "yellow";
    else if (r[1] == 3) colors[1] = "red";

    if(r[2] == 0) colors[2] = "blue";
    else if(r[2] == 1) colors[2] = "green";
    else if(r[2] == 2) colors[2] = "yellow";
    else if (r[2] == 3) colors[2] = "red";

    emit c1(colors[0]);
    emit c2(colors[1]);
    emit c3(colors[2]);
    emit xd(colors);
}
