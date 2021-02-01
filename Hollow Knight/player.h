#pragma once
#include "gameNode.h"
#define MAXSPEEDX 5
#define MAXSPEEDY 5
#define JUMPMAX 25
//�÷��̾� ����


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
//��ų����
enum Skill
{
	Basic_Attack,
	Air_attack,
	Javelin_throw
};

//hp�̹���
struct HpImage
{
	image* hp;
	int frameX;
	int frameY;

};
//�÷��̾� ��������
struct SkillGauge
{
	image* Gauge;
	int posX;
	int posY;

};
//â
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
	float speedX;					//X ���ǵ�
	float speedY;					//Y ���ǵ�
	float posX;						//�÷��̾� ��ǥ
	float posY;						//�÷��̾� ��ǥ
	float jump_power;				//���� �Ŀ�

	int _count;						//�̹��� ī��Ʈ
	int _index;						//�̹��� �ε���

	int _atk_count;					//���� �̹��� ī��Ʈ
	int _atk_index;					//�����̹��� �ε���
	int _skill_count;				//��ų �ð� ����
	int angle;						//�浹�� ����
	int sphear_speed;				//â���ǵ�

	RECT _rc_sphear;				//�÷��̾� ��ų â ������
	RECT _rc_collision;				//�浹 ��Ʈ
	vector<RECT> atkMotion;
	vector<RECT> _atkRc;			//���ݿ� ��Ʈ
	vector<RECT> sh_Rc;				//â �浹

	float gravity1;
	int count_gravity;				//�浹ó��
	int timeHp;

	float gravity;					//�߷�
	float gravity_accumulate;		//�߷� ����

	vector<tagSphear*> _vsphear;		//â
	vector<HpImage*> my_hp;				//�÷��̾� ü��
	vector<SkillGauge*> skill_gauge;	//��ų ������

	Player_state _state;			//�÷��̾� ����

	RECT _rc;						//�÷��̾� ��Ʈ
	Skill _p_skill;					//�÷��̾� ��ų ����

	boss* _b;

	int inuincibility_count;		//���� �ð�
	bool inuincibility;				//����

	int imageaipcount;
	bool imageaip;

	int m_count;
	int m_index;


	bool motion;
	bool iscoillision;				//������ �浹
	bool isSphear_stert;			//â ������
	bool _max_jump;					//���� �ְ�����
	bool Right_and_left;			//���� ������ 
	bool isJump;					//���������� �˻�
	bool isJavelin;					//â�� ������ �޴��� �˻�
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
	void player_Move_left();	//�÷��̾� ����
	void player_Move_up();		//�÷��̾� ����
	void player_Move_right();	//�÷��̾� ������
	void player_Move_down();	//�÷��̾� �Ʒ�
	void player_atk();			//�÷��̾� ����
	void player_skill();		//�÷��̾� ��ų
	void player_sphear_move(float angle);	//â �̵�
	void player_state();		//�÷��̾� ���� 
	void player_gravity();		//���� �߷°�
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
	void collision();			//������ �浹 �˻�
	void boss_collision();		//
	void boss_body_collision();
	void hp_management();		//�÷��̾� ü�� ���� �� ����
	void animation();			//�ִϸ��̼�	
	void sphear_move();			//â ���󰡱�
	int My_Hp_Get();
	player() {}
	~player() {}
};

