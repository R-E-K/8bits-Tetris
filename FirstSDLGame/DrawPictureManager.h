#pragma once
#include <SDL2/SDL.h>
#include "ImageLoader.h"

class DrawPictureManager
{
public:
	DrawPictureManager();
	~DrawPictureManager();

	void DrawAButton() const;
	void DrawBButton() const;
	void DrawXButton() const;
	void DrawYButton() const;
	void DrawLeftStickButton() const;
	void DrawRightStickButton() const;
	void DrawLBButton() const;
	void DrawRBButton() const;
	void DrawLTButton() const;
	void DrawRTButton() const;
	void DrawBackButton() const;
	void DrawDPadDownButton() const;
	void DrawDPadUpButton() const;
	void DrawDPadLeftButton() const;
	void DrawDPadRightButton() const;
private:
	ImageLoader* ImageLdr;
	void DrawPicture(const char* imageFilePath, SDL_Rect* imagePosition) const;
	static void DestroyPicture(SDL_Texture* pictureGraphic, SDL_Rect* picturePosition);
};

