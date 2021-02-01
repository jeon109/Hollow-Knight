#pragma once
#include "gameNode.h"
#include "player.h"
#include "boss.h"

class gameScene : public gameNode
{
private:
	float _x, _y;
	player* _player;
	boss* _boss;
	
public:
	HRESULT init();
	void release();
	void update();
	void render();

};

