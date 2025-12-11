#include "../inc/Shader.hpp"

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

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Attach Vertex Shader source to the Vertex Shader Object
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    // Compile the Vertex Shader into machine code
    glCompileShader(vertexShader);

    // Create Fragment Shader Object and get its reference
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Attach Fragment Shader source to the Fragment Shader Object
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    // Compile the Fragment Shader into machine code
    glCompileShader(fragmentShader);

    // Create Shader Program Object and get its reference
    ID = glCreateProgram();
    // Attach the Vertex and Fragment Shaders to the Shader Program
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    // Link all the shaders together into the Shader Program
    glLinkProgram(ID);

    // Delete the now useless Vertex and Fragment Shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activate() {
    glUseProgram(ID);
}

void Shader::Delete() {
    glDeleteProgram(ID);
}