#version 300 es
precision mediump float;
out vec4 color;
in vec4 interpolatedColor;
uniform vec4 uColor;

void main()
{
   color = interpolatedColor;
}