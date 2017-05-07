//
// Created by nyam on 07.05.17.
//

#ifndef TEAMSTRIKE_CHARACTER_H
#define TEAMSTRIKE_CHARACTER_H
#include "cocos2d.h"
USING_NS_CC;
#include <unordered_map>
#include <string>
#include <vector>

class Character: public cocos2d::Sprite  {
public:

    Character();
//    Character(std::string _pathAnim,
//            std::string _idleAnimFramesTemplate,
//            std::string _moveAnimFramesTemplate,
//            std::string _jumpAnimFramesTemplate,
//            std::string _deathAnimFramesTemplate,
//            std::string _flyingAnimFramesTemplate
//    );

    virtual ~Character();

    virtual void update() = 0;
    virtual void move();
    virtual void jump();
    virtual void idle();
    virtual void die();
    virtual void fly();

    bool is_moving;
    bool is_jumping;
    bool is_idling;
    bool is_shooting;
    bool is_dying;
    bool is_onJetpack;
    bool is_onGround;
    bool is_collisionPlatform_On;

    bool collision_right_platform;
    bool collision_left_platform;

    unsigned int timer;
    int direction;
    float speed;
    int hp = 100;
//    bool key_A;
//    bool key_D;

protected:
    Animate* idleAnimate;
    Animate* moveAnimate;
    Animate* jumpAnimate;
    Animate* deathAnimate;
    Animate* flyingAnimate;

    std::string pathAnim;

    std::unordered_map<std::string, std::string> AnimFiles;

    enum current_animation
    {
        IDLING,
        MOVING,
        JUMPING,
        DYING,
        JETPACK
    } curr_anim;

    bool initOptions();

    virtual void initPhysicsPody() = 0;

    bool initAnimFrames();
    std::string getFrame(std::string &pattern, int number);

    virtual void initIdleAnimate() = 0;
    virtual void initMoveAnimate() = 0;
    virtual void initJumpAnimate() = 0;
    virtual void initDeathAnimate() = 0;
    virtual void initFlyingAnimate() = 0;
};

#endif //TEAMSTRIKE_CHARACTER_H
