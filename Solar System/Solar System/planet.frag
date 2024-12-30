#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D texture1;
vec2 uv;

void sphereUV() {
    const float PI = 3.14159265359;

    vec3 direction = normalize(Normal);
    float longitude = 1 - (atan(direction.z, direction.x) / (2.0 * PI)) * 2;
    float latitude = 0.5 + (asin(direction.y) / PI);

    uv = vec2(longitude, latitude);
}

uniform vec3 lightColor;
uniform vec3 lightPos;

void main() {
    sphereUV();
    
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * texture(texture1, vec2(uv.x, -uv.y)).rgb;

    FragColor = vec4(result, 1.0);
}