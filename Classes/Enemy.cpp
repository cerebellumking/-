#include"Enemy.h"
#include<cmath>
/*������Ұ*/
void enemy::set_sight_distance(float sight_distance)
{
	this->sight_distance = sight_distance;
}

/*���ù�������*/
void enemy::set_attack_distance(float attack_distance)
{
	this->attack_distance = attack_distance;
}
/*��ȡ��������ʿ֮���ֱ�߾���*/
float enemy::get_distance(knight* Knight)
{
	float delta = sqrt(get_distancex(Knight) * get_distancex(Knight) + get_distancey(Knight) * get_distancey(Knight));
	return delta;
}

/*��ȡ��������ʿ֮���x�᷽�����*/
float enemy::get_distancex(knight* Knight)
{
	float delta_x = static_cast<float>((Knight->getPosition().x - get_sprite()->getPositionX()));
	return delta_x;
}
/*��ȡ��������ʿ֮���y�᷽�����*/
float enemy::get_distancey(knight* Knight)
{
	float delta_y = static_cast<float>((Knight->getPosition().y- get_sprite()->getPositionY()));
	return delta_y;
}
/*�ж��Ƿ�Ҫ������ʿ*/
bool enemy::if_close_to_actor(knight* Knight)
{
	if (get_distance(Knight) <= sight_distance)
		return true;
	return false;
}
/*�ж��Ƿ񹥻�*/
bool enemy::if_attack(knight* Knight)
{
	if (get_distance(Knight) <= attack_distance)
		return true;
	return false;
}
/*��ȡ����λ�ã�����Ѳ��ʱ�̶���ʼλ��*/
Vec2 enemy::get_enemy_pos()
{
	return enemy_pos;
}
/*���ù���λ�ã�����ˢ�¹���λ��*/
void enemy::set_enemy_pos()
{
	enemy_pos = get_sprite()->getPosition();

}


/*��������ʿ�ƶ��ĺ���*/
void enemy::move(knight* Knight)
{
	if(get_distancex(Knight)<0)
		get_sprite()->runAction(FlipX::create(true));
	else
		get_sprite()->runAction(FlipX::create(false));
	auto move = MoveBy::create(1/60, Vec2(get_speed()*get_distancex(Knight)/get_distance(Knight),get_speed()*get_distancey(Knight) / get_distance(Knight)));
	get_sprite()->runAction(move);
}
/*δ������ʿʱ ��������ǻ�*/
void enemy::wander()
{
	static Vec2 initial_pos = get_enemy_pos();
	initial_pos = get_enemy_pos();
	srand(unsigned(time(nullptr)));
	float wander_distance = 40;
	float boundary_x1 = initial_pos.x + 80;
	float boundary_x2 = initial_pos.x - 80;
	float boundary_y1 = initial_pos.y + 80;
	float boundary_y2 = initial_pos.y - 80;
	int direction = rand() % 3+1;//����һ���������޹涨����
	float rate_x = static_cast<float>(rand()%90+10)/100;
	//CCLOG("%f", &rate_x);
	float rate_y = sqrt(1 - rate_x * rate_x);
	
	float delta_x=0, delta_y=0;
	switch (direction) {
		case 1:
			delta_x=  wander_distance*  rate_x;
			delta_y = wander_distance * rate_y;
			break;
		case 2:
			delta_x = -wander_distance * rate_x;
			delta_y = wander_distance * rate_y;
			break;
		case 3:
			delta_x = -wander_distance * rate_x;
			delta_y = -wander_distance * rate_y;
			break;
		case 4:
			delta_x = wander_distance * rate_x;
			delta_y = -wander_distance * rate_y;
			break;
		default:
			break;
	}
	auto move = MoveBy::create(1 / 60, Vec2(delta_x/60, delta_y/60));
	if (get_sprite()->getPositionX() + delta_x <= boundary_x1 && get_sprite()->getPositionX() + delta_x >= boundary_x2 ) {
		if (get_sprite()->getPositionY() + delta_y <= boundary_y1 && get_sprite()->getPositionY() + delta_y >= boundary_y2)
			get_sprite()->runAction(move);
			
	}

}

bool enemy::if_collide(knight* Knight, Sprite* bullet)
{
	Rect knight_=Rect(Knight->getPositionX()-Knight->getContentSize().width/2, Knight->getPositionY() - Knight->getContentSize().height/2 ,Knight->getContentSize().width, Knight->getContentSize().height);
	Rect bullet_ = Rect(bullet->getPositionX() -bullet->getContentSize().width/2, bullet->getPositionY() - bullet->getContentSize().height/2, bullet->getContentSize().width, bullet->getContentSize().height);
	return knight_.intersectsRect(bullet_);
}

bool enemy::if_collide(Sprite* enemy_, Sprite* bullet)
{
	Rect enemy__ = Rect(enemy_->getPositionX() - enemy_->getContentSize().width / 2, enemy_->getPositionY() - enemy_->getContentSize().height / 2, enemy_->getContentSize().width, enemy_->getContentSize().height);
	Rect bullet_ = Rect(bullet->getPositionX() - bullet->getContentSize().width / 2, bullet->getPositionY() - bullet->getContentSize().height / 2, bullet->getContentSize().width, bullet->getContentSize().height);
	return enemy__.intersectsRect(bullet_);
}




/*��ս����1�ĳ�ʼ��*/
bool enemy_melee1::init()
{
	set_attack(1);
	set_hp(10);
	set_speed(2.1);
	set_attack_distance(30);
	set_sight_distance(300);
	bind_sprite(Sprite::create("enemy\\melee1.png"));
	set_positon(Vec2(300,200));
	return true;
}

/*��ս����2�ĳ�ʼ��*/
bool enemy_melee2::init()
{
	set_attack(1);
	set_hp(10);
	set_speed(2.1);
	set_attack_distance(30);
	set_sight_distance(300);
	bind_sprite(Sprite::create("enemy\\melee2.png"));
	set_positon(Vec2(500, 400));
	set_enemy_pos();
	return true;
}



/*Զ�̹�1�ĳ�ʼ��*/
bool enemy_remote1::init()
{
	set_attack(1);
	set_hp(7);
	set_speed(2.1);
	set_attack_distance(700);
	set_sight_distance(700);
	bind_sprite(Sprite::create("enemy\\remote1.png"));
	set_positon(Vec2(100, 600));
	bullet = Sprite::create("enemy\\bullet1.png");
	bullet->setPosition(get_sprite()->getPosition());
	return true;
}

/*Զ�̹�1�Ĺ���*/
void enemy_remote1::attack(knight* Knight)
{
	set_attack(1);
	bullet = Sprite::create("enemy\\bullet1.png");
	bullet->setPosition(get_sprite()->getPosition());
	float delta_x = get_distancex(Knight);
	float delta_y = get_distancey(Knight);
	float delta = get_distance(Knight);
	bullet->setRotation(-static_cast<float>(atan2(delta_y, delta_x) * 180 / M_PI));
	auto move = MoveBy::create(1.3, Vec2(1100 * delta_x/delta, 1100 * delta_y/delta));
	bullet->runAction(move);
	
}
void enemy_remote1::remove_bullet()
{
	bullet->removeFromParent();
}
/*Զ�̹�2�ĳ�ʼ��*/
bool enemy_remote2::init()
{
	set_attack(1);
	set_hp(7);
	set_speed(2.1);
	set_attack_distance(500);
	set_sight_distance(500);
	bind_sprite(Sprite::create("enemy\\remote2.png"));
	set_positon(Vec2(700, 400));
	bullet = Sprite::create("enemy\\bullet2.png");
	bullet->setPosition(get_sprite()->getPosition());
	return true;
}
/*Զ�̹�2�Ĺ���*/
void enemy_remote2::attack(knight* Knight)
{
	set_attack(1);
	bullet = Sprite::create("enemy\\bullet2.png");
	bullet->setPosition(get_sprite()->getPosition());
	float delta_x = get_distancex(Knight);
	float delta_y = get_distancey(Knight);
	float delta = get_distance(Knight);
	bullet->setRotation(-static_cast<float>(atan2(delta_y, delta_x) * 180 / M_PI));
	auto move = MoveBy::create(1.3, Vec2(1100 * delta_x / delta, 1100 * delta_y / delta));
	bullet->runAction(move);
}



/*��ȡ�ӵ�*/
Sprite* enemy_remote1::get_bullet()
{
	return this->bullet;
}

Sprite* enemy_remote2::get_bullet()
{
	return this->bullet;
}
