#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

// Reads a text file, and outputs it into a string
std::string get_file_contents(const char *filename);

class Shader
{
public:
    // Reference ID of the Shader Program
    GLuint ID;
    // Builds the Shader Program from 2 different shaders
    Shader(const char *vertexFile, const char *fragmentFile);

    // Activates the Shader Program
    void Activate();
    // Deletes the Shader Program
    void Delete();
};

#endif