#include "stdafx.h"
#include "imageLoader.h"


imageLoader::imageLoader()
{
}

imageLoader::~imageLoader()
{
}

HRESULT imageLoader::init()
{

	IMAGEMANAGER->addImage("background", "Images/background.bmp", 2500, 1060);


	IMAGEMANAGER->addImage("hp_bar", "Images/hp_bar.bmp", 260, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hp", "Images/hp_f.bmp", 78, 57, 2, 1, true, RGB(255, 0, 255));


	IMAGEMANAGER->addImage("skill_bar", "Images/skill_bar.bmp", 169, 41, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("skill_gauge","Images/skill_gauge.bmp",12,42,true,RGB(255, 0, 255));
	IMAGEMANAGER->addImage("player_damage_left", "Images/player_damage_left.bmp", 130, 172, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("player_damage_right", "Images/player_damage_right.bmp", 130, 172, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("player_damage", "Images/player_damage.bmp", 7384, 625, 4, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("player_down", "Images/player_down.bmp", 248, 400,1,2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sphear", "Images/sphear.bmp", 731, 38,3,2, true, RGB(255, 0, 255));


	IMAGEMANAGER->addFrameImage("player_run", "Images/player_run.bmp", 1152, 400, 8, 2, true, RGB(255, 0, 255));//336
	IMAGEMANAGER->addFrameImage("player_jump", "Images/player_jump.bmp", 1488, 410, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("player_idle","Images/player_idle.bmp",1006,400,6,2,true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("player_atk", "Images/player_atk.bmp", 2680, 682, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("player_skill_2", "Images/player_skill_2.bmp", 2254, 384, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("player_skill_2_up", "Images/player_skill_2_up.bmp", 834, 400, 6, 2, true, RGB(255, 0, 255));



	IMAGEMANAGER->addFrameImage("player_skill_1", "Images/player_skill_1.bmp", 1162, 344, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("player_skill_1_0", "Images/player_skill_1_0.bmp", 3436, 404, 9, 1, true, RGB(255, 0, 255));



	IMAGEMANAGER->addFrameImage("boss_idle", "Images/Boss_idle.bmp", 3123, 800, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boss_is_jump","Images/Boss_is_jump.bmp",2434,688,4,2,true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boss_jump_start","images/Boss_jump_start.bmp",1850,800,3,2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boss_atk_1", "Images/Boss_atk_1.bmp", 2923, 800, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boss_atk_2", "Images/Boss_atk_2.bmp", 2126, 1200, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boss_atk_jump", "Images/Boss_atk_jump.bmp", 2862, 858, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boss_atk_jump_2", "Images/Boss_atk_jump_2.bmp", 1680, 1226, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boss_Damage", "Images/Boss_Damage.bmp", 617, 800, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boss_down_1", "Images/Boss_down_1.bmp", 3069, 1040, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boss_down_2", "Images/Boss_down_2.bmp", 1686, 956, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boss_down_3", "Images/Boss_down_3.bmp", 1593, 932, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boss_down_4", "Images/Boss_down_4.bmp", 390, 922, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boss_down_head", "Images/Boss_down_head.bmp", 370, 288, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boss_down_body", "Images/Boss_down_body.bmp", 1071, 926, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boss_head_down", "Images/Boss_head_down.bmp", 1104, 396, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("start_s", "Images/start_s.bmp", 13440, 1060, 6, 1);
	IMAGEMANAGER->addFrameImage("atk", "Images/atk.bmp", 2655, 310, 8, 1);


	return S_OK;
}
