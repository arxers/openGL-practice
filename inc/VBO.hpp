#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>

/* Vertex Buffer Object (VBO)
 * A GPU buffer bound to GL_ARRAY_BUFFER that holds raw per-vertex data
 * (positions, normals, texture coordinates, colors, etc.). The VBO contains
 * the bytes uploaded with glBufferData; attribute layout (how to read those
 * bytes) is configured on the VAO via glVertexAttribPointer.
 */
class VBO
{
public:
    // Reference ID of the Vertex Buffer Object
    GLuint ID;
    // Generates a Vertex Buffer Object, and links it to vertices
    VBO(GLfloat *vertices, GLsizeiptr size);

    // Binds the VBO
    void Bind();
    // Unbinds the VBO
    void Unbind();
    // Deletes the VBO
    void Delete();
};

#endif