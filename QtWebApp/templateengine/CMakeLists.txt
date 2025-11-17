cmake_minimum_required(VERSION 3.16)

project(QtWebAppTemplateEngine LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(${PROJECT_NAME} STATIC)
add_library(QtWebApp::TemplateEngine ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(${PROJECT_NAME} PRIVATE
  TemplateLoader.hpp
  Template.cpp
  Template.hpp
  TemplateCache.cpp
  TemplateCache.hpp
  TemplateGlobal.hpp
  TemplateLoader.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(${PROJECT_NAME} PUBLIC QTWEBAPPTEMPLATEENGINELIB_LIBRARY)
