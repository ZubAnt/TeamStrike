#ifndef TEAMSTRIKE_BULLET_H
#define TEAMSTRIKE_BULLET_H

#define BULLET_COLLISION_BITMASK 0x000004
#define kMaximumBulletSpeed 200.0f;
#define kDefaultDamage 10;

#include "Player/Player.h"
#include "cocos2d.h"
USING_NS_CC;

class Bullet : public cocos2d::Sprite {
public:
    static Bullet* create(const Player* player);
    int getDamage();

private:
    bool life;
    int _damage;
    float _maxSpeed;
    Vec2 _currentSpeed;

    Bullet();
    ~Bullet();
    void initOptions(const Player* player);
};


#endif //TEAMSTRIKE_BULLET_H
