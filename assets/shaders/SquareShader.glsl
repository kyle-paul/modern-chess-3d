#type vertex
#version 330 core
layout(location = 0) in vec3 position;

uniform mat4 projection_view;
uniform mat4 model;

void main()
{
    gl_Position = projection_view * model * vec4(position, 1.0);
}

#type fragment
#version 330 core
out vec4 color;
uniform int type;

void main()
{
    if (type == 1)
        color = vec4(1.0, 1.0, 1.0, 1.0);
    else if (type == 0)
        color = vec4(0.0, 0.0, 0.0, 1.0);
    else
        color = vec4(1.0, 0.0, 0.0, 1.0);
}