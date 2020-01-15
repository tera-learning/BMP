#include <fstream>
#include <iostream>
#include <vector>

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

struct NewBitMapHeader {
	int width;
	int height;
};
#pragma pack()

int main(int argc, char* argv[])
{
	//////////////////////////////////////////////////////////
	// 引数チェック
	//////////////////////////////////////////////////////////
	
	if (argc != 3) {
		std::cout << "argument error !" << std::endl;
		return 0;
	}


	//////////////////////////////////////////////////////////
	// ファイルからデータ取得
	//////////////////////////////////////////////////////////
	
	std::ifstream ifs(argv[1], std::ios::binary);
	if ( !ifs) {
		std::cout << "in file open error !" << std::endl;
		return 0;
	}

	BitMapFileHeader fileHeader;
	BitMapInfoHeader infoHeader;

	ifs.read((char*)&fileHeader, sizeof(BitMapFileHeader));
	ifs.read((char*)&infoHeader, sizeof(BitMapInfoHeader));


	//////////////////////////////////////////////////////////
	// フォーマット変換＆ファイル出力
	//////////////////////////////////////////////////////////

	std::ofstream ofs(argv[2], std::ios::binary);
	if (!ofs) {
		std::cout << "out file open error !" << std::endl;
	}

	NewBitMapHeader newHeader;
	newHeader.width = infoHeader.biWidth;
	newHeader.height = infoHeader.biHeight;

	// ヘッダ出力
	ofs.write((char*)&newHeader, sizeof(NewBitMapHeader));

	// 画像データ部分取得
	std::vector<Color> tmpBuffer;

	for (int j = 0; j < infoHeader.biHeight; j++) {
		for (int i = 0; i < infoHeader.biWidth; i++) {

			Color col;
			ifs.read((char*)&col, sizeof(Color));
			tmpBuffer.push_back(col);
		}
	}

	// 画像データ部分出力
	for (int j = infoHeader.biHeight - 1; j >= 0; j--) {
		for (int i = 0; i < infoHeader.biWidth; i++) {
			Color col = tmpBuffer[j * infoHeader.biWidth + i];
			ofs.write((char*)&col, sizeof(Color));
		}
	}

	// データクリア
	tmpBuffer.clear();
	return 0;
}