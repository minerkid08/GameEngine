$vert
#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 icolor;
layout(location = 2) in vec2 itexCord;
layout(location = 3) in float itexInd;
layout(location = 4) in float itile;
uniform mat4 viewProj;
out vec2 texCord;
out vec4 color;
out float texInd;
out float tile;
void main(){
	texCord = itexCord;
	color = icolor;
	texInd = itexInd;
	tile = itile;
	gl_Position = viewProj * vec4(pos, 1.0);
}

$frag
#version 330 core
uniform sampler2D tex[32];
in vec4 color;
in vec2 texCord;
in float texInd;
in float tile;
out vec4 ocolor;
void main(){
	vec4 texColor;
	switch (int(texInd)) {
		case 0:  texColor = texture(tex[0],  texCord * tile); break;
		case 1:  texColor = texture(tex[1],  texCord * tile); break;
		case 2:  texColor = texture(tex[2],  texCord * tile); break;
		case 3:  texColor = texture(tex[3],  texCord * tile); break;
		case 4:  texColor = texture(tex[4],  texCord * tile); break;
		case 5:  texColor = texture(tex[5],  texCord * tile); break;
		case 6:  texColor = texture(tex[6],  texCord * tile); break;
		case 7:  texColor = texture(tex[7],  texCord * tile); break;
		case 8:  texColor = texture(tex[8],  texCord * tile); break;
		case 9:  texColor = texture(tex[9],  texCord * tile); break;
		case 10: texColor = texture(tex[10], texCord * tile); break;
		case 11: texColor = texture(tex[11], texCord * tile); break;
		case 12: texColor = texture(tex[12], texCord * tile); break;
		case 13: texColor = texture(tex[13], texCord * tile); break;
		case 14: texColor = texture(tex[14], texCord * tile); break;
		case 15: texColor = texture(tex[15], texCord * tile); break;
		case 16: texColor = texture(tex[16], texCord * tile); break;
		case 17: texColor = texture(tex[17], texCord * tile); break;
		case 18: texColor = texture(tex[18], texCord * tile); break;
		case 19: texColor = texture(tex[19], texCord * tile); break;
		case 20: texColor = texture(tex[20], texCord * tile); break;
		case 21: texColor = texture(tex[21], texCord * tile); break;
		case 22: texColor = texture(tex[22], texCord * tile); break;
		case 23: texColor = texture(tex[23], texCord * tile); break;
		case 24: texColor = texture(tex[24], texCord * tile); break;
		case 25: texColor = texture(tex[25], texCord * tile); break;
		case 26: texColor = texture(tex[26], texCord * tile); break;
		case 27: texColor = texture(tex[27], texCord * tile); break;
		case 28: texColor = texture(tex[28], texCord * tile); break;
		case 29: texColor = texture(tex[29], texCord * tile); break;
		case 30: texColor = texture(tex[30], texCord * tile); break;
		case 31: texColor = texture(tex[31], texCord * tile); break;
	}
	ocolor = texColor * color;
}