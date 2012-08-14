#include "CItem_Image.h"
#include "GUI_Engine.h"

CItem_Image::CItem_Image(string name, string fImage, bool isDraggable, bool isClickable,
			string nItemX, ERelativePositionX rPosX, int posX,
			string nItemY, ERelativePositionY rPosY, int posY) :
		CItem(name, isDraggable, isClickable, 0, 0, nItemX, rPosX, posX, nItemY, rPosY, posY), fImage(fImage)
{
	this->type = IMAGE;
}

void CItem_Image::updateDim(){
	D3DXIMAGE_INFO info;
	D3DXGetImageInfoFromFile(fImage.c_str(), &info);
	dimX = info.Width;
	dimY = info.Height;
}

void CItem_Image::draw(){
	D3DXCreateSprite( m_engine.pDevice, &pSprite);
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	if( fImage != "" ){
		D3DXCreateTextureFromFileEx( m_engine.pDevice, fImage.c_str(),
			D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_FROM_FILE, 0, 
			D3DFMT_FROM_FILE,
			D3DPOOL_MANAGED, D3DX_FILTER_NONE,  D3DX_FILTER_NONE,
			0, NULL, NULL,
			&pTexture
			);

		pSprite->Draw(pTexture, NULL, NULL, &D3DXVECTOR3( (float)iPosX, (float)iPosY, 0.0f ), 0xFFFFFFFF);
	}
	
	pSprite->End();
}

void CItem_Image::release(){
	if( pTexture != NULL) pTexture->Release();
	pSprite->Release();
}