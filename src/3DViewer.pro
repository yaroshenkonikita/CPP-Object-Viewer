QT       += core gui opengl openglwidgets widgets
include(QtGifImage/gifimage/qtgifimage.pri)

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    QClass/controller.cc \
    QClass/OpenGLWidget/gl_override.cc \
    Facade/Affine/affine_object.cc \
    Facade/Container/container_object.cc \
    Facade/FileReader/parsing_object.cc \
    Facade/NormalizationParameters/normalization.cc \
    Facade/Singleton/singleton.cc \
    main.cc \
    SettingsClass/options.cc \
    SettingsClass/options_t.cc

HEADERS += \
    QClass/controller.h \
    QClass/OpenGLWidget/gl_override.h \
    Facade/Mediator/object_model.h \
    Facade/part_object.h \
    SettingsClass/options.h \
    SettingsClass/options_t.h

FORMS += \
    SettingsClass/options.ui \
    QClass/view.ui

macx:ICON = $${PWD}/icon/3DviewerLogo.icns

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
