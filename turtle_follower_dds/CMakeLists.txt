cmake_minimum_required(VERSION 3.16)

project(turtle_follower_dds VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(turtle_follower_dds
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        resources.qrc

        PosMsg.idl
        PosMsg.c PosMsg.h



        TeleopMsg.idl
        TeleopMsg.c TeleopMsg.h
        turtleteleopkeywidget.h turtleteleopkeywidget.cpp
        turtlewidget.h turtlewidget.cpp
        turtlefollowerwidget.h turtlefollowerwidget.cpp
        TurtleCalculator.cpp TurtleCalculator.h

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET turtle_follower_dds APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(turtle_follower_dds SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(turtle_follower_dds
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(turtle_follower_dds PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.turtle_follower_dds)
endif()
set_target_properties(turtle_follower_dds PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS turtle_follower_dds
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(turtle_follower_dds)
endif()

set(CycloneDDS_DIR "C:/Users/Alcomarxism/Documents/Libs/cyclonedds/lib/cmake/CycloneDDS")
find_package(CycloneDDS REQUIRED)

target_link_libraries(turtle_follower_dds PRIVATE
    CycloneDDS::ddsc
)
