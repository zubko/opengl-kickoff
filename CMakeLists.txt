cmake_minimum_required(VERSION 2.6)

set (PROJECT GoOpenGL)

project(${PROJECT})

file (GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    src/*.cpp
    src/*.h
)

file (GLOB RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
     res/*.*
)

SET_SOURCE_FILES_PROPERTIES(
  ${RESOURCES}
  PROPERTIES
  MACOSX_PACKAGE_LOCATION Resources
)

source_group(Source FILES ${SOURCES})
source_group(Resources FILES ${RESOURCES})

add_executable(
    ${PROJECT}
    WIN32
    MACOSX_BUNDLE
    ${SOURCES}
    ${RESOURCES}
)

# FROM GUIDE:
# On Windows I am lazy and only look for the
# release version of SDL, feel free to make this also look for debug
# modes depending on the cmake build target.
set(SDL_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/libs/sdl/build
    CACHE STRING "Path to SDL" FORCE)
find_library(SDL_LIBRARY
    NAMES SDL2-2.0.0 SDL2
    PATHS ${SDL_FOLDER}/lib
    PATH_SUFFIXES local/lib VisualC/SDL/Release
    NO_DEFAULT_PATH
)
find_library(SDLMAIN_LIBRARY
    NAMES SDL2main
    PATHS ${SDL_FOLDER}/lib
    PATH_SUFFIXES local/lib VisualC/SDLmain/Release
    NO_DEFAULT_PATH
)

find_package(OpenGL REQUIRED)

# FROM GUIDE:
# on OS X we also have to add '-framework Cocoa' as library.  This is
# actually a bit of an hack but it's easy enough and reliable.
set(EXTRA_LIBS "")
if (APPLE)
    set(EXTRA_LIBS ${EXTRA_LIBS} "-framework Cocoa")
endif()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${SDL_FOLDER}/include/SDL2
)

target_link_libraries(
    ${PROJECT}
    ${OPENGL_LIBRARIES}
    ${SDL_LIBRARY}
    ${SDLMAIN_LIBRARY}
    ${EXTRA_LIBS}
)

if(WIN32)
    set(VS_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR})
    add_custom_command(TARGET ${PROJECT} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SDL_FOLDER}/VisualC/SDL/Release/SDL.dll ${VS_OUTPUT_DIR}/SDL.dll)
endif()

If(APPLE)
    set(BUNDLE_BINARY
        ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${PROJECT}.app/Contents/MacOS/${PROJECT})
    add_custom_command(TARGET ${PROJECT} POST_BUILD
        COMMAND python scripts/frameworkify.py ${BUNDLE_BINARY}
        ${SDL_LIBRARY})
endif()
