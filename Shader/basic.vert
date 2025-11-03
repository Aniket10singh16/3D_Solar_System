#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
uniform mat3 uNormalMatrix;

out vec3 FragColor;
out vec3 FragNormal;

void main()
{
    FragColor = aColor;
    FragNormal = normalize(uNormalMatrix * aNormal);
    gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
}
