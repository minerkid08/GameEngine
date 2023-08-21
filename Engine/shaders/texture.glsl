$vert
#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 itexCord;
uniform mat4 transform;
uniform mat4 viewProj;
out vec2 texCord;
void main(){
	texCord = itexCord;
	gl_Position = viewProj * transform * vec4(pos, 1.0);
}

$frag
#version 330 core
uniform sampler2D tex;
in vec2 texCord;
out vec4 ocolor;
void main(){
	ocolor = texture(tex, texCord);
}