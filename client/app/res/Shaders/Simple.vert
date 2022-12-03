#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec2 a_TexCoord;

out vec2 v_TexCoord;

uniform mat4 u_Transform;

void main()
{
    v_TexCoord = a_TexCoord;
    
    //vec4 position = u_Transform * vec4(a_Position, 1.0f);
    vec4 position = vec4(a_Position, 1.0f);
    gl_Position = position;
}
