cmake_minimum_required( VERSION 3.2 )

include(ExternalProject)

# ExternalProject_Add(
#     assimp
#     SOURCE_DIR "external/assimp" 
#     BINARY_DIR "external/assimp"
#     )
# ExternalProject_Add(
#     glfw
#     SOURCE_DIR "external/glfw"
#     BINARY_DIR "external/glfw"
#     CMAKE_ARGS "-DBUILD_SHARED_LIBS:BOOL=OFF"
# )
add_subdirectory(external/glfw)
add_subdirectory(external/assimp)
add_subdirectory(src/FirstChapter/)
add_subdirectory(src/VoxelChapter/)
#include(src/FirstChapter/CMakeLists.txt)    