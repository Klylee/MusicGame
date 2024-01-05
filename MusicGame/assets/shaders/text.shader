#shader vertex
#version 330 core
layout (location = 0) in vec3 _vertex; // <vec2 pos, vec2 tex>
layout (location = 1) in vec2 _texcoord; 
out vec2 TexCoords;

uniform mat4 _projection;
uniform mat4 _view;
uniform mat4 _model;

void main()
{
    gl_Position = _projection * _view * _model * vec4(_vertex, 1.0);
    TexCoords = _texcoord;
}

#shader fragment
#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D _text;
uniform vec4 _textColor;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(_text, TexCoords).r);
    color = _textColor * sampled;
}