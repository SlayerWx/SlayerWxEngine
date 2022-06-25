#include "Cube.h"
Cube::Cube() : Entity()
{
	data.height = 0;
	data.width = 0;
	data.nrChannels = 0;
	data.texture = 0;
}

Cube::Cube(const char* filePath) : Entity()
{
	data = TextureImporter::ImportTexture(filePath);
	if (data.nrChannels == 4)
		alpha = true;

	material.color = glm::vec4(1.0,1.0,0.0,1.0);
	material.ambient = glm::vec3(1.0,1.0,1.0);
	material.diffuse = glm::vec3(1.0,1.0,1.0);
	material.shininess = 1;
	material.specular = glm::vec3(1.0,1.0,1.0);
}

void Cube::Draw()
{
	TextureImporter::BindTexture(data.texture);
	renderer->MaterialDraw(vertexMaterial, vertexLength, index, indexLength, model, alpha,material.color,material.ambient,material.diffuse,
		material.specular,material.shininess);
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