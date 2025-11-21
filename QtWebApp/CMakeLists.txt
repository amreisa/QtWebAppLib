cmake_minimum_required(VERSION 3.16)

project(QtWebApp LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

# Individual component namespace options (optional)
option(QT_WEBAPP_USE_QT_SERVICE "Build QtService component" OFF)
option(QT_WEBAPP_USE_LOGGING "Build Logging component" OFF)
option(QT_WEBAPP_USE_HTTP_SERVER "Build HttpServer component" ON)
option(QT_WEBAPP_USE_TEMPLATE_ENGINE "Build TemplateEngine component" OFF)

# Conditionally add subdirectories
if(QT_WEBAPP_USE_QT_SERVICE)
    add_subdirectory(qtservice)
endif()

if(QT_WEBAPP_USE_LOGGING)
    add_subdirectory(logging)
endif()

if(QT_WEBAPP_USE_HTTP_SERVER)
    add_subdirectory(httpserver)
endif()

if(QT_WEBAPP_USE_TEMPLATE_ENGINE)
    add_subdirectory(templateengine)
endif()

add_library(${PROJECT_NAME} STATIC)

# Always use the namespace alias for the main library
add_library(QtWebApp::QtWebApp ALIAS ${PROJECT_NAME})

# Debug version naming
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(WIN32 OR (UNIX AND NOT APPLE))
        set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}d")
    elseif(APPLE)
        set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}_debug")
    endif()
endif()

# Link dependencies - use simple conditional linking
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
)

# Link components based on namespace option and build flags
if(QT_WEBAPP_USE_QT_SERVICE)
    target_link_libraries(${PROJECT_NAME} PRIVATE QtWebApp::QtService)
endif()
if(QT_WEBAPP_USE_LOGGING)
    target_link_libraries(${PROJECT_NAME} PRIVATE QtWebApp::Logging)
endif()
if(QT_WEBAPP_USE_HTTP_SERVER)
    target_link_libraries(${PROJECT_NAME} PRIVATE QtWebApp::HttpServer)
endif()
if(QT_WEBAPP_USE_TEMPLATE_ENGINE)
    target_link_libraries(${PROJECT_NAME} PRIVATE QtWebApp::TemplateEngine)
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE QTWEBAPPLIB_LIBRARY)

install(FILES readme.txt DESTINATION doc)
