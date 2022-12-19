#version 330 core

layout (location = 0) out vec4 o_Color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;
uniform vec4 u_Color = vec4(1.0f, 1.0f, 1.0f, 1.0f);

void main()
{
    o_Color = texture2D(u_Texture, v_TexCoord) * u_Color;
    //o_Color = vec4(v_TexCoord, 0.0f, 1.0f);
}
