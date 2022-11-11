/********************************************************************************
** Form generated from reading UI file 'MyForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYFORM_H
#define UI_MYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "MyGLWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MyForm
{
public:
    QHBoxLayout *horizontalLayout;
    MyGLWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_7;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_2;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_2;
    QFrame *frame;
    QVBoxLayout *verticalLayout_8;
    QLabel *label;
    QRadioButton *radioButton_5;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton;

    void setupUi(QWidget *MyForm)
    {
        if (MyForm->objectName().isEmpty())
            MyForm->setObjectName(QString::fromUtf8("MyForm"));
        MyForm->resize(1083, 726);
        horizontalLayout = new QHBoxLayout(MyForm);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget = new MyGLWidget(MyForm);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(50, 50));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));

        horizontalLayout->addWidget(widget);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        frame_2 = new QFrame(MyForm);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_9 = new QVBoxLayout(frame_2);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        label_2 = new QLabel(frame_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_9->addWidget(label_2);

        radioButton_4 = new QRadioButton(frame_2);
        radioButton_4->setObjectName(QString::fromUtf8("radioButton_4"));
        radioButton_4->setChecked(true);

        verticalLayout_9->addWidget(radioButton_4);

        radioButton_2 = new QRadioButton(frame_2);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        verticalLayout_9->addWidget(radioButton_2);


        verticalLayout_7->addWidget(frame_2);

        frame = new QFrame(MyForm);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_8 = new QVBoxLayout(frame);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_8->addWidget(label);

        radioButton_5 = new QRadioButton(frame);
        radioButton_5->setObjectName(QString::fromUtf8("radioButton_5"));
        radioButton_5->setChecked(true);

        verticalLayout_8->addWidget(radioButton_5);

        radioButton_3 = new QRadioButton(frame);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));

        verticalLayout_8->addWidget(radioButton_3);

        radioButton = new QRadioButton(frame);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));

        verticalLayout_8->addWidget(radioButton);


        verticalLayout_7->addWidget(frame);


        verticalLayout_6->addLayout(verticalLayout_7);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer);

        pushButton = new QPushButton(MyForm);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_6->addWidget(pushButton);


        horizontalLayout->addLayout(verticalLayout_6);


        retranslateUi(MyForm);
        QObject::connect(widget, SIGNAL(perspectiva()), radioButton_4, SLOT(click()));
        QObject::connect(widget, SIGNAL(ortogonal()), radioButton_2, SLOT(click()));
        QObject::connect(radioButton_4, SIGNAL(clicked()), widget, SLOT(cambiar_perspectiva()));
        QObject::connect(radioButton_2, SIGNAL(clicked()), widget, SLOT(cambiar_orto()));
        QObject::connect(widget, SIGNAL(reiniciar()), radioButton_5, SLOT(click()));
        QObject::connect(widget, SIGNAL(reiniciar()), radioButton_4, SLOT(click()));

        QMetaObject::connectSlotsByName(MyForm);
    } // setupUi

    void retranslateUi(QWidget *MyForm)
    {
        MyForm->setWindowTitle(QCoreApplication::translate("MyForm", "IDI-Lab", nullptr));
        label_2->setText(QCoreApplication::translate("MyForm", "Escollir Camara", nullptr));
        radioButton_4->setText(QCoreApplication::translate("MyForm", "Perspectiva", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MyForm", "Ortogonal", nullptr));
        label->setText(QCoreApplication::translate("MyForm", "Escollir cub", nullptr));
        radioButton_5->setText(QCoreApplication::translate("MyForm", "Cub 1", nullptr));
        radioButton_3->setText(QCoreApplication::translate("MyForm", "Cub 2", nullptr));
        radioButton->setText(QCoreApplication::translate("MyForm", "Cub 3", nullptr));
        pushButton->setText(QCoreApplication::translate("MyForm", "Sortir", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyForm: public Ui_MyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYFORM_H
