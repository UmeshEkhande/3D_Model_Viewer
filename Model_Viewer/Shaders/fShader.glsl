varying highp vec3 vert;
varying highp vec3 vertNormal;
uniform highp vec3 lightPos;
uniform int u_lightingEnabled;

void main() {
if(u_lightingEnabled==1)
{

highp vec3 LightDir = normalize(lightPos - vert);
highp float NL = max(dot(normalize(vertNormal), LightDir), 0.0);

highp vec3 color = vec3(1.0, 0.0, 0.0);
highp vec3 col = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);

gl_FragColor = vec4(col, 0.0);
}
else if(u_lightingEnabled==2)
{
gl_FragColor = vec4(1.0,1.0,0.0,0.0);
}

gl_FragColor.a = 1.0;
}