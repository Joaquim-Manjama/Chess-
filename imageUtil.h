#pragma once
#include <raylib.h>
#include <string>
#include <map>
#include "position.h"

class ImageUtil {
public:
	ImageUtil();
	~ImageUtil();
	void DrawImage(std::string dir, Position position, int cellSize, int sizeOffset);
private:
	Texture2D texture;
};