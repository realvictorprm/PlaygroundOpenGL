cmake_minimum_required( VERSION 3.2 )

include(ExternalProject)

ExternalProject_Add(
    assimp
    SOURCE_DIR "external/assimp" 
    BINARY_DIR "external/assimp"
    )
ExternalProject_Add(
    glfw
    SOURCE_DIR "external/glfw"
    BINARY_DIR "external/glfw"
)

add_subdirectory(src/FirstChapter/)
#include(src/FirstChapter/CMakeLists.txt)    