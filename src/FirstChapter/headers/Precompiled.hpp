#ifndef PRECOMPILED_HPP
#define PRECOMPILED_HPP
// std lib includes
#define _HAS_CXX17 1
#include <iostream>
#include <memory>
#include <vector>
#include <thread>
#include <functional>
#include <fstream>
#include <string>
#if __has_include(<optional>)
#include <optional>
#else 
#include <experimental\optional>
#endif
#if __has_include(<filesystem>)
#include<filesystem>
#endif
#if __has_include(<experimental\filesystem>)
#include<experimental\filesystem>
#endif

#include <tuple>
#include <numeric>

// library includes
#include <glad\glad.h>
#define GLFW_INCLUDE_NONE
#include <glfw3.h>
#include <glm.hpp>
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>

#endif