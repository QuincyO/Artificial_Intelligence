
#pragma once
#include "rlImGui.h"

class Sprite
{
public:

	Sprite() {}
	Sprite(const char* filepath)
	{
		CreateImage(filepath);
	}


	void CreateImage(const char* filepath)
	{
		Sprite::LoadImage(filepath);
		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.width = texture.width;
		srcRect.height = texture.height;

		dstRect;
		dstRect;
		dstRect.width = srcRect.width;
		dstRect.height = srcRect.height;
	}

	void LoadImage(const char* filepath)
	{
		texture = LoadTexture(filepath);
	}

	Rectangle GetSource() { return srcRect; }
	Rectangle GetDest() { return dstRect; }

	void SetSize(int x, int y) { dstRect.width = x; dstRect.height = y; }

	void SetPosition(int x, int y) { dstRect.x = x; dstRect.y = y; }
	void SetPosition(Vector2 tilePosition) { dstRect.x = tilePosition.x; dstRect.y = tilePosition.y; }
	void Animate(float deltaTime) {}

	Texture2D GetTexture() { return texture; }

protected:
	bool isLeft = true;
	Rectangle srcRect, dstRect;
	Texture2D texture;
};