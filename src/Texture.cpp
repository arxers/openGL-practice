#include "../inc/Texture.hpp"

Texture::Texture(const char *image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {
    // Assigns the type of texture to this texture object
    type = texType;

    // Width, Height, and number of color channels of the image
    int widthImg, heightImg, numColCh;
    // Flips image so that it is right side up
    stbi_set_flip_vertically_on_load(1);
    // Reads image from file, and store in bytes
    unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

    // Generate an OpenGL texture object
    glGenTextures(1, &ID);
    // Assigns the texture to a Texture Unit
    glActiveTexture(slot);
    glBindTexture(texType, ID);

    // Configures type of algo that is used to minimize and magnify the texture
    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Configures the way the texture repeats (if it does at all)
    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Optional if choosing to use GL_CLAMP_TO_BORDER
    // float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

    // Assigns the image to the OpenGL Texture object
    glTexImage2D(texType, 0, GL_RGB, widthImg, heightImg, 0, format, pixelType, bytes);
    // Generates Mipmaps (smaller versions of the image)
    glGenerateMipmap(texType);
    // Delete the image data as it is already in the OpenGL Texture object
    stbi_image_free(bytes);
    // Unbinds the OpenGL Texture object so that it can't be accidentally modified
    glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit) {
    GLuint texUni = glGetUniformLocation(shader.ID, uniform);
    // Shader needs to be activated before changing the value of a uniform
    shader.Activate();
    glUniform1i(texUni, unit);
}

void Texture::Bind() {
    glBindTexture(type, ID);
}

void Texture::Unbind() {
    glBindTexture(type, ID);
}

void Texture::Delete() {
    glDeleteTextures(1, &ID);
}