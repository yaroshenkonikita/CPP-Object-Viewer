cmake_minimum_required(VERSION 3.22)

project(3DViewer VERSION 2.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core Gui Widgets OpenGL OpenGLWidgets REQUIRED)

add_subdirectory(GIFCreation)

add_executable(3DViewer
        main.cc

        QClass/controller.cc
        QClass/OpenGLWidget/gl_override.cc

        QClass/controller.h
        QClass/OpenGLWidget/gl_override.h

        Facade/Affine/affine_object.cc
        Facade/Container/container_object.cc
        Facade/FileReader/parsing_object.cc
        Facade/NormalizationParameters/normalization.cc
        Facade/Singleton/singleton.cc

        Facade/Mediator/object_model.h
        Facade/part_object.h

        SettingsClass/options.cc
        SettingsClass/options_t.cc

        SettingsClass/options.h
        SettingsClass/options_t.h

        SettingsClass/options.ui
        QClass/view.ui

        icon/icons.qrc)

target_link_libraries(3DViewer PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::OpenGL Qt6::OpenGLWidgets GIFLIB)
