#include "textureImporter.h"
#include <glew.h>
#include <glfw3.h>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
TextureData TextureImporter::ImportTexture(const char* filePath)
{
	TextureData textureData;
	textureData.path = filePath;
	stbi_set_flip_vertically_on_load(1);
	glGenTextures(1, &textureData.texture);
	glBindTexture(GL_TEXTURE_2D, textureData.texture);
	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	textureData.pixelData = stbi_load(filePath, &textureData.width, &textureData.height, &textureData.nrChannels, STBI_rgb_alpha);
	if (textureData.pixelData) 
	{
		if(textureData.nrChannels != 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, textureData.width, textureData.height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData.pixelData);
		else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, textureData.width, textureData.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData.pixelData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to import texture: pixel data null: " << textureData.path << std::endl;
	}

	stbi_image_free(textureData.pixelData);
	return textureData;
}

TextureData TextureImporter::ImportFromFile(const char* path, const std::string& directory) {
	std::string filename = std::string(path);
	filename = directory + '/' + filename;

	TextureData textureData;
	textureData.path = path;
	glGenTextures(1, &textureData.texture);

	int width, height, nrComponents;
	textureData.pixelData = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (textureData.pixelData)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureData.texture);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, textureData.pixelData);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(textureData.pixelData);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(textureData.pixelData);
		textureData.path = "";
	}

	return textureData;
}

void TextureImporter::BindTexture(unsigned int data)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, data);
}
void TextureImporter::BindTexture1(unsigned int data)
{

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, data);
}
void TextureImporter::BindTexture2(unsigned int data)
{
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, data);
}