#include "imageUtil.h"

ImageUtil::ImageUtil()
{
}

ImageUtil::~ImageUtil()
{
	UnloadTexture(texture);
}


void ImageUtil::DrawImage(std::string dir, Position position, int cellSize, int sizeOffset) {
	Image image = LoadImage(dir.c_str());
	ImageResize(&image, cellSize + sizeOffset, cellSize + sizeOffset);
	texture = LoadTextureFromImage(image);
	UnloadImage(image);

	DrawTexture(texture, position.column * cellSize + abs(sizeOffset) / 2, position.row * cellSize + abs(sizeOffset) / 2, WHITE);
}