#shader vertex
#version 330 core
layout (location = 0) in vec3 position;
layout(location = 1) in vec2 atexCoord;

uniform mat4 _projection;
uniform mat4 _view;
uniform mat4 _model;

out vec2 texCoord;

void main()
{
    texCoord = atexCoord;
    gl_Position = _projection * _view * _model * vec4(position, 1.0f);
};

#shader fragment
#version 330 core
layout(location = 0) out vec4 fragment_color;

in vec2 texCoord;

uniform sampler2D _texture;
uniform vec4 _color;
uniform float _textureTransparency;

void main()
{
    fragment_color = mix(texture2D(_texture, texCoord), _color, _textureTransparency);
};
