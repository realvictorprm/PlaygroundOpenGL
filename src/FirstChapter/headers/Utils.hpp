#ifndef UTILS_HPP
#define UTILS_HPP

#include <optional>
#include <string>
#include <fstream>

template<typename T>
auto unwrapOptional(std::optional<T>& opt, const char* failMsg) {
    if (opt.has_value()) return opt.value();
    throw new std::exception(failMsg);
}

std::optional<std::string> readCompleteFile(std::string filename);

#endif