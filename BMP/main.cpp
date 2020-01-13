#include <fstream>
#include <iostream>

//////////////////////////////////////////////////////////
// 構造体宣言
//////////////////////////////////////////////////////////
#pragma pack(1)
struct BitMapFileHeader {
	unsigned short bfType;
	unsigned long bfSize;
	unsigned short bfReserved1;
	unsigned short bfReserved2;
	unsigned long bfOffBIts;
};

struct BitMapInfoHeader {
	unsigned int biSize;
	int biWidth;
	int biHeight;
	unsigned short biPlanes;
	unsigned short biBitCount;
	unsigned int biCompression;
	unsigned int biSizeImage;
	int biXPixPerMeter;
	int biYPixPerMeter;
	unsigned int biClrUsed;
	unsigned int biCirImportant;
};

struct Color {
	unsigned char blue;
	unsigned char green;
	unsigned char red;
};
#pragma pack()

int main(void)
{
	//////////////////////////////////////////////////////////
	// ファイルからデータ取得
	//////////////////////////////////////////////////////////
	
	std::ifstream ifs("Image.bmp", std::ios::binary);
	if ( !ifs) {
		std::cout << "in file open error !" << std::endl;
		return 0;
	}

	BitMapFileHeader fileHeader;
	BitMapInfoHeader infoHeader;

	ifs.read((char*)&fileHeader, sizeof(BitMapFileHeader));
	ifs.read((char*)&infoHeader, sizeof(BitMapInfoHeader));


	//////////////////////////////////////////////////////////
	// データ変換＆ファイル出力
	//////////////////////////////////////////////////////////

	std::ofstream ofs("NegaPosi.bmp", std::ios::binary);
	if (!ofs) {
		std::cout << "out file open error !" << std::endl;
	}

	ofs.write((char*)&fileHeader, sizeof(BitMapFileHeader));
	ofs.write((char*)&infoHeader, sizeof(BitMapInfoHeader));

	for (int j = 0; j < infoHeader.biHeight; j++) {
		for (int i = 0; i < infoHeader.biWidth; i++) {

			Color col;
			ifs.read((char*)&col, sizeof(Color));

			col.blue = 255 - col.blue;
			col.green = 255 - col.green;
			col.red = 255 - col.red;

			ofs.write((char*)&col, sizeof(Color));
		}
	}
	

	return 0;
}