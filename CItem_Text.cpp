#include "CItem_Text.h"
#include "GUI_Engine.h"


CItem_Text::CItem_Text(std::string name, std::string text) {
	this->name = name;
	this->text = text;
	color = D3DCOLOR_ARGB(255, 255, 255, 255);

	isClickable = false;
	type = TEXT;
}

void CItem_Text::draw(){
	RECT rect;
	rect.left = iPosX;
	rect.top = iPosY;
	rect.right = iPosX + dimX;
	rect.bottom = iPosY + dimY;

	D3DXCreateFont( m_engine.pDevice, fHeight, 0, fWeight, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, fName, &font );

	if( posX.rPos == RIGHTINTERIOR || posX.rPos == LEFTEXTERIOR )	font->DrawText(NULL, text.c_str(), -1, &rect, DT_RIGHT, color );
	else if( posX.rPos == MIDDLEX )									font->DrawText(NULL, text.c_str(), -1, &rect, DT_CENTER, color );
	else															font->DrawText(NULL, text.c_str(), -1, &rect, NULL, color );
}

void CItem_Text::release(){
	font->Release();
}
