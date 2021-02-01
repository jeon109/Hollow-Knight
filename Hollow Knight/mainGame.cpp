#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## 초기화 ## init()
//=============================================================
HRESULT mainGame::init()
{
	gameNode::init();
	
	/*앞으로 메인게임은 각각의 씬들만 관리를 한다*/
	/*이곳에서 각각의 씬들을 추가하고 현재씬을 설정한다*/
	_imageLoader = new imageLoader;
	_imageLoader->init();
	/*씬추가*/
	SCENEMANAGER->addScene("시작화면", new startScene);
	SCENEMANAGER->addScene("게임화면", new gameScene);

	/*현재씬*/
	SCENEMANAGER->loadScene("시작화면");

	return S_OK;
}

//=============================================================
//	## 해제 ## release()
//=============================================================
void mainGame::release()
{
	gameNode::release();
}

//=============================================================
//	## 업데이트 ## update()
//=============================================================
void mainGame::update()
{
	gameNode::update();
	
	//씬매니져 업데이트
	SCENEMANAGER->update();
}

//=============================================================
//	## 렌더 ## render()
//=============================================================
void mainGame::render()
{
	//흰색 빈 비트맵 (이것은 렌더에 그냥 두기)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
//=============================================================
	//씬매니져 렌더
	SCENEMANAGER->render();
	
//=============================================================
	//백버퍼의 내용을 화면DC에 그린다 (이것도 렌더에 그냥 두기)
	this->getBackBuffer()->render(getHDC());
}
