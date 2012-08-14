#include "GUI_Engine.h"
#include "../VLC_Overlay/utility.h"
#include <vector>

CGUI_Engine m_engine;

void CGUI_Engine::initialize(LPDIRECT3DDEVICE9 pDevice){
		// Create pDevice
	this->pDevice = pDevice;

		// Create hwWindow
	D3DDEVICE_CREATION_PARAMETERS pPar;
	this->pDevice->GetCreationParameters( &pPar );
	this->hwWindow = pPar.hFocusWindow;

		// Create Viewport & Main base items
	addItem(new CItem_Viewport());
	addItem(new CItem("Main", false, false, 1000, 1000, "Viewport", LEFTINTERIOR, 100, "Viewport", TOPINTERIOR, 100));
}

void CGUI_Engine::addItem(PItem item){
	vpItems.push_back(item);
	mpItems[item->name] = item;
}

void CGUI_Engine::clickHandle(){
	if( !GetAsyncKeyState(VK_LBUTTON) /*|| hwWindow != GetFocus()*/ ){
		cDrag.isDragging = false;
		cDrag.isClickedOutside = false;
		return;
	}
	
	if( cDrag.isClickedOutside) return;

	tagPOINT CurPos;
	GetCursorPos(&CurPos);
	ScreenToClient(hwWindow, &CurPos);

	if( cDrag.isDragging ){
		getItem("Main")->posX.pos = CurPos.x - cDrag.x;
		getItem("Main")->posY.pos = CurPos.y - cDrag.y;
		return;
	}

	vector<PItem> clickedItems = getClickedItems( CurPos );
	bool isSomethingDragable = false;

	for( vector<PItem>::iterator it = clickedItems.begin() ; it != clickedItems.end() ; it++ ){
		if( (*it)->isClickable == true ){
			cDrag.isClickedOutside = true;
			(*it)->onClick( CurPos );
		}
		if( (*it)->isDraggable == true )
			isSomethingDragable = true;
	}

	if( cDrag.isClickedOutside ) return;

	if( !isSomethingDragable ){
		cDrag.isClickedOutside = true;
		return ;
	}

	cDrag.isDragging = true;
	cDrag.x = CurPos.x - getItem("Main")->iPosX;
	cDrag.y = CurPos.y - getItem("Main")->iPosY;
}

vector<PItem> CGUI_Engine::getClickedItems( tagPOINT curPos ){
	vector<PItem> res;
	for( vector<PItem>::iterator it = vpItems.begin() ; it != vpItems.end() ; it++){
		if( !(*it)->isInvisible && !(*it)->isParentInvisible )
			if(    curPos.x >= (*it)->iPosX
				&& curPos.x <= (*it)->iPosX + (*it)->dimX
				&& curPos.y >= (*it)->iPosY
				&& curPos.y <= (*it)->iPosY + (*it)->dimY )

				res.push_back( (*it) );
	}
	return res;
}


void CGUI_Engine::drawTriangleStrip( int n, Vertex* v ){
	pDevice->SetTexture( 0, NULL );
	pDevice->SetPixelShader( NULL );
	pDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	pDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	pDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	pDevice->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 );
	
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);


	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, n, v, sizeof(Vertex));
}


void CGUI_Engine::drawShaderedRectangle(int x, int y, int w, int h, D3DCOLOR color1, D3DCOLOR color2, D3DCOLOR color3, D3DCOLOR color4){
	Vertex rect[4] = {
		{ x, y+h, 0.0f, 1.0f, color1 },
		{ x, y, 0.0f, 1.0f, color2 },
		{ x+w, y+h, 0.0f, 1.0f, color3 },
		{ x+w, y, 0.0f, 1.0f, color4 }
	};

	drawTriangleStrip( 2, rect );
}


void CGUI_Engine::drawHorizontalShaderedRectangle(int x, int y, int w, int h, D3DCOLOR color1, D3DCOLOR color2){
	drawShaderedRectangle(x, y, w, h, color2, color1, color2, color1);
}


void CGUI_Engine::drawRectangle(int x, int y, int w, int h, D3DCOLOR color){
	drawShaderedRectangle(x, y, w, h, color, color, color, color);
}


Vertex CGUI_Engine::createVertex(int x, int y, int w, int h, D3DCOLOR color){
	Vertex v = { x, y, w, h, color };
	return v;
}

#define roundPrecision	150
void CGUI_Engine::drawRoundedRectangle(int x, int y, int w, int h, int wedge, D3DCOLOR color){
		// Draw central rectangle
	drawRectangle(x + wedge, y, w - 2*wedge, h, color);
		// Draw right & left rectangles
	drawRectangle(x, y + wedge, wedge, h - 2*wedge, color);
	drawRectangle(x+w - wedge, y + wedge, wedge, h - 2*wedge, color);

		// Draw the rounded corners
	float piD2 = 3.1215f / 2.0f;
	drawCornerCircle( x+w-wedge,	y+h-wedge,	wedge,	0.0f,	color);
	drawCornerCircle( x+w-wedge,	y+wedge,	wedge,	piD2,	color);
	drawCornerCircle( x+wedge,		y+wedge,	wedge,	2*piD2,	color);
	drawCornerCircle( x+wedge,		y+h-wedge,	wedge,	3*piD2,	color);
}

void CGUI_Engine::drawCornerCircle(int xPos, int yPos, int wedge, float angle, D3DCOLOR color){
	float angleIncr = 3.0f * 3.1415f / (2*(float)roundPrecision);
	float x1 = xPos;
	float y1 = yPos;
	Vertex cornerRT[roundPrecision+3];
	for(int i=0 ; i<=roundPrecision ; i+=3){
		float x2 = xPos + wedge * sin(angle);
		float y2 = yPos + wedge * cos(angle);
		cornerRT[i] = createVertex( xPos, yPos, 0.0f, 1.0f, color);
		cornerRT[i+1] = createVertex( x1, y1, 0.0f, 1.0f, color);
		cornerRT[i+2] = createVertex( x2, y2, 0.0f, 1.0f, color);
		y1 = y2;
		x1 = x2;
		angle += angleIncr;
	}
	drawTriangleStrip( roundPrecision+1, cornerRT );
}


void CGUI_Engine::update(){
	for( std::vector<PItem>::iterator it = vpItems.begin() ; it != vpItems.end() ; it++)
		(*it)->update();
}

void CGUI_Engine::draw(){
	for( std::vector<PItem>::iterator it = vpItems.begin() ; it != vpItems.end() ; it++)
		if( !(*it)->isInvisible && !(*it)->isParentInvisible )
			(*it)->draw();
}

void CGUI_Engine::release(){
	for( std::vector<PItem>::iterator it = vpItems.begin() ; it != vpItems.end() ; it++)
		if( !(*it)->isInvisible && !(*it)->isParentInvisible )
			(*it)->release();
}

void CGUI_Engine::completeProcess(){
	update();
	clickHandle();
	draw();
	release();
}