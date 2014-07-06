#version 440

out vec4 colour;

void main(void)
{
    const vec2 res = vec2(800, 600);
    colour = vec4(gl_FragCoord.xy / res, 0.0, 1.0);
    colour = vec4(1.0);
}
