#version 300 es

layout(location = 0) in vec2 position;
uniform float scale;
void main()
{
   gl_Position = vec4(position.x *scale, position.y * scale, 1.0f, 1.0f);
}