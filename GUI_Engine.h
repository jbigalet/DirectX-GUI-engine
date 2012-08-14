#pragma once

#include <d3d9.h>
#include <string>
#include <map>
#include <vector>
#include "CItem.h"
#include "CItem_Text.h"
#include "CItem_Viewport.h"
#include "CItem_Image.h"
#include "CItem_ProgressBar.h"

#include "../VLC_Overlay/utility.h"

struct Vertex {
	float x, y, w, h;
	D3DCOLOR color;
};

struct CDrag{
	bool isDragging;
	bool isClickedOutside;
	int x;
	int y;
};

class CGUI_Engine {
public:
	LPDIRECT3DDEVICE9 pDevice;
	HWND hwWindow;
	vector<PItem> vpItems;
	map<string,PItem> mpItems;
	int posX;
	int posY;
	CDrag cDrag;

public:
	void initialize(LPDIRECT3DDEVICE9);
	void addItem(PItem);
	PItem getItem(string name) { return mpItems[name]; };
	vector<PItem> getClickedItems(tagPOINT);
	void clickHandle();
	void update();
	void draw();
	void release();
	void completeProcess();

	Vertex createVertex(int x, int y, int w, int h, D3DCOLOR color);
	void drawTriangleStrip( int, Vertex* );
	void drawShaderedRectangle(int x, int y, int w, int h, D3DCOLOR color1, D3DCOLOR color2, D3DCOLOR color3, D3DCOLOR color4);
	void drawHorizontalShaderedRectangle(int x, int y, int w, int h, D3DCOLOR color1, D3DCOLOR color2);
	void drawRectangle(int x, int y, int w, int h, D3DCOLOR color);
	void drawRoundedRectangle(int x, int y, int w, int h, int wedge, D3DCOLOR color);
	void drawCornerCircle(int x, int y, int wedge, float angle, D3DCOLOR color);
};

extern CGUI_Engine m_engine;