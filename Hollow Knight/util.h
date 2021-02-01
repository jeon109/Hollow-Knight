#pragma once
//=============================================================
//	## namespace ## MY_UTIL
//=============================================================

#define PI 3.1415926f
#define PI2 (PI * 2)
#define RADIAN 3.1415926f/180.0f

//���߿� �̹��� ȸ���� ����� ��
#define PI_2 (PI / 2) //90��
#define PI_4 (PI / 4) //45��
#define PI_8 (PI / 8) //22.5��

namespace _UTIL
{
	//���� ������ �Ÿ�
	float getDistance(float startX, float startY, float endX, float endY);
	//���� ������ ����
	float getAngle(float startX, float startY, float endX, float endY);
};

