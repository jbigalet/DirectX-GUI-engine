#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <string>

class CItem;
typedef CItem *PItem;

using namespace std;

enum ERelativePositionX {
	LEFTEXTERIOR,
	LEFTINTERIOR,
	MIDDLEX,
	RIGHTINTERIOR,
	RIGHTEXTERIOR
};


struct CPositionX {
	PItem rItem;
	ERelativePositionX rPos;
	int pos;
};


enum ERelativePositionY {
	TOPEXTERIOR,
	TOPINTERIOR,
	MIDDLEY,
	BOTTOMINTERIOR,
	BOTTOMEXTERIOR
};

struct CPositionY {
	PItem rItem;
	ERelativePositionY rPos;
	int pos;
};


enum EItemType{
	DUMMY,
	TEXT,
	IMAGE,
	PROGRESSBAR
};

class CItem {
public:
	string name;
	bool isDraggable;
	bool isClickable;
	int dimX;
	int dimY;
	CPositionX posX;
	CPositionY posY;
	EItemType type;

	bool isInvisible;
	bool isParentInvisible;

	int iPosX;
	int iPosY;

	void createPosAndDim(int,int,string,ERelativePositionX,int,string,ERelativePositionY,int);

	void update();
	virtual void onUpdate() {};
	virtual void updateDim() {};
	virtual void updatePos();
	void updatePosX();
	void updatePosY();
	virtual void checkParentInvisibility();

	virtual void draw() {};
	virtual void onClick( tagPOINT ) {};
	virtual void release() {};

	CItem() : type(DUMMY), isInvisible(false), isParentInvisible(false) {};
	CItem(string name) : name(name), type(DUMMY), isInvisible(false), isParentInvisible(false) {};
	CItem(string name, bool isDraggable, bool isClickable, int dimX, int dimY,
		string nItemX, ERelativePositionX rPosX, int posX,
		string nItemY, ERelativePositionY rPosY, int posY) :
			name(name), type(DUMMY), isDraggable(isDraggable), isClickable(isClickable), isInvisible(false), isParentInvisible(false)
			{ createPosAndDim(dimX, dimY, nItemX, rPosX, posX, nItemY, rPosY, posY); };

};
