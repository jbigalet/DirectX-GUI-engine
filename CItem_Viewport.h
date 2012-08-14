#pragma once

#include "GUI_Engine.h"
#include "CItem.h"

class CItem_Viewport : public CItem {
public:
	void updateDim();
	void updatePos();
	void checkParentInvisibility();
	CItem_Viewport();
};

