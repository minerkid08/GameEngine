$vert
#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 icolor;
layout(location = 2) in vec2 itexCord;
uniform mat4 viewProj;
out vec2 texCord;
out vec4 color2;
void main(){
	texCord = itexCord;
	color2 = icolor;
	gl_Position = viewProj * vec4(pos, 1.0);
}

$frag
#version 330 core
uniform sampler2D tex;
uniform vec4 color;
uniform float tile;
in vec4 color2;
in vec2 texCord;
out vec4 ocolor;
void main(){
	//ocolor = texture(tex, texCord * tile) * color;
	ocolor = color2;
}