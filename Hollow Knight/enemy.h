#pragma once

enum BossState
{
	B_IDLE,
	B_JUMP,
	B_MOVE,
	B_ATK,
	B_DAMAGE,
	B_DOWN,
	B_DOWN2
};

enum BossSkill
{
	B_Basic_Attack,
	B_Air_attack,
	B_Strong_attack
};


class enemy 
{
protected:

	float posX,posY;				//적 x,y값
	float speedX;					//스피드X
	float speedY;					//스피드Y
	float jump_power;				//점프 파워
	float angle;						//점프 각도
	int _count;						//이미지 카운트
	int _index;						//이미지 인덱스
	int atk_count[2];
	int atk_index[2];
	int hp;


	float gravity;					//중력
	float gravity_accumulate;		//중력 누적


	RECT _rc;						//몸체rc


	bool _max_jump;					//점프 최고지점
	bool Right_and_left;			//왼쪽 움직임 
	bool isJump;					//점프중인지 검사
};

