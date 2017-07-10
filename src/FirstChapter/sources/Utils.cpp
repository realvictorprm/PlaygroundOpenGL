#include "../headers/Utils.hpp"

std::optional<std::string> readCompleteFile(std::string filename)
{
    auto file = std::ifstream(filename);
    if (file.is_open()) {
        auto res = std::string();
        file.seekg(0, std::ios::end);
        res.reserve(file.tellg());
        file.seekg(0, std::ios::beg);
        res.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
        file.close();
        return std::make_optional(res);
    }
    else {
        file.close();
        return std::optional<std::string>{};
    }
}
