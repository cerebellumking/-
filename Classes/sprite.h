#pragma once

#ifndef _sprite_H_
#define _sprite_H_


#include"cocos2d.h"
USING_NS_CC;
//#include"Actor.h"
//#include"Map.h"
//#include"obstruction.h"

class sprite_living :public cocos2d::Sprite//�������
{

public:
	
	//virtual bool init();
	CREATE_FUNC(sprite_living);
	void bind_sprite(Sprite* sprite);                           //�󶨾���,��ʼ������Ľӿ�
	void set_positon(Vec2 pos);                                 //���þ�������,��ʼ������Ľӿ�
	Sprite* get_sprite();                                       //��ȡ����,���þ���Ľӿ�
	int get_hp();                                               //��ȡ�����Ѫ���Ľӿ�
	int get_speed();                                            //��ȡ������ٶȵĽӿ�
	int get_attack();                                           //��ȡ����Ĺ������Ľӿ�
	void set_hp(int hp);                                        //����Ѫ��
	void set_speed(float speed);                                //�����ٶ�
	void set_attack(int attack);                                //���ù�����
	bool if_dead();                                             //�Ƿ�����
	void deduct_hp(int attack);                                 //�����Ѫ
	void set_if_is_attacked(bool if_is_attacked);               //�����Ƿ񱻹�����״̬
	bool get_if_is_attacked();                                  //��ȡ�Ƿ񱻹�����״̬
	//bool if_collided_with_border(map* map);//�Ƿ���߽���ײ
	//bool if_collided_with_obstruction(obstruction* obstruction);//�Ƿ����ϰ�����ײ
	//virtual void death_animation();//������������


	//��������ø�����������棬���ܻ�Ҫ�ټ�һЩ��Ա��

private:
	int hp;                                                      //��ǰ����ֵ
	float speed;                                                 //����
	int attack;                                                  //������
	Sprite* sprite;                                              //����
	bool if_is_attacked;                                         //�ж��Ƿ񱻹���
};

class sprite_dead//�������
{
public:

private:

};

#endif;