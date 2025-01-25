#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

void main()
{
    float checkerSize = 0.1;
    vec2 position = TexCoord / checkerSize;
    float pattern = mod(floor(position.x) + floor(position.y), 2.0);

    vec3 black = vec3(0.0, 0.0, 0.0);
    vec3 purple = vec3(0.5, 0.0, 0.5);

    if (pattern == 0.0)
        FragColor = vec4(black, 1.0);
    else
        FragColor = vec4(purple, 1.0);
}
