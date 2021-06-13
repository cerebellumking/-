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

	void knight::set_speed_y(float speed);
	void knight::set_speed_x(float speed);
	void knight::set_E_check(bool check);

	/*ʩ�첩�޸ĵ�knight*/
	int get_hp();                                         //��ȡhp
	void deduct_hp(int attack);                           //��ʿ��Ѫ
	bool if_dead();                                       //�����ж�
	void set_if_is_attacked(bool if_is_attacked);         //�����Ƿ񱻹�����״̬
	bool get_if_is_attacked();                            //��ȡ�Ƿ񱻹�����״̬
	void recover_armor(int delta_armor);                  //�ظ�����
	bool if_armor_max();                                  //�Ƿ�������
	int get_armor();                                      //��ȡ��ǰ�Ļ���
	weapon* Weapon;
private:
	int HP, max_HP, armor, max_armor, MP, max_MP, gold;
	float knight_speed_x, knight_speed_y;
	bool E_pressed_check;
	bool if_is_attacked;
	
};
#endif
