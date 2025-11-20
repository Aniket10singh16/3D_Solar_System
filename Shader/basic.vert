#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTexCoord;
layout (location = 4) in vec3 aTangent;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
uniform mat3 uNormalMatrix;

out vec3 FragColor;     // Vertex color
out vec3 FragNormal;    // World normal space
out vec3 FragPos;       // World space position
out vec2 TexCoord;      // Texture corrdinates
out vec3 Tangent;       // For normal mapping

void main()
{
    // calculate world space position
    vec4 worldPos = uModel * vec4(aPos, 1.0);
    FragPos = worldPos.xyz;

    // Transform normal to world space
    FragNormal = normalize(uNormalMatrix * aNormal);

    // Transform tangent to world space
    Tangent = normalize(uNormalMatrix * aTangent);

    // Pass through color and texture coordinates
    FragColor = aColor;
    TexCoord = aTexCoord;

    // Calculate final clip space position
    gl_Position = uProjection * uView * worldPos;
}