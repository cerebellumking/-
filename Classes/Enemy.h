#pragma once

#ifndef _Enemy_H_
#define _Enemy_H_

#include"knight.h"
#include"sprite.h"
#include"cocos2d.h"

USING_NS_CC;

//�������

class enemy:public sprite_living
{
	
private:
	float sight_distance;                                     //������Ұ
	float attack_distance;                                    //���﹥����Χ
	Vec2 enemy_pos;                                           //�������꣨����Ѳ�߽߱���ж�������ʵʱ���£�
	Vec2 knight_pos;                                          //attack��������˲����ʿ���꣬ÿһ�ι���ʱ���»�ȡ
public:
	//enemy() = default;

	//~enemy();
    //virtual bool init();
	CREATE_FUNC(enemy);
	void set_sight_distance(float sight_distance);              //������Ұ
	void set_attack_distance(float attack_distance);            //���ù�����Χ
	float get_distance(knight* Knight);                         //��ȡ��������ʿ֮���ֱ�߾���
	float get_distancex(knight* Knight);                        //��ȡ��������ʿ֮���x�᷽�����
	float get_distancey(knight* Knight);                        //��ȡ��������ʿ֮���y�᷽�����
	//virtual void death_animation();                           //������������
	virtual bool if_close_to_actor(knight* Knight) ;            //�Ƿ���������㹻��,��սԶ���ж��ж���׼��ͬ
	virtual bool if_attack(knight* Knight);                     //�Ƿ񹥻�����
	//bool if_collided_with_actor(knight* Knight) ;               //�Ƿ���������ײ
	Vec2 get_enemy_pos();                                       //��ȡ��������
	void set_enemy_pos();                                       //���ù�������
	virtual void move(knight* Knight);                          //�ƶ���ʽ,������ʿ����
	virtual void wander();                                      //δ���ֵ���ʱ�ǻ� 
	bool if_collide(knight* Knight,Sprite* bullet);             //����ӵ��Ƿ�����ʿ��ײ��������ӵ�����ʿ
	bool if_collide(Sprite* enemy_, Sprite* bullet);            //����ӵ��Ƿ�����ʿ��ײ����ʿ���ӵ��͹�
	//

};

//������ս����������
class enemy_melee1 :public enemy{
public:
	//virtual void death_animation()override;
	CREATE_FUNC(enemy_melee1);
	virtual bool init();
private:
};

class enemy_melee2 :public enemy{

public:
	virtual bool init();
	CREATE_FUNC(enemy_melee2);
	//virtual void death_animation()override;
private:
	
};

//����Զ�̹���������
class enemy_remote1 :public enemy{
public:
	virtual bool init();
	Sprite* get_bullet();
	virtual void attack(knight* Knight); 
	void remove_bullet();
	//virtual void death_animation()override;
private:
	Sprite* bullet;
	
};

class enemy_remote2 :public enemy {
public:
	virtual bool init();
	//virtual void death_animation()override;
	Sprite* get_bullet();
	virtual void attack(knight* Knight);
private:
	Sprite* bullet;
};

class boss :public enemy{
public:
	//virtual void death_animation()override;
private:
	
};

#endif;