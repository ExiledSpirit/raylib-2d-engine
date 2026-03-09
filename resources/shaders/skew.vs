#version 330

in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec4 vertexColor;

out vec2 fragTexCoord;
out vec4 fragColor;

uniform mat4 mvp;
uniform vec2 tilt;
uniform float hover;

void main()
{
  vec3 pos = vertexPosition;

  if (hover > 0.0)
  {
    float skewX = tilt.x * 8.0;
    float skewY = tilt.y * 8.0;

    pos.x += vertexPosition.y * skewX;
    pos.y += vertexPosition.x * skewY;
  }

  gl_Position = mvp * vec4(pos, 1.0);

  fragTexCoord = vertexTexCoord;
  fragColor = vertexColor;
}