#type vertex
#version 330 core
layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texture;
layout(location = 2) in vec3 a_normals;

uniform mat4 projection_view;
uniform mat4 model;

out vec2 v_texture;
out vec3 v_normals;

void main()
{
    gl_Position = projection_view * model * vec4(a_position, 1.0);
    v_texture = a_texture;
    v_normals = a_normals;
}

#type fragment
#version 330 core
layout(location=0) out vec4 render;
layout(location=1) out int row;
layout(location=2) out int col;

in vec2 v_texture;
in vec3 v_normals;

uniform vec3 light_direction;
uniform vec3 v_color;
uniform int v_row;
uniform int v_col;

void main()
{
    float lightStrength = max(0.5, dot(v_normals, normalize(light_direction))) ;
    vec3 color = v_color * lightStrength;
    render = vec4(color, 1.0);
    row = v_row;
    col = v_col;
}