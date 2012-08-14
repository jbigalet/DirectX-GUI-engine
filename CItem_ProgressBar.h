#pragma once

#include "CItem.h"

enum EPosition {
	HORIZONTAL,
	VERTICAL
};

class CItem_ProgressBar : public CItem {
public:
	int value;
	int minValue;
	int maxValue;
	int thickness;
	int length;
	int borderT;
	int borderL;
	D3DCOLOR extColor;
	D3DCOLOR intColor;
	EPosition position;

	virtual void updateDim();
	void draw();
	int getClickedValue( tagPOINT );

	CItem_ProgressBar(string name, int minValue, int maxValue, int length, int thickness, int borderX, int borderY,
		D3DCOLOR extColor, D3DCOLOR intColor, EPosition position,
		string nItemX, ERelativePositionX rPosX, int posX, string nItemY, ERelativePositionY rPosY, int posY );
};