//
// Created by nyam on 07.05.17.
//
#include <iostream>
#include "Enemy.h"
#include "BitMask.h"
#include "Logging/logger.h"



Enemy::Enemy()
{}

Enemy::Enemy(std::string _pathAnim,
               std::string _idleAnimFramesTemplate,
               std::string _moveAnimFramesTemplate,
               std::string _jumpAnimFramesTemplate,
               std::string _deathAnimFramesTemplate,
               std::string _flyingAnimFramesTemplate)
{
    pathAnim1 = _pathAnim;
    AnimFiles.insert({"Idle",        _idleAnimFramesTemplate});
    AnimFiles.insert({"Move",        _moveAnimFramesTemplate});
    AnimFiles.insert({"Jump",        _jumpAnimFramesTemplate});
    AnimFiles.insert({"Death",       _deathAnimFramesTemplate});
    AnimFiles.insert({"Fly",         _flyingAnimFramesTemplate});
}

Enemy* Enemy::create()
{
//    Player * player = new Player();
//    print_event(__FILE__, __LINE__," in create()");
    Enemy * enemy = new Enemy("player/1/",
                                 "idle",
                                 "run",
                                 "jump",
                                 "die",
                                 "jetpack");

//    print_event(__FILE__, __LINE__,"new Player()");
    if (enemy && enemy->initWithFile("player/1/idle_001.png"))
    {

        enemy->autorelease();
//        print_event(__FILE__, __LINE__,"in if");
        bool initplayer = enemy->initOptions();
        if (initplayer == false)
        {
            return nullptr;
        }
        return enemy;
    }

    CC_SAFE_DELETE(enemy);
    return nullptr;
}

Enemy::~Enemy()
{
//    CC_SAFE_RELEASE(idleAnimate1);
//    CC_SAFE_RELEASE(moveAnimate1);
}


bool Enemy::initOptions()
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
    hp = 100;
    amount_of_players = 3;
    curr_player = player1;

    initPhysicsPody();
    print_event(__FILE__, __LINE__,"initPhysicsPody()");
    bool initanimate = initAnimFrames();
    if (initanimate == false)
    {
        print_error(__FILE__, __LINE__, "BAD INIT ANIMATE");
    }

    return initanimate;
}

void Enemy::update()
{
    if( hp <= 0 )
    {
        is_dying = true;
        if (curr_anim != DYING) {
            die();
        }
        return;
    }
}