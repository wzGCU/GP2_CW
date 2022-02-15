#version 400 
//passes the vertex positions and normal to the fragment shader

layout (location = 0) in vec3 VertexPosition; 

 
uniform mat4 transform; 

out vec4 v_pos;  

void main() 

{ 

v_pos = vec4(VertexPosition, 1.0); 

gl_Position = transform * vec4(VertexPosition, 1.0); 

} 