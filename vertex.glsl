#version 300 es

layout(location = 0) in vec3 position;
out vec4 interpolatedColor;
uniform mat4 transform;
void main()
{
   gl_Position = transform * vec4(position.x, position.y, position.z, 1.0);
   interpolatedColor = vec4(clamp(position, 0.0f, 1.0f), 1.0f);
}