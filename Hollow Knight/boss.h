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

	void animation();			//�ִϸ��̼�	
	void boss_state();			//���� ����
	void boss_state_move();		//���� ���º� �ൿ
	void boss_jump();			//���� ����
	void boss_gravity();		//���� �߷� ���
	void right_left();			//���� ����
	void count_set(int count,int index);
	int getHp() { return bossHp; }
	void setHp(int num) {
		bossHp -= num;
	}

	void BossIsDown();			//�����ٿ�
	void BossDown();			//���� �ٿ�
	void setPlayer(player* p){
		_p = p;
	}							//�÷��̾� �� ��������
	float player_getAngle();		//�÷��̾� ��ó�� ����

	void boss_atk_collision();
	BossState get_state() { return _state; }
	void set_state(BossState _bs) {
		_state = _bs;
	};
private:
	int pattern_count;			//���� ī��Ʈ
	int rendom_atk;				//���� ���� �޾� ����
	int jump_atk_count;			//�����ѵ� ��� ����
	int bossHp;
	int finerHp;
	bool isbossHp;				//ü��
	int gravity1;
	bool isbossHpCount;			//����;
	float angle1;
	bool isHp;
	bool jumping;				//����
	bool jump_start;			//�����غ���
	bool isBasic_atk;			//�⺻������
	bool atk_two;				//�⺻���� �ι�° ���
	bool isDown2;
	bool isDown3;
	bool isDown4;
	bool isDown5;

};

