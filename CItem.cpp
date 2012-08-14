#include "CItem.h"
#include "GUI_Engine.h"


void CItem::createPosAndDim(int dimX, int dimY, string nItemX, ERelativePositionX rPosX, int posX, 
										 string nItemY, ERelativePositionY rPosY ,int posY){
	this->dimX = dimX;
	this->dimY = dimY;
	CPositionX PosX = { m_engine.getItem(nItemX), rPosX, posX };
	this->posX = PosX;
	CPositionY PosY = { m_engine.getItem(nItemY), rPosY, posY };
	this->posY = PosY;
}


void CItem::update(){
	checkParentInvisibility();
	updateDim();
	updatePos();
	onUpdate();
}

void CItem::checkParentInvisibility(){
	isParentInvisible = (posX.rItem->isParentInvisible || posX.rItem->isInvisible)
					 && (posY.rItem->isParentInvisible || posY.rItem->isInvisible);
}

void CItem::updatePos(){
	updatePosX();
	updatePosY();
}

void CItem::updatePosX(){
	switch( posX.rPos ){
		case LEFTINTERIOR:
			iPosX = posX.pos + posX.rItem->iPosX;
			break;
		case RIGHTEXTERIOR:
			iPosX = posX.pos + posX.rItem->iPosX + posX.rItem->dimX;
			break;
		case MIDDLEX:
			iPosX = posX.pos + posX.rItem->iPosX + ( posX.rItem->dimX - dimX ) / 2;
			break;

		case LEFTEXTERIOR:
			iPosX = -posX.pos + posX.rItem->iPosX - dimX;
			break;
		case RIGHTINTERIOR:
			iPosX = -posX.pos + posX.rItem->iPosX - dimX + posX.rItem->dimX;
			break;
		}
}

void CItem::updatePosY(){
	switch( posY.rPos ){
		case TOPINTERIOR:
			iPosY = posY.pos + posY.rItem->iPosY;
			break;
		case BOTTOMEXTERIOR:
			iPosY = posY.pos + posY.rItem->iPosY + posY.rItem->dimY;
			break;
		case MIDDLEY:
			iPosY = posY.pos + posY.rItem->iPosY + ( posY.rItem->dimY - dimY ) / 2;
			break;

		case TOPEXTERIOR:
			iPosY = -posY.pos + posY.rItem->iPosY - dimY;
			break;
		case BOTTOMINTERIOR:
			iPosY = -posY.pos + posY.rItem->iPosY - dimY + posY.rItem->dimY;
			break;
		}
}
	