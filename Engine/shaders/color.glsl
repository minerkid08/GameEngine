$vert
#version 330 core
layout(location = 0) in vec3 pos;
uniform mat4 transform;
uniform mat4 viewProj;
void main(){
	gl_Position = viewProj * transform * vec4(pos, 1.0);
}

$frag
#version 330 core
uniform vec4 color;
out vec4 ocolor;
void main(){
	ocolor = vec4(color);
}