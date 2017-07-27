#pragma once
#include "DrawPictureManager.h"
#include "GamepadButtonsFilePathConsts.h"
#include "SDLMainObjectsProvider.h"

namespace REKFramework
{
	DrawPictureManager::DrawPictureManager()
	{
		
	}


	DrawPictureManager::~DrawPictureManager()
	{
		
	}

	void DrawPictureManager::DrawAButton() const
	{
		SDL_Rect itemMenuPosition;
		itemMenuPosition.x = 10;
		itemMenuPosition.y = 10;

		DrawPicture(GamepadButtonsFilePathConsts::AButton, itemMenuPosition);
	}

	void DrawPictureManager::DrawBButton() const
	{
		SDL_Rect itemMenuPosition;
		itemMenuPosition.x = 120;
		itemMenuPosition.y = 10;

		DrawPicture(GamepadButtonsFilePathConsts::BButton, itemMenuPosition);
	}

	void DrawPictureManager::DrawXButton() const
	{
		SDL_Rect itemMenuPosition;
		itemMenuPosition.x = 230;
		itemMenuPosition.y = 10;

		DrawPicture(GamepadButtonsFilePathConsts::XButton, itemMenuPosition);
	}

	void DrawPictureManager::DrawYButton() const
	{
		SDL_Rect itemMenuPosition;
		itemMenuPosition.x = 340;
		itemMenuPosition.y = 10;

		DrawPicture(GamepadButtonsFilePathConsts::YButton, itemMenuPosition);
	}

	void DrawPictureManager::DrawLBButton() const
	{
		SDL_Rect itemMenuPosition;
		itemMenuPosition.x = 10;
		itemMenuPosition.y = 120;

		DrawPicture(GamepadButtonsFilePathConsts::LBButton, itemMenuPosition);
	}

	void DrawPictureManager::DrawRBButton() const
	{
		SDL_Rect itemMenuPosition;
		itemMenuPosition.x = 120;
		itemMenuPosition.y = 120;

		DrawPicture(GamepadButtonsFilePathConsts::RBButton, itemMenuPosition);
	}

	void DrawPictureManager::DrawLTButton() const
	{
		SDL_Rect itemMenuPosition;
		itemMenuPosition.x = 230;
		itemMenuPosition.y = 120;

		DrawPicture(GamepadButtonsFilePathConsts::LTButton, itemMenuPosition);
	}

	void DrawPictureManager::DrawRTButton() const
	{
		SDL_Rect itemMenuPosition;
		itemMenuPosition.x = 340;
		itemMenuPosition.y = 120;

		DrawPicture(GamepadButtonsFilePathConsts::RTButton, itemMenuPosition);
	}


	void DrawPictureManager::DrawDPadDownButton() const
	{
		SDL_Rect itemMenuPosition;
		itemMenuPosition.x = 10;
		itemMenuPosition.y = 230;

		DrawPicture(GamepadButtonsFilePathConsts::DpadDownButton, itemMenuPosition);
	}

	void DrawPictureManager::DrawDPadUpButton() const
	{
		SDL_Rect itemMenuPosition;
		itemMenuPosition.x = 120;
		itemMenuPosition.y = 230;

		DrawPicture(GamepadButtonsFilePathConsts::DpadUpButton, itemMenuPosition);
	}

	void DrawPictureManager::DrawDPadLeftButton() const
	{
		SDL_Rect itemMenuPosition;
		itemMenuPosition.x = 230;
		itemMenuPosition.y = 230;

		DrawPicture(GamepadButtonsFilePathConsts::DpadLeftButton, itemMenuPosition);
	}

	void DrawPictureManager::DrawDPadRightButton() const
	{
		SDL_Rect itemMenuPosition;
		itemMenuPosition.x = 340;
		itemMenuPosition.y = 230;

		DrawPicture(GamepadButtonsFilePathConsts::DpadRightButton, itemMenuPosition);
	}

	void DrawPictureManager::DrawLeftStickButton() const
	{
		SDL_Rect itemMenuPosition;
		itemMenuPosition.x = 10;
		itemMenuPosition.y = 340;

		DrawPicture(GamepadButtonsFilePathConsts::L3Button, itemMenuPosition);
	}

	void DrawPictureManager::DrawRightStickButton() const
	{
		SDL_Rect itemMenuPosition;
		itemMenuPosition.x = 120;
		itemMenuPosition.y = 340;

		DrawPicture(GamepadButtonsFilePathConsts::R3Button, itemMenuPosition);
	}

	void DrawPictureManager::DrawBackButton() const
	{
		SDL_Rect itemMenuPosition;
		itemMenuPosition.x = 230;
		itemMenuPosition.y = 340;

		DrawPicture(GamepadButtonsFilePathConsts::BackButton, itemMenuPosition);
	}

	void DrawPictureManager::DrawPicture(std::string const& imageFilePath, SDL_Rect& imagePosition) const
	{
		auto image = ImageLoader::GetImage(imageFilePath);
		auto texture = std::unique_ptr<SDL_Texture, SdlDeleter>(
			SDL_CreateTextureFromSurface(SDLMainObjectsProvider::GetRendererRawPointer(), image.get()),
			SdlDeleter()
			);

		int textureWidth, textureHeight;
		SDL_QueryTexture(texture.get(), nullptr, nullptr, &textureWidth, &textureHeight);

		imagePosition.w = textureWidth;
		imagePosition.h = textureHeight;

		SDL_RenderCopy(SDLMainObjectsProvider::GetRendererRawPointer(), texture.get(), nullptr, &imagePosition);
	}
}