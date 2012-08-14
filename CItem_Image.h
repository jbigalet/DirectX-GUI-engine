#pragma once

#include "CItem.h"

class CItem_Image : public CItem {
public:
	string fImage;
	LPD3DXSPRITE pSprite;
	LPDIRECT3DTEXTURE9 pTexture;

	void updateDim();
	void draw();
	void release();

	CItem_Image(string name, string fImage, bool isDraggable, bool isClickable,
				string nItemX, ERelativePositionX rPosX, int posX,
				string nItemY, ERelativePositionY rPosY, int posY);
};
