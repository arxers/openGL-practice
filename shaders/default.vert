#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

// Outputs color for the fragment shader
out vec3 color;

uniform float scale;

void main()
{
    gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z, 1.0);
    // Assigns the colors from the Vertex data to "color"
    color = aColor;
}