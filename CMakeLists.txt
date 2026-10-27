cmake_minimum_required(VERSION 3.16)

project(ReadHub VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Test)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        loginwindow.cpp
        loginwindow.h
        loginwindow.ui
        uploadwindow.cpp
        uploadwindow.h
        uploadwindow.ui
        readwindow.cpp
        readwindow.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ReadHub
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}


    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ReadHub APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(ReadHub SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ReadHub
            ${PROJECT_SOURCES}
        )
    endif()
endif()

include(FetchContent)

set(PDFIUM_TAG "" CACHE STRING "pdfium-binaries release tag (empty = latest)")

if(WIN32)
    set(PDFIUM_ARCHIVE "pdfium-win-x64.tgz")
elseif(APPLE)
    set(PDFIUM_ARCHIVE "pdfium-mac-arm64.tgz")
else()
    set(PDFIUM_ARCHIVE "pdfium-linux-x64.tgz")
endif()

if(PDFIUM_TAG STREQUAL "")
    set(PDFIUM_URL "https://github.com/bblanchon/pdfium-binaries/releases/latest/download/${PDFIUM_ARCHIVE}")
else()
    set(PDFIUM_URL "https://github.com/bblanchon/pdfium-binaries/releases/download/${PDFIUM_TAG}/${PDFIUM_ARCHIVE}")
endif()

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

FetchContent_Declare(pdfium URL ${PDFIUM_URL})
FetchContent_MakeAvailable(pdfium)

set(PDFium_DIR "${pdfium_SOURCE_DIR}")
find_package(PDFium REQUIRED)

target_link_libraries(ReadHub PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

target_link_libraries(ReadHub PRIVATE Qt${QT_VERSION_MAJOR}::Widgets pdfium)

if(WIN32)
    add_custom_command(TARGET ReadHub POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PDFium_DIR}/bin/pdfium.dll"
            $<TARGET_FILE_DIR:ReadHub>)
endif()


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.ReadHub)
endif()
set_target_properties(ReadHub PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ReadHub
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ReadHub)
endif()
# Enable testing
enable_testing()

add_executable(ReadHubTest
    tst_readhubtest.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    loginwindow.cpp
    loginwindow.h
    loginwindow.ui
    uploadwindow.cpp
    uploadwindow.h
    uploadwindow.ui
    readwindow.cpp
    readwindow.h
)

target_link_libraries(ReadHubTest PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Test
    pdfium
)

add_test(NAME ReadHubTest COMMAND ReadHubTest)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ReadHubTest)
endif()
