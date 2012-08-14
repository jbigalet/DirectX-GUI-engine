#include "CItem_ProgressBar.h"
#include "GUI_Engine.h"


void CItem_ProgressBar::updateDim(){
	dimX = (position == HORIZONTAL) ? length : thickness;
	dimY = (position == HORIZONTAL) ? thickness : length;
}


void CItem_ProgressBar::draw(){
		// Draw the border
	m_engine.drawRectangle(iPosX, iPosY, dimX, dimY, extColor);
	//logIt("Drawing: %ix%i : %ix%i", iPosX, iPosY, dimX, dimY);

		// Draw the progress
	int range = maxValue - minValue;
	if( range == 0 ) return;
	int iX = (dimX - 2*borderL) * (value - minValue) / range;
	int iY = (dimY - 2*borderL) * (value - minValue) / range;
	int sY = (dimY - 2*borderL) - iY;
	
	if(position == HORIZONTAL)	m_engine.drawRectangle(iPosX+borderL, iPosY+borderT,  iX, dimY-2*borderT,     intColor);
	else						m_engine.drawRectangle(iPosX+borderT, iPosY+borderL + sY, dimX-2*borderT, iY, intColor);
}


CItem_ProgressBar::CItem_ProgressBar(string name, int minValue, int maxValue, int length, int thickness, int borderL, int borderT,
		D3DCOLOR extColor, D3DCOLOR intColor, EPosition position,
		string nItemX, ERelativePositionX rPosX, int posX, string nItemY, ERelativePositionY rPosY, int posY ) :
	CItem(name, false, true, 0, 0, nItemX, rPosX, posX, nItemY, rPosY, posY),
	minValue(minValue), maxValue(maxValue), length(length), thickness(thickness), borderL(borderL), borderT(borderT),
	extColor(extColor), intColor(intColor), position(position)
{
	this->type = PROGRESSBAR;
	this->value = (minValue + maxValue)/2;
}



int CItem_ProgressBar::getClickedValue( tagPOINT curPos ){
	int x;
	if( position == HORIZONTAL )
		x = minValue + (maxValue - minValue) * (curPos.x - iPosX - borderL) / (dimX - 2*borderL);
	else
		x = maxValue - (maxValue - minValue) * (curPos.y - iPosY - borderL) / (dimY - 2*borderL);
	
	return (x<minValue) ? minValue : (x>maxValue ? maxValue : x);
}