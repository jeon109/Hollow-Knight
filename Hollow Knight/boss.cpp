#include "stdafx.h"
#include "boss.h"
#include "player.h"
HRESULT boss::init()
{
	gravity1 = 0;
	speedX = 35.0f;							//X 스피드
	speedY = 35.5f;							//Y 스피드
	posX = WINSIZEX-100;					//플레이어 좌표
	posY = WINSIZEY / 2+83;					//플레이어 좌표
	jump_power = 0.8f;						//점프 올락는 속도
	gravity_accumulate = 0;					//중력 누적값
	gravity = 0.4f;							//중력
	_count = 0;								//움직임 카운트
	_index = 0;								//움직음 프레임 
	angle = 90;								//보스 점프 각도
	_rc = RectMake(posX, posY, 624, 400);	//보스 랙트
	rendom_atk = 0;
	atk_count[2] = { 0 };
	atk_index[2] = { 0 };
	pattern_count = 0;
	_state  = B_IDLE;						//가만히
	_skill = B_Basic_Attack;				//기본공격
	collisionRc = RectMakeCenter(posX + 390, posY + 250, 350, 250);
	hp = 30;
	jump_atk_count = 0;
	angle1 = 0;
	isDown4 = false;
	bossHp=10;
	finerHp = 0;
	isbossHpCount = false;
	isDown2 = false;
	isJump = false;							//점프상태 확인
	Right_and_left = true;					//좌우 움직임
	_max_jump = false;						//점프 최대 위치 도달
	atk_two = false;						//기본공격 
	isBasic_atk = false;					//기본공격중
	jump_start = false;						//점프준비
	isHp = false;
	isDown3 = false;
	isDown5 = false;
	return S_OK;
}

void boss::release()
{
}

void boss::update()
{
	if (bossHp == 0) {
		_state = B_DOWN;
		gravity1 = 0;
		if (Right_and_left) {
			angle1 = 140;
		}
		else {
			angle1 = 40;
		}
	}
	
	animation();
	boss_gravity();
	boss_atk_collision();
	right_left();
	if (bossHp > 0) {


		if (!isJump && !isBasic_atk && _state != B_DAMAGE && _state != B_DOWN && _state != B_DOWN2) {
			pattern_count++;
			if (pattern_count > 50) {
				pattern_count = 0;
				boss_state();
			}
		}
		else if (_state != B_DOWN && _state != B_DOWN2) {
			boss_jump();
		}


		if (_state == B_ATK && _skill == B_Air_attack && _state != B_DOWN && _state != B_DOWN2) {
			if (speedX < gravity) {
				_max_jump = true;
			}
		}

		if (_state == B_IDLE || _state == B_DOWN2 || _state == B_DOWN) {
			collisionRc_2.clear();
			isHp = false;
		}
		collisionRc = RectMakeCenter(posX + 390, posY + 250, 200, 250);
	}
	boss_state_move();

	player_getAngle();

	cout << bossHp << endl;

	if (bossHp < 0) {
		_state = B_DOWN;
		gravity1 = 0;
		if (Right_and_left) {
			angle1 = 140;
		}
		else {
			angle1 = 40;
		}
	}
	BossIsDown();
}

void boss::render()
{
	
	//Rectangle(CAMERAMANAGER->getMemDC(), _rc);
	switch (_state)
	{
	case B_IDLE:
		if (Right_and_left) {
			IMAGEMANAGER->frameRender("boss_idle", CAMERAMANAGER->getMemDC(), _rc.left, _rc.top-10);
		}
		else {
			IMAGEMANAGER->frameRender("boss_idle", CAMERAMANAGER->getMemDC(), _rc.left+130, _rc.top-10);
		}
		break;
	case B_JUMP:
			if (!jump_start) {
				if (Right_and_left) {
					IMAGEMANAGER->frameRender("Boss_jump_start", CAMERAMANAGER->getMemDC(), _rc.left, _rc.top);
				}
				else {
					IMAGEMANAGER->frameRender("Boss_jump_start", CAMERAMANAGER->getMemDC(), _rc.left + 130, _rc.top);
				}
			}
			else {
				if (Right_and_left) {
					IMAGEMANAGER->frameRender("Boss_is_jump", CAMERAMANAGER->getMemDC(), _rc.left, _rc.top);
				}
				else {
					IMAGEMANAGER->frameRender("Boss_is_jump", CAMERAMANAGER->getMemDC(), _rc.left + 130, _rc.top);
				}
			}
		break;
	case B_ATK:

		switch (_skill)
		{
		case B_Basic_Attack:
			if (!atk_two) {
				if (Right_and_left) {
					IMAGEMANAGER->frameRender("Boss_atk_1", CAMERAMANAGER->getMemDC(), _rc.left, _rc.top);
				}
				else {
					IMAGEMANAGER->frameRender("Boss_atk_1", CAMERAMANAGER->getMemDC(), _rc.left + 180, _rc.top);
				}
			}
			else {
				if (Right_and_left) {
					IMAGEMANAGER->frameRender("Boss_atk_2", CAMERAMANAGER->getMemDC(), _rc.left , _rc.top-180);
				}
				else {
					IMAGEMANAGER->frameRender("Boss_atk_2", CAMERAMANAGER->getMemDC(), _rc.left , _rc.top-180);
				}
			}
			break;
		case B_Air_attack:
			if (!_max_jump) {
				if (!jump_start) {
					if (Right_and_left) {
						IMAGEMANAGER->frameRender("Boss_jump_start", CAMERAMANAGER->getMemDC(), _rc.left, _rc.top);
					}
					else {
						IMAGEMANAGER->frameRender("Boss_jump_start", CAMERAMANAGER->getMemDC(), _rc.left + 130, _rc.top);
					}
				}
				else {
					if (Right_and_left) {
						IMAGEMANAGER->frameRender("Boss_atk_jump", CAMERAMANAGER->getMemDC(), _rc.left, _rc.top);
					}
					else {
						IMAGEMANAGER->frameRender("Boss_atk_jump", CAMERAMANAGER->getMemDC(), _rc.left + 130, _rc.top);
					}
				}
			}
			else {

				if (Right_and_left) {
					IMAGEMANAGER->frameRender("Boss_atk_jump_2", CAMERAMANAGER->getMemDC(), _rc.left, _rc.top-150);
				}
				else {
					IMAGEMANAGER->frameRender("Boss_atk_jump_2", CAMERAMANAGER->getMemDC(), _rc.left + 130, _rc.top-150);
				}

			}
			break;
		case B_Strong_attack:
			break;
		}
		break;
	case B_DAMAGE:
		if (Right_and_left) {
			IMAGEMANAGER->frameRender("Boss_Damage", CAMERAMANAGER->getMemDC(), _rc.left, _rc.top,0,1);
		}
		else {
			IMAGEMANAGER->frameRender("Boss_Damage", CAMERAMANAGER->getMemDC(), _rc.left + 130, _rc.top,0,0);
		}
		break;
	case B_DOWN:
		IMAGEMANAGER->frameRender("Boss_Damage", CAMERAMANAGER->getMemDC(), _rc.left, _rc.top, 0, 1);

		break;
	case B_DOWN2:
		if (!isDown5) {
			if (!isDown4) {
				if (!isDown3) {
					if (!isDown2) {
						if (Right_and_left) {
							IMAGEMANAGER->frameRender("Boss_down_1", CAMERAMANAGER->getMemDC(), _rc.left + 50, _rc.top - 80);
						}
						else {
							IMAGEMANAGER->frameRender("Boss_down_1", CAMERAMANAGER->getMemDC(), _rc.left, _rc.top - 80);
						}
					}
					else {
						if (Right_and_left) {
							IMAGEMANAGER->frameRender("Boss_down_2", CAMERAMANAGER->getMemDC(), _rc.left, _rc.top - 80);
						}
						else {
							IMAGEMANAGER->frameRender("Boss_down_2", CAMERAMANAGER->getMemDC(), _rc.left + 130, _rc.top - 80);
						}
					}
				}
				else {
					if (Right_and_left) {
						IMAGEMANAGER->frameRender("Boss_down_3", CAMERAMANAGER->getMemDC(), _rc.left, _rc.top - 80);
					}
					else {
						IMAGEMANAGER->frameRender("Boss_down_3", CAMERAMANAGER->getMemDC(), _rc.left + 130, _rc.top - 80);
					}

				}
			}
			else {
				if (Right_and_left) {
					IMAGEMANAGER->frameRender("Boss_down_3", CAMERAMANAGER->getMemDC(), _rc.left, _rc.top - 80);
				}
				else {
					IMAGEMANAGER->frameRender("Boss_down_3", CAMERAMANAGER->getMemDC(), _rc.left + 130, _rc.top - 80);
				}
			}
		}
		else {
			if (Right_and_left) {
				IMAGEMANAGER->frameRender("Boss_down_3", CAMERAMANAGER->getMemDC(), _rc.left, _rc.top - 80);
				IMAGEMANAGER->frameRender("Boss_head_down", CAMERAMANAGER->getMemDC(), _rc.left+200, _rc.top+200);
			}
			else {
				IMAGEMANAGER->frameRender("Boss_down_3", CAMERAMANAGER->getMemDC(), _rc.left + 130, _rc.top - 80);
				IMAGEMANAGER->frameRender("Boss_head_down", CAMERAMANAGER->getMemDC(), _rc.left + 130, _rc.top+200);
			}

		}
		
		break;
	}

	
	
	//Rectangle(CAMERAMANAGER->getMemDC(), collisionRc);
	//
	//for (int i = 0; i < collisionRc_2.size(); i++) {
	//	Rectangle(CAMERAMANAGER->getMemDC(), collisionRc_2[i]);
	//}
	
}

void boss::animation()
{

	switch (_state)
	{
	case B_IDLE:
		if (!Right_and_left) {
			IMAGEMANAGER->findImage("boss_idle")->setFrameY(0);
			_count++;
			if (_count > 8) {
				_count = 0;
				_index++;
				if (_index > 5) {
					_index = 0;
				}
				IMAGEMANAGER->findImage("boss_idle")->setFrameX(_index);
			}
		}
		else {
			IMAGEMANAGER->findImage("boss_idle")->setFrameY(1);
			_count++;
			if (_count > 8) {
				_count = 0;
				_index--;
				if (_index < 0) {
					_index = 4;
				}
				IMAGEMANAGER->findImage("boss_idle")->setFrameX(_index);
			}
		}
		break;
	case B_JUMP:
		if (!jump_start) {
			if (Right_and_left) {
				IMAGEMANAGER->findImage("Boss_jump_start")->setFrameY(1);
				_count++;
				if (_count > 4) {
					_count = 0;
					_index++;
					if (_index > 3) {
						jump_start = true;
					}
					IMAGEMANAGER->findImage("Boss_jump_start")->setFrameX(_index);
				}
			}
			else {
				IMAGEMANAGER->findImage("Boss_jump_start")->setFrameY(0);
				_count++;
				if (_count > 4) {
					_count = 0;
					_index--;
					if (_index < 0) {
						jump_start = true;
					}
					IMAGEMANAGER->findImage("Boss_jump_start")->setFrameX(_index);
				}
			}
		}
		else {
			if (Right_and_left) {
				IMAGEMANAGER->findImage("Boss_is_jump")->setFrameY(1);
				_count++;
				if (_count > 8) {
					_count = 0;
					_index--;
					if (_index < 0) {
						_index = 3;
					}
					IMAGEMANAGER->findImage("Boss_is_jump")->setFrameX(_index);
				}
			}
			else {
				IMAGEMANAGER->findImage("Boss_is_jump")->setFrameY(0);
				_count++;
				if (_count > 8) {
					_count = 0;
					_index++;
					if (_index > 4) {
						_index = 0;
					}
					IMAGEMANAGER->findImage("Boss_is_jump")->setFrameX(_index);
				}
			}
		}

		break;
	case B_ATK:
		switch (_skill)
		{
		case B_Basic_Attack:
			if (!atk_two) {
				if (Right_and_left) {
					IMAGEMANAGER->findImage("Boss_atk_1")->setFrameY(1);
					_count++;
					if (_count > 5) {
						_count = 0;
						_index--;
						if (_index < 0) {
							_index = 0;
							atk_two = true;
						}
						if (!atk_two) {
							IMAGEMANAGER->findImage("Boss_atk_1")->setFrameX(_index);
						}
					}
				}
				else {
					IMAGEMANAGER->findImage("Boss_atk_1")->setFrameY(0);
					_count++;
					if (_count > 5) {
						_count = 0;
						_index++;
						if (_index > 5) {
							_index = 3;
							atk_two = true;
						}
						if (!atk_two) {
							IMAGEMANAGER->findImage("Boss_atk_1")->setFrameX(_index);
						}
					}
				}
			}
			else {
				if (Right_and_left) {
					collisionRc_2.push_back(RectMakeCenter(posX + 600, posY + 240, 80, 200));
					IMAGEMANAGER->findImage("Boss_atk_2")->setFrameY(1);
					atk_count[0]++;
					if (atk_count[0] > 5) {
						atk_count[0] = 0;
						atk_index[0]++;
						if (atk_index[0] > 3) {

							atk_index[0] = 0;
							if (bossHp > 0) {
								_state = B_IDLE;

								atk_two = false;
								isBasic_atk = false;
								collisionRc_2.clear();
								isHp = false;
							}
						}
						if (atk_two) {
							IMAGEMANAGER->findImage("Boss_atk_2")->setFrameX(atk_index[0]);
						}
					}

				}
				else {
					collisionRc_2.push_back(RectMakeCenter(posX + 100, posY + 240, 80, 200));
					IMAGEMANAGER->findImage("Boss_atk_2")->setFrameY(0);
					atk_count[1]++;
					if (atk_count[1] > 5) {
						atk_count[1] = 0;
						atk_index[1]--;
						if (atk_index[1] < 0) {
							atk_index[1] = 3;
							if (bossHp > 0) {
								_state = B_IDLE;

								atk_two = false;
								isBasic_atk = false;
								collisionRc_2.clear();
								isHp = false;
							}

						}
						if (atk_two) {
							IMAGEMANAGER->findImage("Boss_atk_2")->setFrameX(atk_index[1]);
						}
					}
				}
			}
			break;
		case B_Air_attack:
			if (!_max_jump) {
				if (!jump_start) {
					if (Right_and_left) {
						IMAGEMANAGER->findImage("Boss_jump_start")->setFrameY(1);
						_count++;
						if (_count > 4) {
							_count = 0;
							_index++;
							if (_index > 3) {
								jump_start = true;
							}
							IMAGEMANAGER->findImage("Boss_jump_start")->setFrameX(_index);
						}
					}
					else {
						IMAGEMANAGER->findImage("Boss_jump_start")->setFrameY(0);
						_count++;
						if (_count > 4) {
							_count = 0;
							_index--;
							if (_index < 0) {
								jump_start = true;
							}
							IMAGEMANAGER->findImage("Boss_jump_start")->setFrameX(_index);
						}
					}
				}
				else {
					if (Right_and_left) {
						IMAGEMANAGER->findImage("Boss_atk_jump")->setFrameY(1);
						_count++;
						if (_count > 8) {
							_count = 0;
							_index--;
							if (_index < 0) {
								_index = 3;
							}
							IMAGEMANAGER->findImage("Boss_atk_jump")->setFrameX(_index);
						}
					}
					else {
						IMAGEMANAGER->findImage("Boss_atk_jump")->setFrameY(0);
						_count++;
						if (_count > 8) {
							_count = 0;
							_index++;
							if (_index > 4) {
								_index = 0;
							}
							IMAGEMANAGER->findImage("Boss_atk_jump")->setFrameX(_index);
						}
					}
				}
			}
			else {
				if (Right_and_left) {

					IMAGEMANAGER->findImage("Boss_atk_jump_2")->setFrameY(1);
					if (_rc.bottom > WINSIZEY - 150) {

						IMAGEMANAGER->findImage("Boss_atk_jump_2")->setFrameX(1);
						CAMERAMANAGER->camerashiver(_p->getX(), _p->getY());

						_max_jump = false;
					}
					if (_rc.bottom > WINSIZEY - 80) {
						collisionRc_2.push_back(RectMakeCenter(posX + 600, posY + 240, 80, 200));
					}
				}
				else {

					IMAGEMANAGER->findImage("Boss_atk_jump_2")->setFrameY(0);
					if (_rc.bottom > WINSIZEY - 150) {

						IMAGEMANAGER->findImage("Boss_atk_jump_2")->setFrameX(0);
						CAMERAMANAGER->camerashiver(_p->getX(), _p->getY());

						_max_jump = false;
					}
					if (_rc.bottom > WINSIZEY - 80) {
						collisionRc_2.push_back(RectMakeCenter(posX + 100, posY + 240, 80, 200));
					}

				}

			}
			break;
		case B_Strong_attack:
			break;

		}
		break;
	case B_DOWN2:
		if (!isDown5) {
			if (!isDown4) {
				if (!isDown3) {
					if (!isDown2) {
						if (Right_and_left) {
							IMAGEMANAGER->findImage("Boss_down_1")->setFrameY(1);
							_count++;
							if (_count > 10) {
								_count = 0;
								_index++;
								if (_index > 4) {
									_index = 0;
									isDown2 = true;
								}
								IMAGEMANAGER->findImage("Boss_down_1")->setFrameX(_index);
							}
						}
						else {
							IMAGEMANAGER->findImage("Boss_down_1")->setFrameY(0);
							_count++;
							if (_count > 10) {
								_count = 0;
								_index--;
								if (_index < 0) {
									_index = 3;
									isDown2 = true;
								}
								IMAGEMANAGER->findImage("Boss_down_1")->setFrameX(_index);
							}
						}
					}
					else {
						if (Right_and_left) {
							IMAGEMANAGER->findImage("Boss_down_2")->setFrameY(1);
							_count++;
							if (_count > 10) {
								_count = 0;
								_index++;
								if (_index > 4) {

									_index = 0;
									isDown3 = true;
								}
								IMAGEMANAGER->findImage("Boss_down_2")->setFrameX(_index);
							}
						}
						else {
							IMAGEMANAGER->findImage("Boss_down_2")->setFrameY(0);
							_count++;
							if (_count > 10) {
								_count = 0;
								_index--;
								if (_index < 0) {
									_index = 3;
									isDown3 = true;
								}
								IMAGEMANAGER->findImage("Boss_down_2")->setFrameX(_index);
							}
						}
					}
				}
				else {
					if (Right_and_left) {
						IMAGEMANAGER->findImage("Boss_down_3")->setFrameY(1);
						_count++;
						if (_count > 10) {
							_count = 0;
							_index++;

							if (_index > 4) {

								isDown5 = true;
								_index = 0;
							}
							IMAGEMANAGER->findImage("Boss_down_3")->setFrameX(_index);
							if (_index == 3) {
								_b_head.push_back(RectMake(posX + 300, posY + 250, 123, 145));
							}
						}
					}
					else {
						IMAGEMANAGER->findImage("Boss_down_3")->setFrameY(0);
						_count++;
						if (_count > 10) {
							_count = 0;
							_index--;
							if (_index == 0) {
								_b_head.push_back(RectMake(posX + 115, posY + 250, 123, 145));
							}
							if (_index < 0) {
								_count = 0;
								_index = 3;
								isDown5 = true;
							}
							IMAGEMANAGER->findImage("Boss_down_3")->setFrameX(_index);
							if (_index == 0) {
								_b_head.push_back(RectMake(posX + 115, posY + 250, 123, 145));
							}
						}
					}
				}
			}
		}
		else {

			if (Right_and_left) {
				IMAGEMANAGER->findImage("Boss_head_down")->setFrameY(1);
				IMAGEMANAGER->findImage("Boss_down_3")->setFrameY(1);
				IMAGEMANAGER->findImage("Boss_down_3")->setFrameX(3);
				_count++;
				if (_count > 10) {
					_count = 0;
					_index++;
					if (_index > 4) {
						_index = 3;
					}
					IMAGEMANAGER->findImage("Boss_head_down")->setFrameX(_index);
				}
			}
			else {
				IMAGEMANAGER->findImage("Boss_head_down")->setFrameY(0);
				IMAGEMANAGER->findImage("Boss_down_3")->setFrameY(0);
				IMAGEMANAGER->findImage("Boss_down_3")->setFrameX(0);
				_count++;
				if (_count > 10) {
					_count = 0;
					_index--;
					if (_index < 0) {
						_index = 0;
					}
					IMAGEMANAGER->findImage("Boss_head_down")->setFrameX(_index);

				}
			}
		}
		break;
	}
	

}

void boss::boss_state()
{
	rendom_atk = RANDOM->range(1,3);

	switch (rendom_atk)
	{
	case 0:
		if (Right_and_left) {
			count_set(0, 4);
		}
		else {
			count_set(0, 0);
		}
		if (bossHp > 0) {
			_state = B_IDLE;
		}
		
		break;
	case 1:
		angle = player_getAngle();
		isJump = true;
		gravity = 0;
		if (Right_and_left) {
			count_set(0, 2);
		}
		else {
			count_set(0, 0);
		}
		if (bossHp > 0) {
			_state = B_JUMP;
		}

		break;

	case 2:
		if (_UTIL::getDistance(((_p->playerRc().left + _p->playerRc().right) / 2),
			((_p->playerRc().top + _p->playerRc().bottom) / 2), posX + 390, posY + 250) > 0 && _UTIL::getDistance(((_p->playerRc().left + _p->playerRc().right) / 2),
			((_p->playerRc().top + _p->playerRc().bottom) / 2), posX + 390, posY + 250) < 400) 
		{
			
			if (Right_and_left) {
				atk_count[0] = 0;
				atk_index[0] = 0;
				IMAGEMANAGER->findImage("Boss_atk_2")->setFrameX(atk_index[0]);
			}
			else {
				atk_count[1] = 0;
				atk_index[1] = 3;
				IMAGEMANAGER->findImage("Boss_atk_2")->setFrameX(atk_index[1]);
			}
			if (bossHp > 0) {
				_state = B_ATK;
				_skill = B_Basic_Attack;
				isBasic_atk = true;
			}
		}
		else if (_UTIL::getDistance(((_p->playerRc().left + _p->playerRc().right) / 2),
			((_p->playerRc().top + _p->playerRc().bottom) / 2), posX + 390, posY + 250) > 400 && _UTIL::getDistance(((_p->playerRc().left + _p->playerRc().right) / 2),
			((_p->playerRc().top + _p->playerRc().bottom) / 2), posX + 390, posY + 250) < 1000) 
		{
			if (bossHp > 0) {
				angle = player_getAngle();
				isJump = true;
				gravity = 0;
				_state = B_ATK;
				_skill = B_Air_attack;
			}

			if (Right_and_left) {
				IMAGEMANAGER->findImage("Boss_atk_jump_2")->setFrameX(0);
			}
			else {
				IMAGEMANAGER->findImage("Boss_atk_jump_2")->setFrameX(1);
			}
			
			
			
		}
		else if (_UTIL::getDistance(((_p->playerRc().left + _p->playerRc().right) / 2),
			((_p->playerRc().top + _p->playerRc().bottom) / 2), posX + 390, posY + 250) > 1000)
		{
			cout << "보류" << endl;

		}
	}
}

void boss::boss_state_move()
{

}

void boss::boss_jump()
{
	if (bossHp > 0) {
		if (isJump) {
			gravity++;
			if (gravity > 55) {
				gravity = 55;
			}
			posX += cosf(angle) * speedX;
			posY += -sinf(angle) * speedY + gravity;


			if (posX + 80 < 0) {
				posX++;
				angle = PI - angle;
			}
			if (posX + 624 > 2500) {
				posX--;
				angle = PI - angle;
			}
			_rc = RectMake(posX, posY, 624, 400);
		}
	}
}

void boss::boss_gravity()
{

	if (_rc.bottom > WINSIZEY - 28) {
		gravity = 0;
		_rc = RectMake(posX, posY-=3, 624, 400);
		CAMERAMANAGER->camerashiver(_p->getX(), _p->getY());
		if (_state != B_DOWN && bossHp > 0) {
			_state = B_IDLE;
		}
		else {
			_state = B_DOWN2;
		}
		
		
		isJump = false;
	}
}

void boss::right_left()
{

	if (!isJump && !isBasic_atk) {
		float _x = ((_p->playerRc().left + _p->playerRc().right) / 2);
		if (_x > posX + 390) {
			Right_and_left = true;

		}
		else {
			Right_and_left = false;

		}
	}
}

void boss::count_set(int count, int index)
{
	_count = count;
	_index = index;
}

void boss::BossIsDown()
{
	if (_state == B_DOWN) {
		
		gravity1++;
		posX += cosf(angle1 * RADIAN) * 20;
		posY += -sinf(angle1 * RADIAN) * 20 + gravity1;
		if (posX+80 < 0) {
			posX++;
			angle = PI - angle;
		}
		if (posX + 624 > 2500) {
			posX--;
			angle = PI - angle;
		}
		_rc = RectMake(posX, posY, 624, 400);
		bossHp = 10;
	}
	
}


float boss::player_getAngle()
{
	float _x = (((_p->playerRc().left + _p->playerRc().right) / 2) + ((_rc.left + _rc.right) / 2))/2;
	float _y = (((_p->playerRc().top + _p->playerRc().bottom) / 2) + ((_rc.top + _rc.bottom) / 2))/2-1900;
	//Rectangle(CAMERAMANAGER->getMemDC(), RectMake(_x, _y, 10, 10));
	//Rectangle(CAMERAMANAGER->getMemDC(), RectMake(posX+390, posY+250, 10, 10));
	RECT temp = RectMake(_x, _y, 10, 10);
	//ut << _UTIL::getAngle(posX + 390, posY + 250, ((temp.left + temp.left) / 2), (temp.top + temp.bottom) / 2) << endl;
	//cout << _UTIL::getDistance(((_p->playerRc().left + _p->playerRc().right) / 2), ((_p->playerRc().top + _p->playerRc().bottom) / 2), posX + 390, posY + 250) << endl;
	//cout << _UTIL::getDistance(((_p->playerRc().left + _p->playerRc().right) / 2), ((_p->playerRc().top + _p->playerRc().bottom) / 2), posX + 390, posY + 250) << endl;
	return _UTIL::getAngle(posX + 390, posY + 250, ((temp.left + temp.left) / 2), (temp.top + temp.bottom) / 2);
}

void boss::boss_atk_collision()
{
	RECT temp;
	for (int i = 0; i < collisionRc_2.size(); i++) {
		if (IntersectRect(&temp, &_p->playerRc(), &collisionRc_2[i]) && !_p->getinuincibility()) {
			if (!isHp) {
				isHp = true;
				if(_p->getState() != DAMAGE){
				_p->Player_Get_Hp();
				_p->setinuincibility(true);
				}
			}
			break;
		}
	}

	for (int i = 0; i < _p->player_atk_Rc().size(); i++) {
		if (_p->getSkill() != Air_attack)continue;
		if (IntersectRect(&temp, &_p->player_atk_Rc()[i], &collisionRc)) {		
			if (_p->getSkill() == Air_attack) {
				_state = B_DAMAGE;
				break;
			}
		}
	}


}


void boss::BossDown()
{
	if (_state == B_DOWN2) {

	}
}