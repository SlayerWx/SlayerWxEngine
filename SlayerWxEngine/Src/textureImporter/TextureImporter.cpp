#include "textureImporter.h"
#include <glew.h>
#include <glfw3.h>
#include <iostream>
TextureData TextureImporter::ImportTexture(const char* filePath, bool alpha)
{
	TextureData textureData;
	textureData.pixelData = stbi_load(filePath, &textureData.width, &textureData.height, &textureData.nrChannels, 0);

	if (textureData.pixelData) {
		switch (alpha) {
		case false:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureData.width, textureData.height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData.pixelData);
			glGenerateMipmap(GL_TEXTURE_2D);
			break;
		case true:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureData.width, textureData.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData.pixelData);
			glGenerateMipmap(GL_TEXTURE_2D);
			break;
		}
	}
	else std::cout << "Failed to import texture: pixel data null" << std::endl;

	return textureData;
}

void TextureImporter::LoadTexture(TextureData textureData, bool alpha)
{
	if (textureData.pixelData) {
		switch (alpha) {
		case false:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureData.width, textureData.height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData.pixelData);
			glGenerateMipmap(GL_TEXTURE_2D);
			break;
		case true:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureData.width, textureData.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData.pixelData);
			glGenerateMipmap(GL_TEXTURE_2D);
			break;
		}
	}
	else std::cout << "Failed to load texture: pixel data null" << std::endl;
}