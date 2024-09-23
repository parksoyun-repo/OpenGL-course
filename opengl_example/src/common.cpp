#include "common.h"
#include <fstream>
#include <sstream>

std::optional<std::string> LoadTextFile(const std::string& filename) 
{
    std::ifstream fin(filename);
    if (!fin.is_open()) 
    {
        SPDLOG_ERROR("failed to open file: {}", filename);
        return {}; // 중괄호 {}는 '아무것도 없는 값'
    }
    std::stringstream text;
    text << fin.rdbuf();
    return text.str(); // 자동으로 optional로 감싸진다
}