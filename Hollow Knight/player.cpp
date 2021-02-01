#include "stdafx.h"
#include "player.h"
#include "boss.h"
//초기화
HRESULT player::init()
{

	speedX = 10.0f;							//X 스피드
	speedY = 4.5f;							//Y 스피드
	posX = WINSIZEX / 2;					//플레이어 좌표
	posY = WINSIZEY / 2+280;				//플레이어 좌표
	jump_power = 0.8f;						//점프 올락는 속도
	gravity_accumulate = 0;					//중력 누적값
	gravity = 0.4f;							//중력
	_count = 0;								//움직임 카운트
	_index = 0;								//움직음 프레임 
	_atk_count = 0;							//공격모션 카운
	_atk_index = 0;							//공격모션 프레임
	_state = IDLE;							//플레이어 상태
	_p_skill = Basic_Attack;				//스킬종류
	_rc = RectMake(posX,posY,150,200);		//플레이어 랙트
	_skill_count = 0;						
	gravity1 = 0;
	timeHp = 0;
	isHp = false;
	iscoillision = false;					//보스봅 충돌
	isJump = true;							//점프상태 확인
	Right_and_left = false;					//좌우 움직임
	_max_jump = false;						//점프 최대 위치 도달
	isJavelin = false;						//창 던짐
	isSphear_stert = false;
	isGauge = false;
	inuincibility = false;

	imageaipcount = 0;
	imageaip = false;
	motion = false;
	m_count=0;
	m_index=0;

	inuincibility_count = 0;
	_rc_sphear = RectMake(posX, posY,243, 19);// 창 랙트
	_rc_collision = RectMake(posX+30, posY+60, 100, 130);
	//hp
	for (int i = 0; i < 5; i++) {
		image* im = new image;
		im = IMAGEMANAGER->findImage("hp");
		HpImage* _push_hp = new HpImage;
		_push_hp->hp = im;
		_push_hp->frameX = 0;
		_push_hp->frameY = 0;
		my_hp.push_back(_push_hp);
	}										//플레이어 hp초기화

	return S_OK;
}
//삭제
void player::release()
{
}
//업데이트
void player::update()
{
	player_state();
	animation();
	hp_management();
	sphear_move();
	_rc_collision = RectMake(posX+30, posY+60, 100, 130);
	collision();
	boss_body_collision();
	if (iscoillision) {

		boss_collision();
	}

	if (_state == IDLE && _state == DAMAGE) {
		_atkRc.clear();
	}

	if (inuincibility) {

		inuincibility_count++;
		if (inuincibility_count > 150) {
			inuincibility_count = 0;
			inuincibility = false;
		}
	}
	if (motion) {
		morion_animation();
	}
}
//랜더
void player::render()
{
	
	if (Right_and_left) {
		for (int i = 0; i < _vsphear.size(); i++) {
			IMAGEMANAGER->findImage("sphear")->setFrameY(0);
			IMAGEMANAGER->frameRender("sphear", CAMERAMANAGER->getMemDC(), _vsphear[i]->x, _vsphear[i]->y);
		}
	}
	else {
		for (int i = 0; i < _vsphear.size(); i++) {
			IMAGEMANAGER->findImage("sphear")->setFrameY(1);
			IMAGEMANAGER->frameRender("sphear", CAMERAMANAGER->getMemDC(), _vsphear[i]->x, _vsphear[i]->y);
		}
	}
	if (!inuincibility) {


		switch (_state)
		{
		case IDLE:
			IMAGEMANAGER->frameRender("player_idle", CAMERAMANAGER->getMemDC(), _rc.left, _rc.top);
			break;
		case DOWN:
			IMAGEMANAGER->frameRender("player_down", CAMERAMANAGER->getMemDC(), _rc.left, _rc.top);
			break;
		case JUMP:
			IMAGEMANAGER->frameRender("player_jump", CAMERAMANAGER->getMemDC(), _rc.left, _rc.top);
			break;
		case MOVE:
			IMAGEMANAGER->frameRender("player_run", CAMERAMANAGER->getMemDC(), _rc.left, _rc.top);
			break;
		case ATK:
			switch (_p_skill)
			{
			case Basic_Attack:
				if (Right_and_left) {
					IMAGEMANAGER->frameRender("player_atk", CAMERAMANAGER->getMemDC(), _rc.left - 140, _rc.top - 140);
				}
				else {
					IMAGEMANAGER->frameRender("player_atk", CAMERAMANAGER->getMemDC(), _rc.left - 220, _rc.top - 140);

				}
				break;
			case Air_attack:
				IMAGEMANAGER->frameRender("player_skill_1", CAMERAMANAGER->getMemDC(), _rc.left, _rc.top);
				IMAGEMANAGER->frameRender("player_skill_1_0", CAMERAMANAGER->getMemDC(), _rc.left - 140, _rc.top - 140);

				break;

			}
			break;
		case SKILL:
			switch (_p_skill)
			{
			case Javelin_throw:
				if (!isJavelin) {
					if (Right_and_left) {
						IMAGEMANAGER->frameRender("player_skill_2", CAMERAMANAGER->getMemDC(), _rc.left, _rc.top);
					}
					else {
						IMAGEMANAGER->frameRender("player_skill_2", CAMERAMANAGER->getMemDC(), _rc.left - 50, _rc.top);
					}
				}
				else {
					IMAGEMANAGER->frameRender("player_skill_2_up", CAMERAMANAGER->getMemDC(), _rc.left, _rc.top);
				}
				break;
			}
			break;
		case DAMAGE:
			if (Right_and_left) {
				IMAGEMANAGER->render("player_damage_right", CAMERAMANAGER->getMemDC(), _rc.left - 50, _rc.top);

			}
			else {
				IMAGEMANAGER->render("player_damage_left", CAMERAMANAGER->getMemDC(), _rc.left, _rc.top);
			}
			break;

		}
	}
	else {

		if (imageaip) {
			imageaip = false;
		}
		else {
			imageaip = true;
			switch (_state)
			{
			case IDLE:
				IMAGEMANAGER->frameRender("player_idle", CAMERAMANAGER->getMemDC(), _rc.left, _rc.top);
				break;
			case DOWN:
				IMAGEMANAGER->frameRender("player_down", CAMERAMANAGER->getMemDC(), _rc.left, _rc.top);
				break;
			case JUMP:
				IMAGEMANAGER->frameRender("player_jump", CAMERAMANAGER->getMemDC(), _rc.left, _rc.top);
				break;
			case MOVE:
				IMAGEMANAGER->frameRender("player_run", CAMERAMANAGER->getMemDC(), _rc.left, _rc.top);
				break;
			case ATK:
				switch (_p_skill)
				{
				case Basic_Attack:
					if (Right_and_left) {
						IMAGEMANAGER->frameRender("player_atk", CAMERAMANAGER->getMemDC(), _rc.left - 140, _rc.top - 140);
					}
					else {
						IMAGEMANAGER->frameRender("player_atk", CAMERAMANAGER->getMemDC(), _rc.left - 220, _rc.top - 140);

					}
					break;
				case Air_attack:
					IMAGEMANAGER->frameRender("player_skill_1", CAMERAMANAGER->getMemDC(), _rc.left, _rc.top);
					IMAGEMANAGER->frameRender("player_skill_1_0", CAMERAMANAGER->getMemDC(), _rc.left - 140, _rc.top - 140);

					break;

				}
				break;
			case SKILL:
				switch (_p_skill)
				{
				case Javelin_throw:
					if (!isJavelin) {
						if (Right_and_left) {
							IMAGEMANAGER->frameRender("player_skill_2", CAMERAMANAGER->getMemDC(), _rc.left, _rc.top);
						}
						else {
							IMAGEMANAGER->frameRender("player_skill_2", CAMERAMANAGER->getMemDC(), _rc.left - 50, _rc.top);
						}
					}
					else {
						IMAGEMANAGER->frameRender("player_skill_2_up", CAMERAMANAGER->getMemDC(), _rc.left, _rc.top);
					}
					break;
				}
				break;
			case DAMAGE:
				if (Right_and_left) {
					IMAGEMANAGER->render("player_damage_right", CAMERAMANAGER->getMemDC(), _rc.left - 50, _rc.top);

				}
				else {
					IMAGEMANAGER->render("player_damage_left", CAMERAMANAGER->getMemDC(), _rc.left, _rc.top);
				}
				break;
			}
		}
		
	}

	IMAGEMANAGER->render("hp_bar", getMemDC(), 40, 30);
	for (int i = 0; i < my_hp.size(); i++) {
		my_hp[i]->hp->frameRender(getMemDC(), 145 + i * 50, 30, my_hp[i]->frameX, my_hp[i]->frameY);

	}

	IMAGEMANAGER->render("skill_bar", getMemDC(), 50, 120);
	for (int i = 0; i < skill_gauge.size(); i++) {
		skill_gauge[i]->Gauge->render(getMemDC(), skill_gauge[i]->posX, skill_gauge[i]->posY);
	}
	
	//Rectangle(CAMERAMANAGER->getMemDC(), _rc_collision);
	//
	//for (int i = 0; i < _atkRc.size(); i++) {
	//	Rectangle(CAMERAMANAGER->getMemDC(), _atkRc[i]);
	//}
	for (int i = 0; i < atkMotion.size(); i++) {
		IMAGEMANAGER->frameRender("atk", CAMERAMANAGER->getMemDC(), atkMotion[i].left-150, atkMotion[i].top-150);
	}
}


//플레어어 움직임
void player::player_Move_up()
{
	if (!_max_jump) {

		if (INPUT->GetKey(VK_SPACE)) {
			isJump = true;
			_state = JUMP;
			if (speedY < JUMPMAX) {
				posY -= speedY;
				speedY += jump_power;
				gravity_accumulate = 4;
			}
			else {
				_max_jump = true;
			}
		}

	}

	if (INPUT->GetKeyUp(VK_SPACE)) {
		_max_jump = true;
	}
}
void player::player_Move_left()
{
	if (INPUT->GetKey(VK_LEFT)&& _rc.left > -20) {
		posX -= speedX;
		Right_and_left = true;
		if(!isJump){
			_state = MOVE;
		}
		
	}
	if (INPUT->GetKeyUp(VK_LEFT)) {
		
		if (!isJump) {
			_state = IDLE;
		}
		
	}
	_rc = RectMake(posX, posY, 150, 200);
}
void player::player_Move_right()
{
	if (INPUT->GetKey(VK_RIGHT)&& _rc.right< 2520) {
		posX += speedX;
		Right_and_left = false;
		if (!isJump) {
			_state = MOVE;
		}
	}
	if (INPUT->GetKeyUp(VK_RIGHT)) {

		if (!isJump) {
			_state = IDLE;
		}
		
	}
	_rc = RectMake(posX, posY, 150, 200);
}
void player::player_Move_down()
{
	if (INPUT->GetKey(VK_DOWN)) {
		if (!isJump) {
			_state = DOWN;
		}
	}

	if (INPUT->GetKeyUp(VK_DOWN)) {
		if (!isJump) {
			_state = IDLE;
		}

	}

}
//플레이 공격
void player::player_atk()
{
	if (INPUT->GetKeyDown('S')) {
		if (Right_and_left) {
			_atk_index = -1;
		}
		else {
			_atk_index = 5;
		}
		_p_skill = Basic_Attack;
		_state = ATK;
	}
	if (_state == JUMP && _max_jump) {
		
		if (INPUT->GetKeyDown('D')) {
			if (skill_gauge.size() >= 5) {
				_skill_count = 0;
				if (Right_and_left) {
					_atk_index = -1;
				}
				else {
					_atk_index = 5;
				}
				_p_skill = Air_attack;
				_state = ATK;
				for (int i = 0; i < 5; i++) {
					skill_gauge.erase(skill_gauge.begin() + skill_gauge.size() - 1);
				}
			}
		}
			
		
	}
}
void player::player_skill()
{
	if (skill_gauge.size() >= 2) {

		if (INPUT->GetKeyDown('X')) {
			_count = 0;
			_index = 0;
			if (Right_and_left) {
				_count = 0;
				_index = 0;
			}
			else {
				_count = 0;
				_index = 8;

			}
			isSphear_stert = true;

		}
		

	}
	if (isSphear_stert) {
		if (INPUT->GetKey('X')) {
			_state = SKILL;
			_p_skill = Javelin_throw;
		}

		if (INPUT->GetKeyUp('X')) {
			isSphear_stert = false;
			if (Right_and_left) {
				if (_index < 8) {
					_state = IDLE;
					_p_skill = Basic_Attack;
				}
				else {
					if (skill_gauge.size() >= 2) {
						_state = SKILL;
						_p_skill = Javelin_throw;
						_count = 0;
						_index = 0;
						player_sphear_move(180);
						isJavelin = true;
						for (int i = 0; i < 2; i++) {
							skill_gauge.erase(skill_gauge.begin() + skill_gauge.size() - 1);
						}
					}
				}
			}
			else {
				if (_index > 0) {
					_state = IDLE;
					_p_skill = Basic_Attack;
				}
				else {
					if (skill_gauge.size() >= 2) {
						_state = SKILL;
						_p_skill = Javelin_throw;
						_count = 0;
						_index = 5;
						isJavelin = true;
						player_sphear_move(0);
						for (int i = 0; i < 2; i++) {
							skill_gauge.erase(skill_gauge.begin() + skill_gauge.size() - 1);
						}
					}
				}
			}

		}
	}
}

//플래이어 상태별 행동
void player::player_state()
{
	switch (_state)
	{
	case IDLE:
		player_Move_right();
		player_Move_left();
		player_Move_up();
		player_Move_down();
		player_atk();
		player_skill();
		break;
	case DOWN:
		player_Move_up();
		player_Move_down();
		player_atk();
		player_skill();
		break;
	case JUMP:
		player_Move_right();
		player_Move_left();
		player_Move_up();
		player_atk();
		
		break;
	case MOVE:
		player_Move_right();
		player_Move_left();
		player_Move_up();
		player_Move_down();
		player_atk();
		player_skill();
		break;
	case ATK:
		
		break;
	case SKILL:
		player_skill();
		break;
	case DAMAGE:
		break;
	}
	player_gravity();
}
//플레이어 중력
void player::player_gravity()
{
	if(_max_jump&& _rc.bottom <WINSIZEY-60 && _p_skill != Air_attack){
		if (gravity_accumulate < 15) {
			gravity_accumulate -= gravity;
		}
		_state == JUMP;
		posY -= gravity_accumulate;
		
		_rc = RectMake(posX, posY, 150, 200);
		
	}
	else if(_rc.bottom > WINSIZEY -62) {
		iscoillision = false;
		_max_jump = false;
		isHp = false;
		speedY = 8.5f;
		if (_state == JUMP || _state == DAMAGE) {
			_state = IDLE;
		}
		isJump = false;
	}
}

//중력 관련


//프레임 애니메이션
void player::animation()
{

	switch (_state)
	{
	case IDLE:
		_count++;
		if (Right_and_left) {
			IMAGEMANAGER->findImage("player_idle")->setFrameY(0);
			if (_count > 6) {
				_index++;
				_count = 0;
				if (_index > 6) {
					_index = 0;
				}
				IMAGEMANAGER->findImage("player_idle")->setFrameX(_index);
			}
		}
		else {
			IMAGEMANAGER->findImage("player_idle")->setFrameY(1);
			if (_count > 6) {
				_index--;
				_count = 0;
				if (_index < 0) {
					_index = 5;
				}
				IMAGEMANAGER->findImage("player_idle")->setFrameX(_index);
			}
			
		}
		break;
	case DOWN:
		if (Right_and_left) {
			IMAGEMANAGER->findImage("player_down")->setFrameY(0);
		}
		else {
			IMAGEMANAGER->findImage("player_down")->setFrameY(1);
		}
		break;
	case JUMP:
		_count++;
		if (Right_and_left) {
			IMAGEMANAGER->findImage("player_jump")->setFrameY(0);
			if (_count > 6) {
				_count = 0;
				if (!_max_jump) {
					_index++;
					if (_index > 2) {
						_index = 2;
					}
				}
				else {
					_index++;
					if (_index > 10) {
						_index = 10;
					}
				}
				IMAGEMANAGER->findImage("player_jump")->setFrameX(_index);
			}
		}
		else {
			IMAGEMANAGER->findImage("player_jump")->setFrameY(1);
			if (_count > 6) {
				_count = 0;
				if (!_max_jump) {
					_index--;
					if (_index <6) {
						_index = 6;
					}
				}
				else {
					_index--;
					if (_index < 0) {
						_index = 0;
					}
				}
				IMAGEMANAGER->findImage("player_jump")->setFrameX(_index);
			}

		}
		break;
	case MOVE:
		_count++;
		if (Right_and_left) {
			IMAGEMANAGER->findImage("player_run")->setFrameY(0);
			if (_count > 6) {
				_index++;
				_count = 0;
				if (_index > 8) {
					_index = 0;
				}
				IMAGEMANAGER->findImage("player_run")->setFrameX(_index);
			}
		}
		else {
			IMAGEMANAGER->findImage("player_run")->setFrameY(1);
			if (_count > 6) {
				_index--;
				_count = 0;
				if (_index < 0) {
					_index = 7;
				}
				IMAGEMANAGER->findImage("player_run")->setFrameX(_index);
			}

		}
		break;
	case ATK:
		switch (_p_skill)
		{
		case Basic_Attack:
			if (Right_and_left) {
				_atkRc.push_back(RectMake(posX-125, posY, 100, 100));
				_atkRc.push_back(RectMake(posX-50 , posY -50, 150, 100));
				_atk_count++;
				IMAGEMANAGER->findImage("player_atk")->setFrameY(0);
				if (_atk_count > 2) {
					_atk_index++;
					_atk_count = 0;
					if (_atk_index > 5) {
						_atk_index = 0;
						_atkRc.clear();
						_state = IDLE;
						isGauge = false;
						break;
					}
					IMAGEMANAGER->findImage("player_atk")->setFrameX(_atk_index);
				}
			}
			else {
				_atk_count++;
				_atkRc.push_back(RectMake(posX + 200, posY + 30, 80, 100));
				_atkRc.push_back(RectMake(posX + 140, posY - 50, 150, 100));
				IMAGEMANAGER->findImage("player_atk")->setFrameY(1);
				if (_atk_count > 2) {
					_atk_index--;
					_atk_count = 0;
					if (_atk_index < 0) {
						_atk_index = 5;
						_atkRc.clear();
						_state = IDLE;
						isGauge = false;
						break;
					}
					IMAGEMANAGER->findImage("player_atk")->setFrameX(_atk_index);
				}

			}
			break;
		case Air_attack:
			_skill_count++;
			if (Right_and_left) {
				_atkRc.push_back(RectMakeCenter(posX+80, posY+80, 300, 300));
				_atk_count++;
				_count++;
				IMAGEMANAGER->findImage("player_skill_1")->setFrameY(0);
				if (_atk_count > 5) {
					_atk_index++;
					_atk_count = 0;
				
					if (_atk_index > 10) {
						_atk_index = 7;
						/*_state = IDLE;
						break;*/
					}
				
					IMAGEMANAGER->findImage("player_skill_1")->setFrameX(_atk_index);
					
				}
				if (_count > 2) {
					_count = 0;
					_index++;
					if (_index > 9) {
						_index = 0;
					}
					IMAGEMANAGER->findImage("player_skill_1_0")->setFrameX(_index);
				}

			}
			else {
				_atkRc.push_back(RectMakeCenter(posX + 80, posY + 80, 350, 300));
				_atk_count++;
				_count++;
				IMAGEMANAGER->findImage("player_skill_1")->setFrameY(1);
				if (_atk_count > 5) {
					_atk_index--;
					_atk_count = 0;

					if (_atk_index < 0) {
						_atk_index = 3;
						/*_state = IDLE;
						break;*/
					}

					IMAGEMANAGER->findImage("player_skill_1")->setFrameX(_atk_index);
					
				}
				if (_count > 2) {
					_count = 0;
					_index++;
					if (_index > 9) {
						_index = 0;
					}
					IMAGEMANAGER->findImage("player_skill_1_0")->setFrameX(_index);
				}

			}
			if (_skill_count > 50) {
				if (_b->get_state() == B_DAMAGE) {
					_b->set_state(B_IDLE);
				}
				_state = JUMP;
				_p_skill = Basic_Attack;
				_atkRc.clear();
			}
			break;
		}
		
		break;
	case SKILL:
		switch (_p_skill)
		{
		case Javelin_throw:
			if (!isJavelin) {
				if (Right_and_left) {
					IMAGEMANAGER->findImage("player_skill_2")->setFrameY(0);
					_count++;
					if (_count > 4) {
						_count = 0;
						_index++;
						if (_index > 9) {
							_index = 8;
						}
						IMAGEMANAGER->findImage("player_skill_2")->setFrameX(_index);
					}
				}
				else {
					IMAGEMANAGER->findImage("player_skill_2")->setFrameY(1);
					_count++;
					if (_count > 4) {
						_count = 0;
						_index--;
						if (_index < 0) {
							_index = 0;
							
						}
						IMAGEMANAGER->findImage("player_skill_2")->setFrameX(_index);
					}
				}
			}
			else {			
				if (Right_and_left) {
					IMAGEMANAGER->findImage("player_skill_2_up")->setFrameY(0);

					_count++;
					if (_count > 4) {
						_count = 0;
						_index++;
						if (_index > 6) {
							isJavelin = false;
							_state = IDLE;
							_p_skill = Basic_Attack;
							_index = 5;
							
						}
						IMAGEMANAGER->findImage("player_skill_2_up")->setFrameX(_index);
					}
				}
				else {
					IMAGEMANAGER->findImage("player_skill_2_up")->setFrameY(1);
					_count++;
					if (_count > 4) {
						_count = 0;
						_index--;
						if (_index < 0) {
							isJavelin = false;
							_state = IDLE;
							_p_skill = Basic_Attack;
							_index = 0;
							
						}
						IMAGEMANAGER->findImage("player_skill_2_up")->setFrameX(_index);
					}
				}
			}

			break;
		}
		break;
	}
}




//hp관련 동작들 test
void player::hp_management()
{
	if (INPUT->GetKeyDown('A')) {
		
	}

	if (skill_gauge.size() >= 3 && this->My_Hp_Get() <5) {
		if (INPUT->GetKeyDown('Z')) {
			for (int i = 0; i < my_hp.size(); i++) {
				if (my_hp[i]->frameX == 0)continue;
				my_hp[i]->frameX = 0;
				break;
			}
			for (int i = 0; i < 3; i++) {
				skill_gauge.erase(skill_gauge.begin() + skill_gauge.size() - 1);
			}
		}
	}
	

	if (INPUT->GetKeyDown('C')) {
		if (skill_gauge.size() < 12) {

			SkillGauge*  _SG = new SkillGauge;
			_SG->Gauge = IMAGEMANAGER->findImage("skill_gauge");
			_SG->posX = 61.5 + skill_gauge.size() * 12;
			_SG->posY = 118;
			skill_gauge.push_back(_SG);
			
		}
		
	}
	/*if (INPUT->GetKeyDown('X')) {
		if (skill_gauge.size()!=0) {
			for (int i = 0; i < 1; i++) {
				skill_gauge.erase(skill_gauge.begin() + skill_gauge.size() - 1);
			}
		}
		
	}*/

	
}
void player::player_sphear_move(float angle)
{
	tagSphear* _ts = new tagSphear;
	_ts->angle = angle;
	_ts->speed = 20.0f;
	_ts->x = (_rc.left + _rc.right) / 2 - 100;
	_ts->y = (_rc.top + _rc.bottom) / 2;	
	_vsphear.push_back(_ts);
}

void player::sphear_move()
{
	for (int i = 0; i < _vsphear.size(); i++) {
		_vsphear[i]->x += cosf((_vsphear[i]->angle)*(3.14 / 180))*_vsphear[i]->speed;
		_vsphear[i]->y += -sinf((_vsphear[i]->angle)*(3.14 / 180))*_vsphear[i]->speed;
	}

	for (int i = 0; i < _vsphear.size(); i++) {
		if (_vsphear[i]->x > 2750 || _vsphear[i]->x+250 < 0) {
			_vsphear.erase(_vsphear.begin() + i);
			break;
		}
	}
}

int player::My_Hp_Get()
{

	int c=0;
	for (int i = 0; i < my_hp.size(); i++) {
		if (my_hp[i]->frameX == 0)c++;

		
	}
	return c;
}



void player::Player_Get_Hp()
{
	
	for (int i = my_hp.size() - 1; i >= 0; i--) {
		if (my_hp[i]->frameX == 1)continue;
		my_hp[i]->frameX = 1;
		break;
	}
}

/*vector<RECT> _atkRc;			//공격용 랙트
	vector<RECT> sh_Rc;				//창 충돌*/
void player::collision()
{
	RECT temp;
	if (_b->get_state() != B_DOWN && _b->get_state() != B_DOWN2) {
		if (IntersectRect(&temp, &_rc, &_b->collisionRc) && _p_skill != Air_attack && !inuincibility) {

			if (!isHp) {
				isHp = true;
				if (_state != DAMAGE) {
					Player_Get_Hp();
					
				}
				inuincibility = true;
			}
			_state = DAMAGE;
			gravity1 = 0;
			if ((_rc.left + _rc.right) / 2 < (_b->collisionRc.left + _b->collisionRc.right) / 2) {
				angle = 140;
			}
			else {
				angle = 40;
			}
			iscoillision = true;
		}

		for (int i = 0; i < _b->collisionRc_2.size(); i++) {
			if (IntersectRect(&temp, &_rc, &_b->collisionRc_2[i])) {
				_state = DAMAGE;
				gravity1 = 0;
				if ((_rc.left + _rc.right) / 2 < (_b->collisionRc.left + _b->collisionRc.right) / 2) {
					angle = 140;
				}
				else {
					angle = 40;
				}
				iscoillision = true;
			}
		}
	}
}

void player::boss_collision()
{
	
		gravity1++;
		posX += cosf(angle * RADIAN) * 22;
		posY += -sinf(angle * RADIAN) * 22 + gravity1;
		_rc = RectMake(posX, posY, 150, 200);
		

		if (posX < 0) {
			posX++;
			angle = 180 - angle;
		}
		if (_rc.right > 2500) {
			posX--;
			angle = 180 - angle;
		}

		_rc = RectMake(posX, posY, 150, 200);
}
//_atkRc;			//공격용 랙트
 //sh_Rc;
void player::boss_body_collision()
{

	RECT temp;
	for (int i = 0; i < _atkRc.size(); i++) {
		if (IntersectRect(&temp, &_atkRc[i], &_b->collisionRc)) {
			if (!isGauge) {
				isGauge = true;
				atkMotion.push_back(temp);
				motion = true;
				if (_p_skill == Air_attack) {
					_b->setHp(3);
				}
				else {
					_b->setHp(1);
				}
				if (skill_gauge.size() < 12) {

					SkillGauge*  _SG = new SkillGauge;
					_SG->Gauge = IMAGEMANAGER->findImage("skill_gauge");
					_SG->posX = 61.5 + skill_gauge.size() * 12;
					_SG->posY = 118;
					skill_gauge.push_back(_SG);
					
					
				}
			}
			
		}
	}

	for (int i = 0; i < _vsphear.size(); i++) {
		if (IntersectRect(&temp, &RectMake(_vsphear[i]->x + 25, _vsphear[i]->y, 160, 20), &_b->collisionRc)) {
			_b->setHp(1);
			_vsphear.erase(_vsphear.begin() + i);
			break;
		}
	}

}

void player::morion_animation()
{
	m_count++;
	if (m_count > 4) {
		m_index++;
		if (m_index > 8) {
			motion = false;
			atkMotion.erase(atkMotion.begin());
			m_index = 0;
		}
		IMAGEMANAGER->findImage("atk")->setFrameX(m_index);
	}
	
}