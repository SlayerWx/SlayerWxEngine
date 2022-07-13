#include "Cube.h"
Cube::Cube() : Entity("Entity")
{
	data.height = 0;
	data.width = 0;
	data.nrChannels = 0;
	data.texture = 0;
}
Cube::Cube(std::string name, const char* filePath) : Entity(name)
{
	data = TextureImporter::ImportTexture(filePath);
	if (data.nrChannels == 4)
		alpha = true;

	material.color = glm::vec4(1.0, 1.0, 1.0, 1.0);
	material.ambient = glm::vec3(1.0, 1.0, 1.0);
	material.shininess = 1;
}
Cube::Cube(std::string name,const char* filePath, const char* diffuse) : Entity(name)
{
	data = TextureImporter::ImportTexture(filePath);
	material.diffuse = TextureImporter::ImportTexture(diffuse);
	if (data.nrChannels == 4)
		alpha = true;

	material.color = glm::vec4(1.0,1.0,1.0,1.0);
	material.ambient = glm::vec3(1.0,1.0,1.0);
	material.shininess = 1;
}
Cube::Cube(std::string name, const char* filePath, const char* diffuse, const char* specular) : Entity(name)
{
	data = TextureImporter::ImportTexture(filePath);
	material.diffuse = TextureImporter::ImportTexture(diffuse);
	material.specular = TextureImporter::ImportTexture(specular);
	if (data.nrChannels == 4)
		alpha = true;

	material.color = glm::vec4(1.0, 1.0, 1.0, 1.0);
	material.ambient = glm::vec3(1.0, 1.0, 1.0);
	material.shininess = 1;
}
void Cube::Draw()
{

	TextureImporter::BindTexture(data.texture);

	if (material.diffuse.nrChannels > 0) TextureImporter::BindTexture1(material.diffuse.texture);
	if (material.specular.nrChannels > 0) TextureImporter::BindTexture2(material.specular.texture);

	renderer->MaterialDraw(vertexMaterial, vertexLength, index, indexLength, model, alpha,material.color
		,material.ambient,   material.diffuse.nrChannels>0,
		material.specular.nrChannels > 0,   material.shininess);
}

void Cube::SetTextureCoordinate(float u0, float v0, float u1, float v1, float u2, float v2, float u3, float v3)
{
	vertexMaterial[6] = u3; //right
	vertexMaterial[7] = v3; //up
	
	vertexMaterial[14] = u1; //right 
	vertexMaterial[15] = v1; //down
	
	vertexMaterial[22] = u0; //left   
	vertexMaterial[23] = v0; //down      
	
	vertexMaterial[30] = u2; //left
	vertexMaterial[31] = v2; //up

}