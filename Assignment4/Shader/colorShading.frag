#version 130

in vec2 fragmentPos;
in vec4 fragmentColor;
in vec2 fragmentUV;
out vec4 color;

uniform float time;
uniform sampler2D mySampler;

void main()
{
	vec4 textureColor = texture(mySampler, fragmentUV);
	
	//color blending
	color = textureColor * vec4 
	(
	fragmentColor.r *0.5*(cos(fragmentPos.x+2*time)),
	fragmentColor.g *0.5*(cos(fragmentPos.x+3*time)),
	fragmentColor.b *0.5*(cos(fragmentPos.x+4*time)),
	1.0
	); 
}