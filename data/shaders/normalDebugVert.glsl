#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 3) in vec3 aNormal;
layout (location = 4) in vec3 aTangent;

out VS_OUT {
    vec3 normal;
    vec3 tangent;
    vec3 binormal;
} vs_out;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 normalMatrix;

void main()
{
    gl_Position = viewMatrix * modelMatrix * vec4(aPos, 1.0);

    vs_out.normal = normalize(vec3(viewMatrix * normalMatrix * vec4(aNormal, 0.0)));
    vs_out.tangent = normalize(vec3(viewMatrix * normalMatrix * vec4(aTangent, 0.0)));
    
    vs_out.tangent = normalize(vs_out.tangent - dot(vs_out.tangent, vs_out.normal) * vs_out.normal); //Gram–Schmidt process
    vs_out.binormal = cross(vs_out.normal, vs_out.tangent); //Get third basis vector as a cross of the two existing orthogonal ones
}