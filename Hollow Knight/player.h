#pragma once
#include "gameNode.h"
#define MAXSPEEDX 5
#define MAXSPEEDY 5
#define JUMPMAX 25
//플레이어 상태


enum Player_state
{
	IDLE,
	DOWN,
	JUMP,
	MOVE,
	ATK,
	SKILL,
	DAMAGE
	
};
//스킬관련
enum Skill
{
	Basic_Attack,
	Air_attack,
	Javelin_throw
};

//hp이미지
struct HpImage
{
	image* hp;
	int frameX;
	int frameY;

};
//플레이어 게이지바
struct SkillGauge
{
	image* Gauge;
	int posX;
	int posY;

};
//창
struct tagSphear
{
	float x, y;
	float speed;
	float angle;
};

class boss;
class player : public gameNode
{

private:	
	float speedX;					//X 스피드
	float speedY;					//Y 스피드
	float posX;						//플레이어 좌표
	float posY;						//플레이어 좌표
	float jump_power;				//점프 파워

	int _count;						//이미지 카운트
	int _index;						//이미지 인덱스

	int _atk_count;					//공격 이미지 카운트
	int _atk_index;					//공격이미지 인덱스
	int _skill_count;				//스킬 시간 조정
	int angle;						//충돌후 날라감
	int sphear_speed;				//창스피드

	RECT _rc_sphear;				//플레이어 스킬 창 던지기
	RECT _rc_collision;				//충돌 랙트
	vector<RECT> atkMotion;
	vector<RECT> _atkRc;			//공격용 랙트
	vector<RECT> sh_Rc;				//창 충돌

	float gravity1;
	int count_gravity;				//충돌처리
	int timeHp;

	float gravity;					//중력
	float gravity_accumulate;		//중력 누적

	vector<tagSphear*> _vsphear;		//창
	vector<HpImage*> my_hp;				//플레이어 체력
	vector<SkillGauge*> skill_gauge;	//스킬 게이지

	Player_state _state;			//플레이어 상태

	RECT _rc;						//플레이어 랙트
	Skill _p_skill;					//플레이어 스킬 종류

	boss* _b;

	int inuincibility_count;		//무적 시간
	bool inuincibility;				//무적

	int imageaipcount;
	bool imageaip;

	int m_count;
	int m_index;


	bool motion;
	bool iscoillision;				//보스봅 충돌
	bool isSphear_stert;			//창 던지기
	bool _max_jump;					//점프 최고지점
	bool Right_and_left;			//왼쪽 움직임 
	bool isJump;					//점프중인지 검사
	bool isJavelin;					//창을 던지고 받는지 검사
	bool isHp;
	bool isGauge;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	float getX() { return _rc.left/*(_rc.left + _rc.right) / 2; */; }
	float getY() { return _rc.top/* (_rc.top + _rc.bottom) / 2*/; }
	RECT playerRc() { return _rc; }

	void setCollsion(bool t) { iscoillision = t; }
	void player_Move_left();	//플레이어 왼쪽
	void player_Move_up();		//플레이어 점프
	void player_Move_right();	//플레이어 오른쪽
	void player_Move_down();	//플레이어 아래
	void player_atk();			//플레이어 공격
	void player_skill();		//플레이어 스킬
	void player_sphear_move(float angle);	//창 이동
	void player_state();		//플레이어 상태 
	void player_gravity();		//점프 중력값
	vector<RECT>  player_atk_Rc() { return _atkRc; }
	void setBossInfo(boss* b) { _b = b; }

	bool getinuincibility() {
		return inuincibility;
	}
	void setinuincibility(bool r) {
		inuincibility = r;
	}

	void morion_animation();
	Skill getSkill() {return _p_skill;}
	Player_state getState() { return _state; };
	void Player_Get_Hp();
	void collision();			//보스랑 충돌 검사
	void boss_collision();		//
	void boss_body_collision();
	void hp_management();		//플레이어 체력 관리 및 랜더
	void animation();			//애니메이션	
	void sphear_move();			//창 날라가기
	int My_Hp_Get();
	player() {}
	~player() {}
};

