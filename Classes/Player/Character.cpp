//
// Created by nyam on 07.05.17.
//

#include "Character.h"
#include <iostream>
#include "BitMask.h"
#include "Logging/logger.h"

Character::Character()
{}

//Character::Character(std::string _pathAnim,
//               std::string _idleAnimFramesTemplate,
//               std::string _moveAnimFramesTemplate,
//               std::string _jumpAnimFramesTemplate,
//               std::string _deathAnimFramesTemplate,
//               std::string _flyingAnimFramesTemplate)
//{
//    pathAnim = _pathAnim;
//    AnimFiles.insert({"Idle",        _idleAnimFramesTemplate});
//    AnimFiles.insert({"Move",        _moveAnimFramesTemplate});
//    AnimFiles.insert({"Jump",        _jumpAnimFramesTemplate});
//    AnimFiles.insert({"Death",       _deathAnimFramesTemplate});
//    AnimFiles.insert({"Fly",         _flyingAnimFramesTemplate});
//}

Character::~Character()
{
    CC_SAFE_RELEASE(idleAnimate);
    CC_SAFE_RELEASE(moveAnimate);
}

bool Character::initAnimFrames()
{
    try
    {
        initIdleAnimate();
        initMoveAnimate();
        initJumpAnimate();
        initDeathAnimate();
        initFlyingAnimate();
    }
    catch(std::out_of_range &err)
    {
        print_error(__FILE__, __LINE__, err.what());
        log_error(__FILE__, __LINE__, err.what());
        return false;
    }
    catch(std::invalid_argument &err)
    {
        print_error(__FILE__, __LINE__, err.what());
        log_error(__FILE__, __LINE__, err.what());
        return false;
    }
    catch(std::bad_alloc &err)
    {
        print_error(__FILE__, __LINE__, err.what());
        log_error(__FILE__, __LINE__, err.what());
        return false;
    }
    return true;
}

std::string Character::getFrame(std::string &pattern, int number)
{
    if (number < 0 || number >= 100) { throw std::out_of_range("number < 0"); }

    std::string frame = pathAnim + pattern;
    std::string format = ".png";
    std::string prefix("_00");
    char number_str[4] = {0, 0, 0};

    if (number >= 10)
    {
        prefix = "_0";
    }

    sprintf(number_str, "%i", number);
    frame += prefix + number_str + format;

    return frame;
}

bool Character::initOptions()
{
    is_dying = false;
    is_moving = false;
    is_jumping = false;
    is_idling = true;
    is_shooting = false;
    is_onGround = false;
    is_onJetpack = false;
    collision_right_platform = false;
    collision_left_platform = false;
    is_collisionPlatform_On = true;
    timer = 0;
    direction = 1;
    speed = 0;

    initPhysicsPody();
    print_event(__FILE__, __LINE__,"initPhysicsPody()");
    bool initanimate = initAnimFrames();
    if (initanimate == false)
    {
        print_error(__FILE__, __LINE__, "BAD INIT ANIMATE");
    }

    return initanimate;
}

void Character::move()
{
    curr_anim = MOVING;
    this->stopAllActions();
    this->runAction(RepeatForever::create( moveAnimate ));
}

void Character::idle()
{
    curr_anim = IDLING;
    this->stopAllActions();
    this->runAction(RepeatForever::create(idleAnimate));
}

void Character::jump()
{
    curr_anim = JUMPING;
    this->stopAllActions();
    this->runAction(RepeatForever::create(jumpAnimate));
}

void Character::die()
{
    curr_anim = DYING;
    is_idling = false;
    is_moving = false;
    is_jumping = false;
    is_shooting = false;
    this->stopAllActions();
    this->runAction(Repeat::create( deathAnimate, 1 ));
}

void Character::fly()
{
    curr_anim = JETPACK;
    this->stopAllActions();
    this->runAction(RepeatForever::create( flyingAnimate ));
}