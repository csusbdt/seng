//--------------------------------------------------------------------------------------
// File: gui.frag
//--------------------------------------------------------------------------------------

varying vec2 texture_coordinate;
uniform sampler2D diffuseTexture;
uniform vec4 pickColor;
uniform int pick;
void main()
{
	if (pick == 1)
	{
		vec4 color = texture2D(diffuseTexture, texture_coordinate);
		if (color[3] == 0) 
		{
		}
		else
		{
			gl_FragColor = pickColor;
		}
	}
	else
	{
		gl_FragColor = texture2D(diffuseTexture, texture_coordinate);
		
	}
}	
