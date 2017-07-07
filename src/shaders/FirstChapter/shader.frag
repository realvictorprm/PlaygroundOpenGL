#version 330 core

in vec3 inColor;
in vec2 TextureCoords;
out vec4 FragColor;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TextureCoords) * vec4(inColor, 1.f);
    //FragColor = vec4(inColor, 1.f);//vec4(inColor, 1.f);
}