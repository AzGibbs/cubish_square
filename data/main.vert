#version 440

layout(location = 0) in vec4 v_pos;

out gl_PerVertex {
    vec4 gl_Position;
};

void main(void)
{
    //const mat4 scale = mat4(2/800, 0, 0, 0, 0, 2/600, 0, 0, 0, 0, 1, 0, -1.0, -1.0, 0.0, 1.0);
    gl_Position = scale * v_pos;
}
