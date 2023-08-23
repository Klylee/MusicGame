#shader vertex
#version 330 core
layout (location = 0) in vec3 position;

uniform mat4 _projection;
uniform mat4 _view;
uniform mat4 _model;

void main()
{
    gl_Position = _projection * _view * _model * vec4(position, 1.0f);
};

#shader fragment
#version 330 core
layout(location = 0) out vec4 fragment_color;

uniform int _code;

void main()
{
    fragment_color = vec4(_code / 255.0, 0, 0, 0);
};