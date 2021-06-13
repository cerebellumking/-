#include "safeScene.h"
#include"cocos2d.h"
#include"InitialScene.h"

float volume2 = 0.2;
float volume3 = 0.5;
int id_2;
int id_3;


Scene* safe_scene::createWithPhysics()
{
	return safe_scene::create();
}

bool safe_scene::init()
{
	if (!Scene::initWithPhysics())
	{
		return false;
	}

	//

	if (!Scene::init())
		return false;
	//enemy enemy_;


	id_2 = AudioEngine::play2d("1bgm.mp3", true, volume2);


	auto safe_map = Sprite::create("windows//safemap1.jpg");
	auto layer = Layer::create();
	auto visibleSize = Director::getInstance()->getWinSize();       //��������ߴ�
	Vec2 origin = Director::getInstance()->getVisibleOrigin();          //���������������
	if (safe_map == nullptr);
	else {
		safe_map->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		addChild(safe_map, 1, 0);
		safe_map->addChild(layer, 1, 122);
	}
	auto return_to_home = MenuItemImage::create("windows\\return initial.jpg", "windows\\return initial1.jpg", CC_CALLBACK_1(safe_scene::menuReturnCallback, this));


	if (return_to_home == nullptr ||return_to_home->getContentSize().width <= 0 ||return_to_home->getContentSize().height <= 0)
	{
		return false;
	}
	else
	{
		float x = origin.x + return_to_home->getContentSize().width / 2;
		float y = origin.y + return_to_home->getContentSize().height / 2;
		return_to_home->setPosition(Vec2(x, y));

	}
	auto menu = Menu::create(return_to_home, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);


	auto upItem = MenuItemImage::create("windows\\up.png", "windows\\up1.png", CC_CALLBACK_1(safe_scene::menuCloseCallback4, this));

	if (upItem == nullptr ||
		upItem->getContentSize().width <= 0 ||
		upItem->getContentSize().height <= 0)
	{
		return false;
	}
	else
	{
		float x = origin.x + return_to_home->getContentSize().width / 2 + 100;
		float y = origin.y + return_to_home->getContentSize().height / 2;
		upItem->setPosition(Vec2(x, y));

	}
	auto menu4 = Menu::create(upItem, NULL);
	menu4->setPosition(Vec2::ZERO);
	this->addChild(menu4, 1);



	auto downItem = MenuItemImage::create("windows\\down.png", "windows\\down1.png", CC_CALLBACK_1(safe_scene::menuCloseCallback5, this));

	if (downItem == nullptr ||
		downItem->getContentSize().width <= 0 ||
		downItem->getContentSize().height <= 0)
	{
		return false;
	}
	else
	{
		float x = origin.x + return_to_home->getContentSize().width / 2 + 200;
		float y = origin.y + return_to_home->getContentSize().height / 2;
		downItem->setPosition(Vec2(x, y));

	}
	auto menu5 = Menu::create(downItem, NULL);
	menu5->setPosition(Vec2::ZERO);
	this->addChild(menu5, 1);


	//��ͣ����

	auto stopItem = MenuItemImage::create("windows\\down.png", "windows\\down1.png", CC_CALLBACK_1(safe_scene::menuCloseCallback_stop, this));

	if (stopItem == nullptr ||
		stopItem->getContentSize().width <= 0 ||
		stopItem->getContentSize().height <= 0)
	{
		return false;
	}
	else
	{
		float x = origin.x + return_to_home->getContentSize().width / 2 + 300;
		float y = origin.y + return_to_home->getContentSize().height / 2;
		stopItem->setPosition(Vec2(x, y));

	}
	auto menu_stop = Menu::create(stopItem, NULL);
	menu_stop->setPosition(Vec2::ZERO);
	this->addChild(menu_stop, 1);


	auto goItem = MenuItemImage::create("windows\\down.png", "windows\\down1.png", CC_CALLBACK_1(safe_scene::menuCloseCallback_go, this));

	if (goItem == nullptr ||
		goItem->getContentSize().width <= 0 ||
		goItem->getContentSize().height <= 0)
	{
		return false;
	}
	else
	{
		float x = origin.x + return_to_home->getContentSize().width / 2 + 400;
		float y = origin.y + return_to_home->getContentSize().height / 2;
		goItem->setPosition(Vec2(x, y));

	}
	auto menu_go = Menu::create(goItem, NULL);
	menu_go->setPosition(Vec2::ZERO);
	this->addChild(menu_go, 1);


	/*���ĸ�������г�ʼ�� byʩ�첩*/
	enemy_1.init();
	layer->addChild(enemy_1.get_sprite());

	enemy_2.init();
	layer->addChild(enemy_2.get_sprite(),2);

	enemy_3.init();
	layer->addChild(enemy_3.get_sprite(),2);
	
	enemy_4.init();
	layer->addChild(enemy_4.get_sprite());


	/*��ʿ���� by�����*/
	Knight = knight::create("knight.png");
	Knight->setPosition(Vec2(visibleSize.width / 2 , visibleSize.height / 2 ));
	Knight->init();
	layer->addChild(Knight, 2);
	Knight->weapon_init();
	create_unpicked_weapon(Vec2(400, 400), "M2.png", "M2 bullet.png");


	/*��ʱ������*/
	schedule(CC_SCHEDULE_SELECTOR(safe_scene::update),1/60);                   //��ʿ��һϵ�ж���   ������ƶ�

	schedule(CC_SCHEDULE_SELECTOR(safe_scene::update_knight_fire), 0.4);

	schedule(CC_SCHEDULE_SELECTOR(safe_scene::update_remote), 1);              //Զ�ֹ̹����ļ�ʱ��    

	schedule(CC_SCHEDULE_SELECTOR(safe_scene::update_if_recover_armor), 4);    //�ж���ʿ�Ƿ�ָ����׵ļ�ʱ��
	return true;
}

void safe_scene::update(float dt)
{
	/*��ʿ�ƶ���������ǹ�Ĳ��� by�����*/
	Knight->keyboard_event();
	if (Knight->get_speed_x() < 0)
	{
		Knight->runAction(FlipX::create(true));
		Knight->Weapon->runAction(FlipX::create(true));
	}
	if (Knight->get_speed_x() > 0)
	{
		Knight->runAction(FlipX::create(false));
		Knight->Weapon->runAction(FlipX::create(false));
	}
	



	auto move = MoveBy::create(0.2, Vec2(10 * Knight->get_speed_x(), 10 * Knight->get_speed_y()));
	Knight->runAction(move);
	if (Knight->get_E_check())
	{
		gun_switch();
	}


	/*�����ƶ��Ĳ��� byʩ�첩
	����˼·��1���ж������Ƿ�����
	          2��δ�������ж��Ƿ�ӽ���ʿ
			  3�������ӽ�������ε� ����Ҫ�ӽ���ʿ ��ս�ֵ���move������������ƶ���ˢ�����꣬��Ϊ�ε�����ʼλ��
	*/
	if (!enemy_2.if_dead()) {
		if (enemy_2.if_close_to_actor(Knight))
		{
			enemy_2.move(Knight);
			enemy_2.set_enemy_pos();
		}
		else
			enemy_2.wander();
	}
	if (!enemy_3.if_dead()) {
		if (enemy_3.if_close_to_actor(Knight))
		{
			enemy_3.set_enemy_pos();
		}
		else
			enemy_3.wander();
	}
	

	
	
}
void safe_scene::update_knight_fire(float dt)
{
	Knight->Weapon->fire();
	if (Knight->Weapon->get_click_check())
	{
		fire_bullet();
		Knight->Weapon->set_click_check(false);
	}
}
/*Զ�ֹ̹��� ��ʱ��*/
void safe_scene::update_remote(float dt)
{
	if (!enemy_3.if_dead()) {
		if (enemy_3.if_attack(Knight)) {
			enemy_3.attack(Knight);
			this->addChild(enemy_3.get_bullet(), 5, 10);
			schedule(CC_SCHEDULE_SELECTOR(safe_scene::update_bullet), 1 / 60);
		}
	}
	if (!enemy_4.if_dead()) {
		if (enemy_4.if_attack(Knight)) {
			enemy_4.attack(Knight);
			this->addChild(enemy_4.get_bullet(), 5);
			schedule(CC_SCHEDULE_SELECTOR(safe_scene::update_bullet), 1 / 60);
		}
	}
}

/*
          ��update_remote����
          Զ�ֹ̹��� ����ʿ����
*/
void safe_scene::update_bullet(float dt)
{
	if (!enemy_3.if_dead()) {
		if (enemy_3.if_collide(Knight, enemy_3.get_bullet())) {
			enemy_3.get_bullet()->setVisible(false);
			Knight->deduct_hp(enemy_3.get_attack());
			Knight->set_if_is_attacked(true);
			enemy_3.set_attack(0);
		}
	}
	if (!enemy_4.if_dead()) {
		if (enemy_4.if_collide(Knight, enemy_4.get_bullet())) {
			enemy_4.get_bullet()->setVisible(false);
			Knight->deduct_hp(enemy_4.get_attack());
			Knight->set_if_is_attacked(true);
			enemy_4.set_attack(0);
		}
	}
	/*�ж���ʿ�Ƿ�����*/
	if (Knight->if_dead()) {
		Knight->setVisible(false);
		Director::getInstance()->popScene();
	}
}
/*�ж���ʿ�Ƿ�ָ�����*/
void safe_scene::update_if_recover_armor(float dt)
{
	if (!Knight->get_if_is_attacked() && !Knight->if_armor_max()) {
		schedule(CC_SCHEDULE_SELECTOR(safe_scene::update_recover_armor), 1);
	}
	else
		unschedule(CC_SCHEDULE_SELECTOR(safe_scene::update_recover_armor));
	Knight->set_if_is_attacked(false);
}

/*��ʿ�ָ�����*/
void safe_scene::update_recover_armor(float dt)
{
	Knight->recover_armor(1);
}
/*��ʿ���ӵ��Թֵ�Ч������firebullet�б�����*/
void safe_scene::update_bullet_to_enemy(float dt)
{
	if (!enemy_3.if_dead()) {
		if (enemy_3.if_collide(Knight->Weapon->get_bullet(), enemy_3.get_sprite())) {
			Knight->Weapon->get_bullet()->setVisible(false);
			enemy_3.deduct_hp(Knight->Weapon->get_bullet_demage());
			CCLOG("%d", enemy_3.get_hp());
			Knight->Weapon->set_demage(0);
		}
	}
	else{
		enemy_3.get_sprite()->setVisible(false);
	}
	if (!enemy_4.if_dead()) {
		if (enemy_4.if_collide(Knight->Weapon->get_bullet(), enemy_4.get_sprite())) {
			Knight->Weapon->get_bullet()->setVisible(false);
			enemy_4.deduct_hp(Knight->Weapon->get_bullet_demage());
			CCLOG("%d", enemy_4.get_hp());
			Knight->Weapon->set_demage(0);
		}
	}
	else {
		enemy_4.get_sprite()->setVisible(false);
	}
}


void safe_scene::delete_bullet()
{
	if (Knight->Weapon->get_pos().x < -1 * Director::getInstance()->getVisibleSize().width / 2 || Knight->Weapon->get_pos().x < -1 * Director::getInstance()->getVisibleSize().height / 2
		|| Knight->Weapon->get_pos().x > 1 * Director::getInstance()->getVisibleSize().width / 2 || Knight->Weapon->get_pos().x > 1 * Director::getInstance()->getVisibleSize().height / 2)
	{
		this->removeChild(Knight->Weapon->get_bullet(), 1);
	}
}

void safe_scene::fire_bullet()
{
	Knight->Weapon->set_bullet(Sprite::create(Knight->Weapon->get_bullet_name()));


	/*��仰�ǳ���Ҫ ��Ҫʵ�ָ��ݵ�ǰ�����������ù�����   ��Ҫ�޸�!!!!!!!*/
	Knight->Weapon->set_demage(Knight->Weapon->get_original_demage());
	/*ʩ�첩������ʿ�ӵ������ײ���޸�*/
	schedule(CC_SCHEDULE_SELECTOR(safe_scene::update_bullet_to_enemy), 1/60);


	if (Knight->isFlippedX())
	{
		Knight->Weapon->get_bullet()->setPosition(Knight->getPosition().x - 40, Knight->getPosition().y - 10);
	}
	else
	{
		Knight->Weapon->get_bullet()->setPosition(Knight->getPosition().x + 40, Knight->getPosition().y - 10);
	}
	this->addChild(Knight->Weapon->get_bullet(), 2);
	float rad = atan2(Knight->Weapon->get_pos().x, Knight->Weapon->get_pos().y);
	float degree = CC_RADIANS_TO_DEGREES(rad);
	auto rotate = RotateTo::create(0.001, degree - 90);
	float delta = sqrt(Knight->Weapon->get_pos().x * Knight->Weapon->get_pos().x + Knight->Weapon->get_pos().y * Knight->Weapon->get_pos().y);
	auto bullet_move = MoveBy::create(100 / Knight->Weapon->get_bullet_speed(), Vec2(600000 * Knight->Weapon->get_pos().x/delta, 600000 * Knight->Weapon->get_pos().y/delta));
	auto action = Sequence::create(rotate, bullet_move, NULL);
	Knight->Weapon->get_bullet()->runAction(action);
	id_3 = AudioEngine::play2d("fire1.mp3", false, volume3);

}

void safe_scene::menuReturnCallback(cocos2d::Ref* pSender)
{
	AudioEngine::stop(id_2);
	Director::getInstance()->popScene();
}

void safe_scene::menuCloseCallback4(cocos2d::Ref* pSender)
{
	if (volume2 < 0.4f) {
		volume2 = volume2 + 0.1;
		AudioEngine::setVolume(id_2, volume2);
	}
	if (volume3 < 1.0f) {
		volume3 = volume3 + 0.25;
		AudioEngine::setVolume(id_3, volume3);
	}
}

void safe_scene::menuCloseCallback5(cocos2d::Ref* pSender)
{
	if (volume2 > 0.f) {
		volume2 = volume2 - 0.1;
		AudioEngine::setVolume(id_2, volume2);
	}
	if (volume3 > 0.f) {
		volume3 = volume3 - 0.25;
		AudioEngine::setVolume(id_3, volume3);
	}

}



void safe_scene::menuCloseCallback_stop(cocos2d::Ref* psender)
{

	auto size = Director::getInstance()->getWinSize();
	Director::getInstance()->stopAnimation();

}

void safe_scene::menuCloseCallback_go(cocos2d::Ref* psender)
{

	//  auto size = Director::getInstance()->getWinSize();

	//   auto layer_stop = LayerColor::create(Color4B(0, 255, 0, 120), 200, 200);
	//   this->addChild(layer_stop, 2);
	Director::getInstance()->startAnimation();

	//   this->removeChild(layer_stop, 2);
}



void safe_scene::create_unpicked_weapon(Vec2 pos, std::string name, std::string bulllet_name)
{
	const char* c1 = name.c_str();
	const char* c2 = bulllet_name.c_str();

	weapon_map[pos] = weapon::create(c1);
	weapon_map[pos]->setPosition(pos);
	weapon_map[pos]->set_bullet_name(c2);
	weapon_map[pos]->set_weapon_name(c1);

	if (c1 == "M2.png")
	{
		weapon_map[pos]->set_demage(7);
		weapon_map[pos]->set_bullet_cost(1);
	}
	else if (c1 == "OldPistal.png")
	{
		weapon_map[pos]->set_demage(5);
		weapon_map[pos]->set_bullet_cost(0);
	}
	addChild(weapon_map[pos],10);
}

void safe_scene::delete_picked_weapon(Vec2 pos)
{
	if (weapon_map[pos] != nullptr)
	{
		removeChild(weapon_map[pos]);
	}
}

std::map<Vec2, weapon*> safe_scene::get_weapon_map()
{
	return weapon_map;
}

void safe_scene::gun_switch()
{

	Knight->set_E_check(false);
	Vec2 Knight_pos = Knight->getPosition();
	std::map<Vec2, weapon*>::iterator iter;
	for (iter = weapon_map.begin(); iter != weapon_map.end(); iter++)
	{
		if (sqrt(pow((iter->first.x - Knight_pos.x), 2) + pow((iter->first.y - Knight_pos.y), 2)) <= 200)
		{
			weapon* Knight_weapon = Knight->Weapon;
			create_unpicked_weapon(Knight_pos, Knight_weapon->get_weapon_name(), Knight_weapon->get_bullet_name());
			Knight->removeChild(Knight->Weapon, 1);
			// Knight->weapon_init();
			Knight->picked_weapon_init(iter->second->get_weapon_name(), iter->second->get_bullet_name(), iter->second->get_bullet_demage(), iter->second->get_bullet_cost());
			delete_picked_weapon(iter->first);
			weapon_map.erase(iter);
			CCLOG("%d", weapon_map.size());
			break;

		}
	}
}
