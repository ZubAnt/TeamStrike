//
// Created by pavel on 02.04.17.
//

#ifndef TEAMSTRIKE_WARRIOR_H
#define TEAMSTRIKE_WARRIOR_H

#include "cocos2d.h"
USING_NS_CC;

class Warrior : public cocos2d::Sprite {
public:
    Warrior();
    ~Warrior();
    static Warrior* create();

    int GetCurrentHP();
    bool MoveWarrior(const Vec2 direction);
    bool StopWarrior();
    void AddEvents();
    void MakeBoom();
    void InitOptions();

protected:
    int _baseHP;
    int _currentHP;
    Vec2 _movementDirection;
    //bool _rightMove;

};

#endif //TEAMSTRIKE_WARRIOR_H
