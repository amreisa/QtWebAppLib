cmake_minimum_required(VERSION 3.16)

project(QtWebApp LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_subdirectory(logging)
add_subdirectory(qtservice)
add_subdirectory(httpserver)
add_subdirectory(templateengine)

add_library(${PROJECT_NAME} STATIC)
add_library(QtWebApp::QtWebApp ALIAS ${PROJECT_NAME})

# إصدار الت debug
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  if(WIN32 OR (UNIX AND NOT APPLE))
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}d")
  elseif(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}_debug")
  endif()
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core
  QtWebApp::Logging
  QtWebApp::HttpServer
  QtWebApp::QtService
  QtWebApp::TemplateEngine
)

target_compile_definitions(${PROJECT_NAME} PRIVATE QTWEBAPPLIB_LIBRARY)

install(FILES readme.txt DESTINATION doc)
