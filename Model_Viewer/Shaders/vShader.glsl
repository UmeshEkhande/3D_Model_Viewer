in vec4 posAttr;
in vec4 colAttr;
in vec3 normalAttr;

uniform highp mat4 u_ProjMatrix;
uniform highp mat4 u_modelMatrix;
uniform highp mat4 u_viewMatrix;

void main() {


   gl_Position = u_ProjMatrix * u_modelMatrix * u_viewMatrix * posAttr;
}