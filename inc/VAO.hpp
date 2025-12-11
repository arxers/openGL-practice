#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>
#include "VBO.hpp"

/* Vertex Array Object (VAO)
 * Stores the vertex attribute configuration (attribute locations, formats,
 * strides, offsets, and which attributes are enabled) and the association
 * with a GL_ELEMENT_ARRAY_BUFFER (EBO). The VAO records how vertex data
 * (from VBOs) is interpreted during draw calls. It is NOT the buffer that
 * stores vertex data itself — that is the VBO's job.
 */ 
class VAO
{
public:
    // Reference ID of the Vertex Array Object
    GLuint ID;
    // Generates a VAO ID
    VAO();

    // Links a VBO to the VAO using a certain layout
    void LinkVBO(VBO VBO, GLuint layout);
    // Binds the VAO
    void Bind();
    // Unbinds the VAO
    void Unbind();
    // Deletes the VAO
    void Delete();
};

#endif