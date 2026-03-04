#version 330

in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec4 vertexColor;

out vec2 fragTexCoord;
out vec4 fragColor;

uniform mat4 mvp;

uniform vec2 mouse_screen_pos;
uniform float hovering;
uniform float screen_scale;
uniform vec2 screen_size;

void main()
{
    vec4 position = vec4(vertexPosition, 1.0);

    if (hovering > 0.0)
    {
        float mid_dist =
            length(position.xy - 0.5 * screen_size) /
            length(screen_size);

        vec2 mouse_offset =
            (position.xy - mouse_screen_pos) / screen_scale;

        float scale =
            0.2 * (-0.03 - 0.3 * max(0.0, 0.3 - mid_dist))
            * hovering
            * (length(mouse_offset) * length(mouse_offset))
            / (2.0 - mid_dist);

        position.z += scale;
    }

    gl_Position = mvp * position;

    fragTexCoord = vertexTexCoord;
    fragColor = vertexColor;
}