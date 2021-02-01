#pragma once
#include "enemy.h"

class player;
class boss : public enemy
{
public:

	RECT collisionRc;
	vector<RECT> _b_head;
	vector<RECT> collisionRc_2;

	player* _p;

	BossState _state;

	BossSkill _skill;

	HRESULT init();
	void release();
	void update();
	void render();
	RECT LeftRc;
	RECT RightRc;

	void animation();			//애니메이션	
	void boss_state();			//보스 상태
	void boss_state_move();		//보스 상태별 행동
	void boss_jump();			//보스 점프
	void boss_gravity();		//보스 중력 계산
	void right_left();			//보스 방향
	void count_set(int count,int index);
	int getHp() { return bossHp; }
	void setHp(int num) {
		bossHp -= num;
	}

	void BossIsDown();			//보스다운
	void BossDown();			//보스 다운
	void setPlayer(player* p){
		_p = p;
	}							//플레이어 값 가져오기
	float player_getAngle();		//플래이어 근처로 점프

	void boss_atk_collision();
	BossState get_state() { return _state; }
	void set_state(BossState _bs) {
		_state = _bs;
	};
private:
	int pattern_count;			//패턴 카운트
	int rendom_atk;				//랜덤 값을 받아 공격
	int jump_atk_count;			//공격한뒤 잠시 멈춤
	int bossHp;
	int finerHp;
	bool isbossHp;				//체력
	int gravity1;
	bool isbossHpCount;			//보스;
	float angle1;
	bool isHp;
	bool jumping;				//점프
	bool jump_start;			//점프준비중
	bool isBasic_atk;			//기본공격중
	bool atk_two;				//기본공격 두번째 모션
	bool isDown2;
	bool isDown3;
	bool isDown4;
	bool isDown5;

};

