cmake_minimum_required(VERSION 3.16)

project(QtWebAppLogging LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(${PROJECT_NAME} STATIC)
add_library(QtWebApp::Logging ALIAS ${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
  LogMessage.hpp
  DualFileLogger.cpp
  DualFileLogger.hpp
  FileLogger.cpp
  FileLogger.hpp
  Logger.cpp
  Logger.hpp
  LogGlobal.hpp
  logmessage.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core )

target_compile_definitions(${PROJECT_NAME} PUBLIC QTWEBAPPLOGGINGLIB_LIBRARY)
