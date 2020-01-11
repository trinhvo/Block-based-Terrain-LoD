cmake_minimum_required (VERSION 3.0)
cmake_policy(VERSION 3.0)

project (Terrain_LOD)


if(MSVC)
  add_definitions(/DNOMINMAX)
else()
  list(APPEND CMAKE_CXX_FLAGS "-std=c++11")
endif()

#########################################################################
# On Ubuntu:
# sudo apt-get install libglfw3-dev libglfw3 libglm-dev libglew-dev
#########################################################################

#########################################################################
# On Mac OSX:
# brew install cmake glfw glm glew
#########################################################################

find_package(OpenGL REQUIRED)

if(WIN32)
  include_directories(include)
  link_directories(libs)

  set(LIBS mingw32 glfw glew32 opengl32 gdi32)

else(WIN32)
  # set(CMAKE_MODULE_PATH /usr/local/lib/cmake /usr/local/lib/x86_64-linux-gnu/cmake)
  # set(CMAKE_PREFIX_PATH /usr/local/lib/cmake/glfw)

  find_package(PkgConfig REQUIRED)
  find_package(GLFW3 REQUIRED)
  find_package(GLEW REQUIRED STATIC)
  # find_package(GLUT REQUIRED STATIC)
  find_package(Freetype REQUIRED)
  find_package(jpeg REQUIRED)
  find_package(png REQUIRED)

  # pkg_search_module(GLFW REQUIRED glfw3)
  include_directories(
    ${OPENGL_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    # ${GLUT_INCLUDE_DIR}
    ${FREETYPE_INCLUDE_DIRS}
    ${JPEG_INCLUDE_DIR}
    ${PNG_INCLUDE_DIRS}
  )

endif(WIN32)

if(APPLE)
  add_definitions(-DGL_SILENCE_DEPRECATION)

  include_directories(
    /usr/local/include
    include
  )

  link_directories(/usr/local/lib/ /opt/local/lib)

  find_library(COCOA_LIBRARY Cocoa REQUIRED)
  find_library(IOKIT_LIBRARY IOKit REQUIRED)
  find_library(COREVID_LIBRARY CoreVideo REQUIRED)

  MARK_AS_ADVANCED(COCOA_LIBRARY OPENGL_LIBRARIES)

  set(LIBS  glfw
            ${OPENGL_LIBRARIES}
            # ${GLUT_LIBRARIES}
            glew
            ${COCOA_LIBRARY}
            ${COREVID_LIBRARY}
            ${IOKIT_LIBRARY}
            ${FREETYPE_LIBRARIES}
            ${JPEG_LIBRARIES}
            ${PNG_LIBRARIES}
            )

elseif(UNIX AND NOT APPLE)
  add_definitions(${OPENGL_DEFINITIONS})

  set(LIBS  ${GLFW_LIBRARIES}
            ${OPENGL_LIBRARIES}
            # ${GLUT_LIBRARIES}
            ${GLEW_LIBRARIES}
            ${FREETYPE_LIBRARIES}
            ${JPEG_LIBRARIES}
            ${PNG_LIBRARIES}
            X11 Xxf86vm pthread Xrandr Xinerama Xi Xcursor)
else()
  set(LIBS )
endif(APPLE)


file(GLOB_RECURSE PROJ_SOURCES src/*.h src/*.hpp src/*.cpp src/*.c)

add_executable(${PROJECT_NAME} ${PROJ_SOURCES})

target_link_libraries(${PROJECT_NAME} ${LIBS})

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)