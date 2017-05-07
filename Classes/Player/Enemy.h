//
// Created by nyam on 07.05.17.
//

#ifndef TEAMSTRIKE_ENEMY_H
#define TEAMSTRIKE_ENEMY_H
#include "cocos2d.h"
#include "Character.h"
USING_NS_CC;

#include <unordered_map>
#include <string>
#include <vector>
#define SPEED_PLAYER_LIMIT 2700.0f
#define PLAYER_DENSITY 500.0f
#define PLAYER_RESTITUTION 0.0000001f
#define PLAYER_FRICTION 1.0f

class Enemy: public Character {
public:

    Enemy();
    Enemy(std::string _pathAnim,
           std::string _idleAnimFramesTemplate,
           std::string _moveAnimFramesTemplate,
           std::string _jumpAnimFramesTemplate,
           std::string _deathAnimFramesTemplate,
           std::string _flyingAnimFramesTemplate
    );

    static Enemy* create();
    ~Enemy();

    void update();

protected:
    bool initOptions();

    void initPhysicsPody();

    void initIdleAnimate();
    void initMoveAnimate();
    void initJumpAnimate();
    void initDeathAnimate();
    void initFlyingAnimate();
};

#endif //TEAMSTRIKE_ENEMY_H
