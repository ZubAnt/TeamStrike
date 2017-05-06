#ifndef TEAMSTRIKE_BULLET_H
#define TEAMSTRIKE_BULLET_H

#define BULLET_DEFAULT_DAMAGE 10;
#define BULLET_VELOCITY 2000.0f
//#define BULLET_VELOCITY 1500.0f

#include "Player/Player.h"
#include "cocos2d.h"
USING_NS_CC;

class Bullet : public cocos2d::Sprite {
public:
    static Bullet* create(const Player* player);
    int getDamage();
    void increment_cnt_life();
    int cnt_life();
    bool isEqual(Node *node);

private:
    bool life;
    int _Damage;
    int _cnt_life;
    float _Velocity;
    Vec2 _currentSpeed;

    Bullet();
    ~Bullet();
    void initOptions(const Player* player);
};


#endif //TEAMSTRIKE_BULLET_H
