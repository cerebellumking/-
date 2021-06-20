#ifndef _KNIGHT_H_
#define  _KNIGHT_H_
#include "weapon.h"
#include "cocos2d.h"
#include"sprite.h"
USING_NS_CC;

class knight : public sprite_living
{
public:
	static	knight* knight::create(const char* picFileName);
	bool knight::init();
	void knight::keyboard_event();
	bool knight::weapon_init();
	bool knight::picked_weapon_init(std::string name, std::string bulllet_name, int demage, int cost);

	float knight::get_speed_x();
	float knight::get_speed_y();
	bool knight::get_E_check();
	//���첹���ͼ��𲹸� �����***********************************************************************************************************
	bool knight::get_Q_check();
	//���첹���ͼ��𲹸� �����***********************************************************************************************************
	int knight::get_max_hp();
	int knight::get_sheild();
	int knight::get_max_sheild();
	int knight::get_max_mp();
	int knight::get_mp();
	bool knight::get_if_get_add_attack_speed_buff();
	bool knight::get_if_get_arrmor_buff();
	bool knight::get_if_get_recover_mp_buff();

	void knight::set_speed_y(float speed);
	void knight::set_speed_x(float speed);
	void knight::set_E_check(bool check);
	//���첹���ͼ��𲹸� �����***********************************************************************************************************
	void knight::set_Q_check(bool check);
	//���첹���ͼ��𲹸� �����***********************************************************************************************************
	void knight::set_mp(int mp);
	void knight::set_max_hp(int hp);
	void knight::set_max_mp(int hp);
	void knight::set_if_get_add_attack_speed_buff(bool buff);
	void knight::set_if_get_arrmor_buff(bool buf);
	void knight::set_if_get_recover_mp_buff(bool buff);

	/*ʩ�첩�޸ĵ�knight*/
	int get_hp();                                         //��ȡhp
	void deduct_hp(int attack);                           //��ʿ��Ѫ
	bool if_dead();                                       //�����ж�
	void set_if_is_attacked(bool if_is_attacked);         //�����Ƿ񱻹�����״̬
	bool get_if_is_attacked();                            //��ȡ�Ƿ񱻹�����״̬
	void recover_armor(int delta_armor);                  //�ظ�����
	bool if_armor_max();                                  //�Ƿ�������
	int get_armor();                                      //��ȡ��ǰ�Ļ���
	void set_hp(int hp);
	void set_max_armor(int armor);
	void weapon_init(std::string weapon_name, std::string bullet_name, int damage, int mp_cost);
	weapon* Weapon;
private:
	int HP, max_HP, armor, max_armor, MP, max_MP, gold;
	float knight_speed_x, knight_speed_y;
	bool E_pressed_check;
	//���첹���ͼ��𲹸� �����***********************************************************************************************************
	bool Q_pressed_check;
	//���첹���ͼ��𲹸� �����***********************************************************************************************************
	bool if_is_attacked;
	bool if_get_add_attack_speed_buff;
	bool if_get_arrmor_buff;
	bool if_get_recover_mp_buff;
	
};
#endif
