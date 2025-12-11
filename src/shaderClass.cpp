#include "../inc/shaderClass.hpp"

// std::string get_file_contents(const char *filename)
// {
//     std::ifstream in(filename, std::ios::binary);
//     if (in) {
//         std::string contents;
//         in.seekg(0, std::ios::end);
//         contents.resize(in.tellg());
//         in.seekg(0, std::ios::beg);
//         in.read(&contents[0], contents.size());
//         in.close();
//         return contents;
//     }
//     throw(errno);
// }

std::string get_file_contents(const char *filename)
{
    std::ifstream in(filename);
    if (!in) throw std::runtime_error(std::string("Failed to open file: ") + filename);
    
    std::ostringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

Shader::Shader(const char* vertexFile, const char *fragmentFile) {
    std::string vertexStr = get_file_contents(vertexFile);
    std::string fragmentStr = get_file_contents(fragmentFile);

    const char* vertexSource = vertexStr.c_str();
    const char* fragmentSource = fragmentStr.c_str();
}