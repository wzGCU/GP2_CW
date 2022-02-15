#version 400 

out vec4 FragColor; 

in vec4 v_pos;  
 
uniform vec3 fogColor; //color of the fog


uniform float maxDist; //distance to the point where fog is maximal
uniform float minDist; //dsitance from eye to the fog's starting point

void main()  
{ 

float dist = abs( v_pos.z ); //return the absolute value (i.e the positive), store the distance from the surface point to the eye position, z coordinate used as an estimate distance

float fogFactor = (Fog.maxDist - dist) / (Fog.maxDist - Fog.minDist); //computed using the prev equation so it is between 0 an 1

fogFactor = clamp( fogFactor, 0.0, 1.0 ); // clamp between 0 and 1 

vec3 lightColor = vec3(0.1,0.1,0.1); 

vec3 color = mix( fogColor, lightColor, fogFactor); 

FragColor = vec4(color, 1.0); 
} 