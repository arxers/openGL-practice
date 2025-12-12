#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <cmath>

#include "../inc/Shader.hpp"
#include "../inc/VAO.hpp"
#include "../inc/VBO.hpp"
#include "../inc/EBO.hpp"
#include "../inc/Texture.hpp"

using std::sqrt;

// GLfloat vertices[] =
// {   //          COORDINATES                     /       COLORS
//     -0.5f,  -0.5f * float(sqrt(3)) / 3,     0.0f,   0.8f, 0.3f,  0.02f,     // Lower left corner
//      0.5f,  -0.5f * float(sqrt(3)) / 3,     0.0f,   0.8f, 0.3f,  0.02f,     // Lower right corner
//      0.0f,   0.5f * float(sqrt(3)) * 2 / 3, 0.0f,   1.0f, 0.6f,  0.32f,     // Upper corner
//     -0.25f,  0.5f * float(sqrt(3)) / 6,     0.0f,   0.9f, 0.45f, 0.17f,     // Inner left
//      0.25f,  0.5f * float(sqrt(3)) / 6,     0.0f,   0.9f, 0.45f, 0.17f,     // Inner right
//      0.0f,  -0.5f * float(sqrt(3)) / 3,     0.0f,   0.8f, 0.3f,  0.02f      // Inner down
//     };   

// GLuint indices[] = {
//     0, 3, 5, // Lower left triangle
//     3, 2, 4, // Lower right triangle
//     5, 4, 1  // Upper triangle
// };

GLfloat vertices[] =
{   //          COORDINATES                     /       COLORS
    -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    -0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
     0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
     0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,   1.0f, 0.0f
};

GLuint indices[] = {
    0, 2, 1, // Lower left triangle
    0, 3, 2, // Lower right triangle
};


int main()
{

    // Init GLFW
    glfwInit();

    // Tell GLFW what version of OpenGL we are using (3.3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Using CORE profile, so only modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create GLFWwindow object with 800 by 800 pixels, naming it "OpenGL"
    GLFWwindow *window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);

    if (window == NULL)
    {
        glfwTerminate();
        return -1;
    }

    // Introduce window into the current context
    glfwMakeContextCurrent(window);

    // Load GLAD so it configures OpenGL
    gladLoadGL();

    // Specify the viewport of OpenGL in the window
    // params: x_begin, y_begin, x_end, y_end
    glViewport(0, 0, 800, 800);

    Shader shaderProgram("resources/shaders/default.vert", "resources/shaders/default.frag");

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    // Gets ID of uniform called "scale"
    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

    // Texture
    Texture popcat("resources/textures/popcat.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    popcat.texUnit(shaderProgram, "tex0", 0);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Specify the color of the background
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT);
        // Tell OpenGL which Shader Program we want to use
        shaderProgram.Activate();
        // Assigns a value to the uniform; NOTE: Must be done after shaderProgram.activate()
        glUniform1f(uniID, 0.0f);
        // Binds texture so that it appears in rendering
        popcat.Bind();
        // Bind the VAO so OpenGL knows to use it
        VAO1.Bind();
        // Draw the triangle using the GL_TRIANGLES primitive
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // Swap the back buffer with front buffer
        glfwSwapBuffers(window);

        // Handles GLFW events
        glfwPollEvents();
    }

    // Delete all objects we've created
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();
    popcat.Delete();

    // Delete window before ending the program
    glfwDestroyWindow(window);
    glfwTerminate();
}
