#pragma once
#include "gameNode.h"
/*������ ���ΰ����� ������ ���鸸 ������ �Ѵ�*/
/*������ ������ϸ� �̰��� �߰��Ѵ�*/
#include "startScene.h"
#include "gameScene.h"
#include "imageLoader.h"
class mainGame : public gameNode
{
public:
	imageLoader* _imageLoader;

	HRESULT init();
	void release();
	void update();
	void render();
};