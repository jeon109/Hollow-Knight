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

	float posX,posY;				//�� x,y��
	float speedX;					//���ǵ�X
	float speedY;					//���ǵ�Y
	float jump_power;				//���� �Ŀ�
	float angle;						//���� ����
	int _count;						//�̹��� ī��Ʈ
	int _index;						//�̹��� �ε���
	int atk_count[2];
	int atk_index[2];
	int hp;


	float gravity;					//�߷�
	float gravity_accumulate;		//�߷� ����


	RECT _rc;						//��ürc


	bool _max_jump;					//���� �ְ�����
	bool Right_and_left;			//���� ������ 
	bool isJump;					//���������� �˻�
};

