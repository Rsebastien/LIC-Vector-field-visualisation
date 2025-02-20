#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 FragPos;
out vec3 Normal;
out vec2 TextCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
	//Normal = aNormal;

	gl_Position = projection * view * model * vec4(aPos, 1.0);
    mat3 normalMatrix = mat3(transpose(inverse(model)));
    Normal = vec3(vec4(normalMatrix * aNormal, 0.0));

	TextCoords = aTexCoord;
}
