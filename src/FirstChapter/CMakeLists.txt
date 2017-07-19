cmake_minimum_required( VERSION 2.8 )
PROJECT(FirstChapter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)

include_directories(
    "headers"
    "../../external/assimp/include"
    "../../external/glfw/include"
    "../../external/glm"
    "../../deps"
    "../../deps/glad_static_generated/include"
)

link_directories(
    "../../external/assimp/lib/"
    "../../external/glfw/src/"
)

if(MSVC)
    set(ASSIMP_LIB "assimp-vc140-mt")
else()
    set(ASSIMP_LIB "assimp")
endif()

link_libraries(
    ${ASSIMP_LIB}
    "glfw3"
    "IrrXML"
    "zlibstatic"
)

set(GLAD_SRC "../../deps/glad_static_generated/src/glad.c")

file(GLOB MainSources "src/FirstChapter/sources/*.cpp" )
file(GLOB MainSources "sources/*.cpp" )
file(GLOB MainHeaders "headers/*.*")

message(STATUS "Source files of FirstChapter: " ${MainHeaders} ${MainSources} ${GLAD_SRC})

# Check for C++17 support
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
if (_cpp_latest_flag_supported)
    add_compile_options("/std:c++latest")
else()
    Message(Error "no c++17 support detected. On windows please use the developer command prompt of the vs 2017 preview!")
endif()


add_executable(${PROJECT_NAME}  ${MainHeaders} ${MainSources} ${GLAD_SRC})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})