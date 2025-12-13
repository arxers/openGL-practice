#version 330 core
// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Color
layout (location = 1) in vec3 aColor;
// Texture
layout (location = 2) in vec2 aTex;

// Outputs color for the fragment shader
out vec3 color;

// Output texture for fragment shader
out vec2 texCoord;

// Controls scale of vertices
uniform float scale;

// Inputs matrices needed for 3d viewing with perspective
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    // Outputs the positions/coordinates of all vertices
    gl_Position = proj * view * model * vec4(aPos, 1.0);
    // Assigns the colors from the Vertex data to "color"
    color = aColor;
    // Assigns the texture coordinates from the Vertex Data to "texCoord"
    texCoord = aTex;
}