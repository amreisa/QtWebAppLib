cmake_minimum_required(VERSION 3.16)

project(QtService LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

if(WIN32)
  find_library(USER32_LIB user32)

#   # Unicode definitions for Windows API
#   target_compile_definitions(${PROJECT_NAME} PRIVATE
#     UNICODE
#     _UNICODE
#   )

# # MinGW specific options
# if(MINGW)
#   target_compile_options(${PROJECT_NAME} PRIVATE -municode)
# endif()

else()
  find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Network)
  find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Network)
endif()

add_library(${PROJECT_NAME} STATIC)
add_library(QtWebApp::QtService ALIAS ${PROJECT_NAME})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_definitions(${PROJECT_NAME} PRIVATE SUPERVERBOSE)
endif()

target_sources(${PROJECT_NAME} PRIVATE
  qtservice.h
  qtservice_p.h
  qtservice.cpp
  $<$<BOOL:${WIN32}>:qtservice_win.cpp>
  $<$<BOOL:${UNIX}>:qtservice_unix.cpp>
  $<$<BOOL:${UNIX}>:qtunixsocket.cpp>
  $<$<BOOL:${UNIX}>:qtunixserversocket.cpp>
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
)

if(WIN32)

    # Unicode definitions for Windows API
    target_compile_definitions(${PROJECT_NAME} PRIVATE
      UNICODE
      _UNICODE
    )

  # MinGW specific options
  if(MINGW)
    target_compile_options(${PROJECT_NAME} PRIVATE -municode)
  endif()

  target_link_libraries(${PROJECT_NAME} PUBLIC ${USER32_LIB})
else()
  target_link_libraries(${PROJECT_NAME} PUBLIC Qt${QT_VERSION_MAJOR}::Network)
endif()

target_compile_definitions(${PROJECT_NAME} PUBLIC QTSERVICELIB_LIBRARY)
