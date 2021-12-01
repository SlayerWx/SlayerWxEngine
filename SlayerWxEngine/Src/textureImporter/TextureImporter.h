#ifndef TEXTURE_IMPORTER_H
#define TEXTURE_IMPORTER_H
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

struct TextureData
{
	unsigned char* pixelData;
	int width;
	int height;
	int nrChannels;
};

class TextureImporter {
private:

public:
	static TextureData ImportTexture(const char* filePath, bool alpha);
	static void LoadTexture(TextureData textureData, bool alpha);
};

#endif