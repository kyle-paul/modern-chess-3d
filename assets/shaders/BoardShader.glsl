#type vertex
#version 330 core
layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_color;

out vec3 v_color;

uniform mat4 projection_view;
uniform mat4 model;

void main()
{
    gl_Position = projection_view * vec4(a_position, 1.0);
    v_color = a_color;
}

#type fragment
#version 330 core
in vec3 v_color;
out vec4 color;

void main()
{
    color = vec4(v_color, 1.0);
}