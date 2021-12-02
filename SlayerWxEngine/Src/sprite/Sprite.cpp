#include "Sprite.h"

Sprite::Sprite() : Entity2D()
{
	//c++ xd
}

Sprite::Sprite(const char* filePath) : Entity2D()
{
	data = TextureImporter::ImportTexture(filePath);
	if(data.nrChannels == 4)
	alpha = true;
}

void Sprite::Draw()
{
	TextureImporter::BindTexture(data.texture);
	renderer->SpriteDraw(vertexSprite, vertexLength, index, indexLength, model,alpha);
}
