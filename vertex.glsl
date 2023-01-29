#version 300 es

layout(location = 0) in vec3 position;
out vec4 interpolatedColor;
void main()
{
   gl_Position = vec4(position.x, position.y, 0.0f, 1.0f);
   interpolatedColor = vec4(clamp(position, 0.0f, 1.0f), 1.0f);
}