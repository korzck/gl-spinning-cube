#version 300 es

layout(location = 0) in vec3 position;
out vec4 interpolatedColor;
uniform float scale;
uniform mat4 moving;
void main()
{
   gl_Position = moving * vec4(position.x * scale, position.y * scale, 1.0f, 1.0f);
   interpolatedColor = vec4(clamp(position, 0.0f, 1.0f), 1.0f);
}