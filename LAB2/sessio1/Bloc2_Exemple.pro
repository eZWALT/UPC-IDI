TEMPLATE    = app
QT         += opengl 

INCLUDEPATH +=  /usr/include/glm
INCLUDEPATH += /home/walterjtv/Escritorio/Assignatures/IDI/models3d

FORMS += MyForm.ui

HEADERS += MyForm.h BL2GLWidget.h MyGLWidget.h

SOURCES += main.cpp MyForm.cpp \
        BL2GLWidget.cpp MyGLWidget.cpp

SOURCES += /home/walterjtv/Escritorio/Assignatures/IDI/models3d/model.cpp
