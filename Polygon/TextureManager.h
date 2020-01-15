#pragma once
#include <vector>

#pragma pack(1)
struct NewBitMapHeader {
	int width;
	int height;
};

struct Color {
	unsigned char blue;
	unsigned char green;
	unsigned char red;
};
#pragma pack()

class TextureManager final
{
private:
	std::vector<unsigned char> m_Buffer;
	int m_Width;
	int m_Height;
	int m_PixelByte;

public:
	TextureManager();
	TextureManager(const TextureManager& textureManager) = delete;
	TextureManager& operator=(const TextureManager& textureManager) = delete;
	/* virtual */ ~TextureManager();

	int getWidth(void);
	int getHeight(void);
	int getPixelByte(void);
	const unsigned char* getTextureBuffer(void);
};

