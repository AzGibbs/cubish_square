#version 330

layout(location = 0) in vec4 v_pos;

layout(std140) uniform MVP {
    mat4 model;
    mat4 view;
    mat4 projection;
};

out gl_PerVertex {
    vec4 gl_Position;
};


void main(void)
{
    gl_Position = view * v_pos;
}
