#include "CItem_Viewport.h"

CItem_Viewport::CItem_Viewport(){
	name = "Viewport";
	isDraggable = false;
	isClickable = false;
	isInvisible = false;
	isParentInvisible = false;
	//updatePosAndDim();
}

void CItem_Viewport::updateDim(){
	D3DVIEWPORT9 pViewport;
	m_engine.pDevice->GetViewport( &pViewport );

	dimX = pViewport.Width;
	dimY = pViewport.Height;
}

void CItem_Viewport::updatePos(){
	iPosX = 0;
	iPosY = 0;
}

void CItem_Viewport::checkParentInvisibility(){
	isParentInvisible = false;
}
