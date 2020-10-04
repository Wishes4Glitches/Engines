#version 450 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 Colour;
in vec3 FragPosition;

out vec4 fColour;

struct MaterialStruct
{
	float matShininess; //Ns
	float matTransparency; //d
	vec3 matAmbient; //Ka
	vec3 matDiffuse; //Kd
	vec3 matSpecular; //Ks
	sampler2D texture;
};

struct LightStruct
{
	vec3 lightPosition;
	float lightAmbient;
	float lightDiffuse;
	vec3 lightColour;
};

//uniform sampler2D inputTexture; //uniform for newly created material structure
uniform vec3 viewPos;
uniform LightStruct light;
uniform MaterialStruct material;

void main()
{
	//ambient
	vec3 ambient = light.lightAmbient * material.matAmbient * texture(material.texture, TexCoords).rgb * light.lightColour;

	//diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.lightPosition - FragPosition);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * material.matDiffuse) * texture(material.texture, TexCoords).rgb * light.lightColour;

	//specular
	vec3 viewDir = normalize(viewPos-FragPosition);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.matShininess);
	vec3 specular = (spec * material.matSpecular) * light.lightColour;

	vec3 result = ambient + diffuse + specular;

	fColour = vec4(result, material.matTransparency);
	//fColour = texture(inputTexture, TexCoords);
}