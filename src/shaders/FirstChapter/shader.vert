#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec3 aColor; // the color variable has attribute position 1
layout (location = 2) in vec2 aTexture;
  
out vec3 inColor; // output a color to the fragment shader
out vec2 TextureCoords;
void main()
{
    gl_Position = vec4(aPos, 1.0);
    inColor = aColor; // set ourColor to the input color we got from the vertex data
    TextureCoords = aTexture;
}       