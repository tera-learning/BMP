#include "TextureManager.h"
#include <fstream>
#include <iostream>

TextureManager::TextureManager()
{
	std::ifstream ifs("Image.nbmp", std::ios::binary);
	if (!ifs) {
		std::cout << "in file open error !" << std::endl;
		return;
	}

	NewBitMapHeader fileHeader;
	ifs.read((char*)&fileHeader, sizeof(NewBitMapHeader));

	m_Width = fileHeader.width;
	m_Height = fileHeader.height;
	m_PixelByte = 4;

	for (int j = 0; j < m_Height; j++) {
		for (int i = 0; i < m_Width; i++) {

			Color col;

			//ファイルを細かく読みにいかない。sizeを取得して一括でよむ
			ifs.read((char*)&col, sizeof(Color));

			//アロケーションが頻繁にはしってしまうので、vectorも一括でサイズを確保しておく
			m_Buffer.push_back(col.blue);
			m_Buffer.push_back(col.green);
			m_Buffer.push_back(col.red);
			m_Buffer.push_back(255);
		}
	}
}


TextureManager::~TextureManager()
{
	m_Buffer.clear();
	m_Width = 0;
	m_Height = 0;
}

int TextureManager::getWidth(void)
{
	return m_Width;
}

int TextureManager::getHeight(void)
{
	return m_Height;
}

int TextureManager::getPixelByte(void)
{
	return m_PixelByte;
}

const unsigned char* TextureManager::getTextureBuffer(void)
{
	return &m_Buffer[0];
}