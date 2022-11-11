/********************************************************************************
** Form generated from reading UI file 'Atzar.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ATZAR_H
#define UI_ATZAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "MyQButton.h"
#include "MyQGLCD.h"

QT_BEGIN_NAMESPACE

class Ui_Atzar
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    MyQButton *pushButton_2;
    MyQButton *pushButton_3;
    MyQButton *pushButton;
    MyQGLCD *lcdNumber;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_6;
    QSpacerItem *horizontalSpacer;
    MyQButton *pushButton_4;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_5;

    void setupUi(QWidget *Atzar)
    {
        if (Atzar->objectName().isEmpty())
            Atzar->setObjectName(QString::fromUtf8("Atzar"));
        Atzar->resize(867, 516);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Atzar->sizePolicy().hasHeightForWidth());
        Atzar->setSizePolicy(sizePolicy);
        Atzar->setMinimumSize(QSize(0, 200));
        verticalLayout_3 = new QVBoxLayout(Atzar);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton_2 = new MyQButton(Atzar);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy1);
        pushButton_2->setMinimumSize(QSize(0, 0));
        pushButton_2->setMaximumSize(QSize(16777215, 16777215));
        pushButton_2->setAutoFillBackground(false);
        pushButton_2->setStyleSheet(QString::fromUtf8(""));
        pushButton_2->setAutoDefault(false);
        pushButton_2->setFlat(false);

        horizontalLayout_2->addWidget(pushButton_2);

        pushButton_3 = new MyQButton(Atzar);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        sizePolicy1.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy1);
        pushButton_3->setMinimumSize(QSize(0, 0));
        pushButton_3->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_2->addWidget(pushButton_3);

        pushButton = new MyQButton(Atzar);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);
        pushButton->setMinimumSize(QSize(0, 0));
        pushButton->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_2->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_3->addLayout(verticalLayout);

        lcdNumber = new MyQGLCD(Atzar);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lcdNumber->sizePolicy().hasHeightForWidth());
        lcdNumber->setSizePolicy(sizePolicy2);
        lcdNumber->setMinimumSize(QSize(0, 0));

        verticalLayout_3->addWidget(lcdNumber);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        verticalLayout_3->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_6 = new QPushButton(Atzar);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));

        horizontalLayout->addWidget(pushButton_6);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_4 = new MyQButton(Atzar);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        horizontalLayout->addWidget(pushButton_4);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButton_5 = new QPushButton(Atzar);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        horizontalLayout->addWidget(pushButton_5);


        verticalLayout_3->addLayout(horizontalLayout);


        retranslateUi(Atzar);
        QObject::connect(pushButton_5, SIGNAL(clicked()), Atzar, SLOT(close()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), pushButton_2, SLOT(paint()));
        QObject::connect(pushButton_3, SIGNAL(clicked()), pushButton_3, SLOT(paint()));
        QObject::connect(pushButton, SIGNAL(clicked()), pushButton, SLOT(paint()));
        QObject::connect(pushButton_6, SIGNAL(clicked()), pushButton_2, SLOT(resetColor()));
        QObject::connect(pushButton_6, SIGNAL(clicked()), pushButton_3, SLOT(resetColor()));
        QObject::connect(pushButton_6, SIGNAL(clicked()), pushButton, SLOT(resetColor()));
        QObject::connect(pushButton_3, SIGNAL(SendColor(QString)), lcdNumber, SLOT(button2(QString)));
        QObject::connect(pushButton_6, SIGNAL(clicked()), lcdNumber, SLOT(RRReset()));
        QObject::connect(pushButton_2, SIGNAL(SendColor(QString)), lcdNumber, SLOT(button1(QString)));
        QObject::connect(pushButton, SIGNAL(SendColor(QString)), lcdNumber, SLOT(button3(QString)));
        QObject::connect(pushButton_4, SIGNAL(clicked()), pushButton_4, SLOT(start()));
        QObject::connect(pushButton_4, SIGNAL(Trio()), lcdNumber, SLOT(MUDAMUDA()));
        QObject::connect(pushButton_4, SIGNAL(c1(QString)), pushButton_2, SLOT(justpaint(QString)));
        QObject::connect(pushButton_4, SIGNAL(c2(QString)), pushButton_3, SLOT(justpaint(QString)));
        QObject::connect(pushButton_4, SIGNAL(c3(QString)), pushButton, SLOT(justpaint(QString)));
        QObject::connect(pushButton_4, SIGNAL(xd(QString*)), lcdNumber, SLOT(start(QString*)));

        pushButton_2->setDefault(false);


        QMetaObject::connectSlotsByName(Atzar);
    } // setupUi

    void retranslateUi(QWidget *Atzar)
    {
        Atzar->setWindowTitle(QCoreApplication::translate("Atzar", "Atzar", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Atzar", "1", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Atzar", "2", nullptr));
        pushButton->setText(QCoreApplication::translate("Atzar", "3", nullptr));
        pushButton_6->setText(QCoreApplication::translate("Atzar", "&RESET", nullptr));
        pushButton_4->setText(QCoreApplication::translate("Atzar", "&START", nullptr));
        pushButton_5->setText(QCoreApplication::translate("Atzar", "&EXIT", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Atzar: public Ui_Atzar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ATZAR_H
