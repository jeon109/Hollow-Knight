#pragma once
#include "gameNode.h"

class startScene : public gameNode
{
private:
	RECT _rc;

	int count;
	int index;

public:
	HRESULT init();
	void release();
	void update();
	void render();


	void animation();
};

