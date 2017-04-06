//
// Created by pavel on 07.04.17.
//
#include "Player/Warrior.h"
#include "cocos2d.h"
USING_NS_CC;

#ifndef TEAMSTRIKE_BULLET_H
#define TEAMSTRIKE_BULLET_H


class Bullet : public cocos2d::Sprite {
public:
    static Bullet* create( const Warrior* warrior );
    int getDamage();

private:
    Bullet();
    ~Bullet();

    void initOptions( const Warrior* warrior );
    void addEvents();

private:
    int _damage;
    float _maxSpeed;
    Vec2 _currentSpeed;

};


#endif //TEAMSTRIKE_BULLET_H
