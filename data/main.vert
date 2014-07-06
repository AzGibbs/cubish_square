#version 440

layout(location = 0) in dvec4 v_pos;

layout(std140) uniform MVP {
    dmat4 model;
    dmat4 view;
    dmat4 projection;
};

out gl_PerVertex {
    vec4 gl_Position;
};


void main(void)
{
    gl_Position = vec4(view * v_pos);
}
