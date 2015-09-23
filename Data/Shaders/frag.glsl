#version 120 

uniform sampler2D u_Tex; 

varying vec3 v_color; 
varying vec2 v_texCoord; 

void main() 
{ 
	vec4 texColor =  texture2D(u_Tex, v_texCoord).rgba;
	//NOTE(mate):transparency
	/*TODO(mate):fix it*/
#if 1
	if(texColor.a < 0.8)
	{
		discard;
	}
#endif 
	vec3 gamma = vec3(1.0 / 2.2); 
// 	vec3 color = texColor.rgb * v_color; 
	vec3 color = texColor.rgb; 

 	gl_FragColor = vec4(pow(color, gamma), 1.0); 
 } 
