#pragma once

#include "CItem.h"

class CItem_Text : public CItem {
public:
	std::string text;
	ID3DXFont* font;
	int fHeight;
	UINT fWeight;
	LPCSTR fName;
	D3DCOLOR color;

	void draw();
	void release();

	CItem_Text( string, string );
	CItem_Text( string name, string text, int fHeight, UINT fWeight, LPCSTR fName, D3DCOLOR color,
					  int dimX, string nItemX, ERelativePositionX rPosX, int posX,
								string nItemY, ERelativePositionY rPosY, int posY) :
			CItem(name, true, false, dimX, 20, nItemX, rPosX, posX, nItemY, rPosY, posY),
			text(text), fHeight(fHeight), fWeight(fWeight), fName(fName), color(color) { this->type = TEXT; };
};