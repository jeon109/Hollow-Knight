#include "stdafx.h"
#include "startScene.h"


HRESULT startScene::init()
{
	//렉트 위치 초기화
	_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 440, 200, 50);
	count = 0;
	index = 0;
	return S_OK;
}

void startScene::release()
{
}

void startScene::update()
{
	if (INPUT->GetKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_rc, _ptMouse))
		{
			SCENEMANAGER->loadScene("게임화면");
		}
	}
	animation();
}

void startScene::render()
{
	IMAGEMANAGER->frameRender("start_s", getMemDC(), 0, 0);

	//Rectangle(getMemDC(), _rc);
	/*TextOut(getMemDC(), _rc.left + 80, _rc.top + 50, "START", strlen("START"));*/
}

void startScene::animation()
{

	count++;

	if (count > 10) {
		count = 0;

		index++;
		if (index < 7) {
			index = 0;
		}
		cout << "a" << endl;
		IMAGEMANAGER->findImage("start_s")->setFrameX(index);
	}
}
