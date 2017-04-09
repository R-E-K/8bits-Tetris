#pragma once
#include <SDL2/SDL.h>
#include "SDLMainObjectsProvider.h"
#include "ImageLoader.h"
#include "DrawTextService.h"

class DrawGameButtonLabelService
{
public:
	DrawGameButtonLabelService();
	~DrawGameButtonLabelService();

	void DrawWithLabel(const char* pathFile, char* label, int x, int y) const;
private:
	DrawTextService* drawTextSrvc;
};

