cmake_minimum_required (VERSION 2.8.11)
project (HelloPaper)
set(CMAKE_CXX_FLAGS "-std=c++11 -fno-exceptions")

link_directories(/usr/local/lib)
find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

include_directories (${GLFW_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR} /usr/local/include)
set (PAPERDEPS Stick Brick Scrub ${OPENGL_LIBRARIES})

add_executable (HelloPaper HelloPaper.cpp)
target_link_libraries(HelloPaper ${GLFW_STATIC_LIBRARIES} ${PAPERDEPS} Paper)
