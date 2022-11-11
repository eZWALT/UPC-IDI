#version 330 core

out vec4 FragColor;
uniform float val;

void main() {
    FragColor = vec4(val*0.5, 0.1*val, val * 0.2, 1);
}

