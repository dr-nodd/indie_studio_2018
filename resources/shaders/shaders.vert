#version 130

varying vec2 texCoord;
varying vec3 normalMap;

void main()
{
    gl_Position = normalize(gl_ModelViewProjectionMatrix * gl_Vertex);
    texCoord = gl_MultiTexCoord0.st;
    normalMap = normalize(gl_Normal * gl_NormalMatrix);
}