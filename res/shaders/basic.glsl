#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
out vec2 TexCoord;
  
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
  gl_Position = projection * view * model * vec4(aPos, 1.0f);
  TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}

#shader fragment
#version 330 core
out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
  float ambientStrength = 0.1;
  vec3 ambient = ambientStrength * lightColor;
  vec3 temp = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2).rgb;
  FragColor = vec4(ambient * temp, 1.0);
}
