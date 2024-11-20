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
    if (type == 0)
        color = vec4(0.0, 0.0, 0.0, 1.0);
    else if (type == 1)
        color = vec4(1.0, 1.0, 1.0, 1.0);
    else if (type == 2)
        color = vec4(0.0, 0.7, 0.2, 0.8);
    else if (type == 3)
        color = vec4(0.0, 0.7, 0.2, 0.5);
    else if (type == 4)
        color = vec4(0.9, 0.1, 0.1, 1.0);
    else if (type == 5)
        color = vec4(0.5, 0.5, 0.5, 1.0);
    else if (type == 6)
        color = vec4(0.9, 0.1, 0.6, 1.0);
    else if (type == 7)
        color = vec4(0.0, 0.7, 0.2, 0.9);
    else 
        color = vec4(1.0, 0.0, 0.0, 1.0);
}