#include "stdafx.h"
#include "gameScene.h"

HRESULT gameScene::init()
{
	_player = new player;
	_player->init();
	_boss = new boss;
	_boss->init();

	_boss->setPlayer(_player);
	_player->setBossInfo(_boss);

	CAMERAMANAGER->init(2500, 1060, WINSIZEX, WINSIZEY);
	return S_OK;
}

void gameScene::release()
{
	_player->release();
	SAFE_DELETE(_player);
	_boss->release();
	SAFE_DELETE(_boss);
}

void gameScene::update()
{
	_player->update();
	_x = _player->getX();
	_y = _player->getY();
	CAMERAMANAGER->cameraMove(_x, _y);

	_boss->update();
}

void gameScene::render()
{
	CAMERAMANAGER->render(getMemDC());
	IMAGEMANAGER->render("background", CAMERAMANAGER->getMemDC(), 0, 0);
	_boss->render();
	_player->render();


}
