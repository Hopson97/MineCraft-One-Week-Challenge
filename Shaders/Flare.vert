#version 330

in vec2 inVertexPosition;
out vec2 passTextureCoords;

uniform vec4 transform;

void main(void){
	

	pass_textureCoords = in_position + vec2(0.5, 0.5);
	pass_textureCoords.y = 1.0 - pass_textureCoords.y;
	
	vec2 screenPosition = in_position * transform.zw + transform.xy;
	//no need for conversion here
	gl_Position = vec4(screenPosition, 0.9999, 1.0);

}