#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D texture1;

void main() {
    const float PI = 3.14159265359;

    vec3 direction = normalize(Normal);
    float longitude = 1 - (atan(direction.z, direction.x) / (2.0 * PI)) * 2;
    float latitude = 0.5 + (asin(direction.y) / PI);

    vec2 uv = vec2(longitude, latitude);
    
    FragColor = texture(texture1, vec2(uv.x, -uv.y));
}