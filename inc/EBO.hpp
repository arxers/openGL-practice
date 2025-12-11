#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>

/* Element Buffer Object (EBO) / Index Buffer Object (IBO)
 * A GPU buffer bound to GL_ELEMENT_ARRAY_BUFFER that stores indices into
 * vertex arrays. Used by glDrawElements to reuse vertices and define
 * primitive topology via indices. Bind the EBO while a VAO is bound so
 * the VAO records the index-buffer binding.
 */
class EBO
{
public:
    // Reference ID of the Elements Buffer Object
    GLuint ID;
    // Generates an Elements Buffer Object, and links it to indices
    EBO(GLuint* indices, GLsizeiptr size);

    // Binds the EBO
    void Bind();
    // Uninds the EBO
    void Unbind();
    // Deletes the EBO
    void Delete();
};

#endif