#ifndef TEXTURE_IMPORTER_H
#define TEXTURE_IMPORTER_H
#include <string>
struct TextureData
{
	unsigned char* pixelData;
	int width;
	int height;
	int nrChannels;
	unsigned int texture;
	std::string path;
	std::string txType;

};

class TextureImporter {
private:

public:
	static TextureData ImportTexture(const char* filePath);
	static TextureData ImportFromFile(const char* path, const std::string& directory);
	static void BindTexture(unsigned int data);
	static void BindTexture1(unsigned int data);
	static void BindTexture2(unsigned int data);
	static void BindClean();
};

#endif