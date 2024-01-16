attribute vec4 posAttr;
attribute vec4 colAttr;
attribute vec3 normalAttr;


varying vec3 vert;
varying vec3 vertNormal;

uniform mat3 normalMatrix;
uniform highp mat4 u_ProjMatrix;
uniform highp mat4 u_modelMatrix;
uniform highp mat4 u_viewMatrix;
uniform int u_lightingEnabled;

void main() {
vert = posAttr.xyz;
vertNormal = normalMatrix * normalAttr;
gl_Position = u_ProjMatrix * u_modelMatrix * u_viewMatrix * posAttr;

}