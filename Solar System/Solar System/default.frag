#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D texture1;
vec2 uv;

uniform vec3 viewPos;
vec3 lightColor = vec3(1.0);

void sphereUV() {
    const float PI = 3.14159265359;

    vec3 direction = normalize(Normal);
    float longitude = 1 - (atan(direction.z, direction.x) / (2.0 * PI)) * 2;
    float latitude = 0.5 + (asin(direction.y) / PI);

    uv = vec2(longitude, latitude);
}

void main() {
    sphereUV();

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(vec3(0.0, 0.0, 0.0) - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  

    vec4 result = (vec4(ambient, 1.0) + vec4(diffuse, 1.0) + vec4(specular, 1.0)) * texture(texture1, vec2(uv.x, -uv.y));
    
    FragColor = result;
}