cmake_minimum_required(VERSION 3.5)

project(APDFCreator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR}PrintSupport REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        resources.qrc
        gui/welcomepage/welcomepage.h
        gui/welcomepage/welcomepage.cpp
        gui/welcomepage/welcomepage.ui
        gui/mainwindow.cpp
        gui/mainwindow.h
        gui/mainwindow.ui
        gui/paper.cpp
        gui/paper.h
        tools/draggabletool.h
        tools/draggabletool.cpp
        tools/texttool.h
        tools/texttool.cpp
        components/pagegrid.h components/pagegrid.cpp
        tools/imagetool.h
        tools/imagetool.cpp
        gui/pagesetup.h
        gui/pagesetup.cpp
        gui/pagesetup.ui
        gui/formulaeditor.h
        gui/formulaeditor.cpp
        gui/formulaeditor.ui
        tools/formulatool.h
        tools/formulatool.cpp
        in_out/in_out.h
        in_out/in_out.cpp
        tools/tooloptions.h
        tools/tooloptions.cpp
        gui/document.h gui/document.cpp
        components/documentpagecontroller.h components/documentpagecontroller.cpp
        components/documenttoolbar.h components/documenttoolbar.cpp
        components/settingsscopecombo.h components/settingsscopecombo.cpp
        components/pageproperties.h components/pageproperties.cpp
        components/ruler/slider.h components/ruler/slider.cpp
        components/ruler/ruler.h components/ruler/ruler.cpp
        components/papersizecombo.h components/papersizecombo.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    if(WIN32)
        qt_add_executable(APDFCreator
            WIN32
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
        )
    else()
        qt_add_executable(APDFCreator
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
        )
    endif()
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET APDFCreator APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(APDFCreator SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(APDFCreator
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(APDFCreator PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(APDFCreator PRIVATE Qt${QT_VERSION_MAJOR}::PrintSupport)

set_target_properties(APDFCreator PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(APDFCreator)
endif()
