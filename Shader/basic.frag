#version 460 core
in vec3 FragColor;
in vec3 FragNormal;
out vec4 FragOutput;

uniform vec3 uLightDir = normalize(vec3(0.5, 0.7, 1.0));

void main()
{
    float lighting = max(dot(normalize(FragNormal), normalize(uLightDir)), 0.1);
    vec3 color = FragColor * lighting;
    FragOutput = vec4(color, 1.0);
}
