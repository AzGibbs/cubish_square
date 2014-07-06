#version 440

layout(location = 0) in vec4 v_pos;

out gl_PerVertex {
    vec4 gl_Position;
};

void main(void)
{
    const mat4 view = mat4(1.0 / 400.0, 0, 0, 0, 0, 1.0 / 300.0, 0, 0, 0, 0, 1.0, 0, -1.0, -1.0, 0.0, 1.0);
    gl_Position = view * v_pos;
}
