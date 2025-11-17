cmake_minimum_required(VERSION 3.16)

project(QtWebAppHttpServer LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Network)

add_library(${PROJECT_NAME} STATIC)
add_library(QtWebApp::HttpServer ALIAS ${PROJECT_NAME})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE SUPERVERBOSE)
endif()

target_sources(${PROJECT_NAME} PRIVATE
  HttpRequest.hpp
  HttpRequestHandler.cpp
  HttpRequestHandler.hpp
  HttpResponse.cpp
  HttpResponse.hpp
  HttpSession.cpp
  HttpSession.hpp
  HttpSessionStore.cpp
  HttpSessionStore.hpp
  StaticFileController.cpp
  StaticFileController.hpp
  HttpConnectionHandler.cpp
  HttpConnectionHandler.hpp
  HttpConnectionHandlerPool.cpp
  HttpConnectionHandlerPool.hpp
  HttpCookie.cpp
  HttpCookie.hpp
  HttpGlobal.cpp
  HttpGlobal.hpp
  HttpListener.cpp
  HttpListener.hpp
  HttpRequest.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Network
)

target_compile_definitions(${PROJECT_NAME} PUBLIC QTWEBAPPHTTPSERVERLIB_LIBRARY)
