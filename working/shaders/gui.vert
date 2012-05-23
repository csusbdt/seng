//--------------------------------------------------------------------------------------
// File: gui.vert
//--------------------------------------------------------------------------------------


uniform mat4 worldMatrix;
uniform mat4 projectionMatrix;
varying vec2 texture_coordinate;

void main()
{
	gl_Position = projectionMatrix * worldMatrix * gl_Vertex;
	
	texture_coordinate = gl_MultiTexCoord0.st;
}