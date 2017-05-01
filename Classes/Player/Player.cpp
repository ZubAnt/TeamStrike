#include <iostream>
#include "Player.h"
#include "BitMask.h"
#include "Logging/logger.h"

Player::Player()
{}

Player::Player(std::string _pathAnim,
               std::string _idleAnimFramesTemplate,
               std::string _moveAnimFramesTemplate,
               std::string _move_fireAnimFramesTemplate,
               std::string _jumpAnimFramesTemplate,
               std::string _deathAnimFramesTemplate,
               std::string _flyingAnimFramesTemplate,
               std::string _shootingAnimFramesTemplate,
               std::string _stay_with_gunAnimFramesTemplate,
               std::string _jump_fireAnimFramesTemplate)
{
    pathAnim = _pathAnim;
    AnimFiles.insert({"Idle",        _idleAnimFramesTemplate});
    AnimFiles.insert({"Move",        _moveAnimFramesTemplate});
    AnimFiles.insert({"MoveGun",     _move_fireAnimFramesTemplate});
    AnimFiles.insert({"Jump",        _jumpAnimFramesTemplate});
    AnimFiles.insert({"Death",       _deathAnimFramesTemplate});
    AnimFiles.insert({"Fly",         _flyingAnimFramesTemplate});
    AnimFiles.insert({"Shoot",       _shootingAnimFramesTemplate});
    AnimFiles.insert({"StayGun",     _stay_with_gunAnimFramesTemplate});
    AnimFiles.insert({"JumpGun",     _jump_fireAnimFramesTemplate});
}

Player* Player::create()
{
    print_event(__FILE__, __LINE__," in create()");
    Player * player = new Player("player/1/",
                                 "idle",
                                 "run",
                                 "run_with_gun",
                                 "jump",
                                 "die",
                                 "jetpack",
                                 "shot",
                                 "idle_with_gun",
                                 "jump_with_gun");
    print_event(__FILE__, __LINE__,"new Player()");
    if (player && player->initWithFile("player/1/idle_000.png"))
    {

        player->autorelease();
        print_event(__FILE__, __LINE__,"in if");
        bool initplayer = player->initOptions();
        if (initplayer == false)
        {
           return nullptr;
        }
        return player;
    }

    CC_SAFE_DELETE(player);
    return nullptr;
}

Player::~Player()
{
    CC_SAFE_RELEASE(idleAnimate);
    CC_SAFE_RELEASE(moveAnimate);
}


bool Player::initOptions()
{
    is_moving = false;
    is_jumping = true;
    is_idling = false;
    is_onGround = false;

    is_dying = false;
    is_moving = false;
    is_jumping = false;
    is_idling = true;
    is_shooting = false;
    is_onGround = false;
    is_onJetpack = false;
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

void Player::move()
{
    curr_anim = MOVING;
    this->stopAllActions();
    this->runAction(RepeatForever::create( moveAnimate ));
}

void Player::run_fire()
{
    curr_anim = RUN_GUN;
    this->stopAllActions();
    this->runAction(RepeatForever::create(moveGunAnimate));
}

void Player::idle()
{
    curr_anim = IDLING;
    this->stopAllActions();
    this->runAction(RepeatForever::create(idleAnimate));
}

void Player::jump()
{
    curr_anim = JUMPING;
    this->stopAllActions();
    this->runAction(RepeatForever::create(jumpAnimate));
}

void Player::jump_fire()
{
    curr_anim = JUMP_GUN;
    this->stopAllActions();
    this->runAction(RepeatForever::create(jumpGunAnimate));
}

void Player::die()
{
    curr_anim = DYING;
    is_idling = false;
    is_moving = false;
    is_jumping = false;
    is_shooting = false;
    this->stopAllActions();
    this->runAction(RepeatForever::create( deathAnimate ));
}

void Player::shoot()
{
    curr_anim = STAY_SHOOT;
    this->stopAllActions();
    this->runAction(RepeatForever::create( shootingAnimate ));
}

void Player::stay_with_gun()
{
    curr_anim = STAY_GUN;
    this->stopAllActions();
    this->runAction(RepeatForever::create( stayGunAnimate ));
}

void Player::fly()
{
    curr_anim = JATPACK;
    this->stopAllActions();
    this->runAction(RepeatForever::create( flyingAnimate ));
}

void Player::update()
{
    if( false == is_onJetpack ) {

        if (true == is_dying) {
            if (curr_anim != DYING) {
                die();
            }
            return;
        }

        if (false == is_jumping && false == is_moving) {
            if( curr_anim != STAY_SHOOT && true == is_onGround && true == is_shooting ){
                shoot();
            }
            else if(  curr_anim != STAY_GUN && true == is_onGround && false == is_shooting && timer < 250 )
            {
                stay_with_gun();
            }
            else if( curr_anim != IDLING && true == is_onGround && false == is_shooting && timer >= 250 ) {
                    idle();
            }
        }

        if (is_moving)
        {
            if (true == is_onGround) {
                speed = SPEED_OF_THE_PLAYER;
            } else {
                speed = SPEED_OF_THE_PLAYER_IN_THE_AIR;
            }
            if (direction == 0)
            {
                this->setScaleX(-1);
                this->setPositionX(this->getPositionX() - speed);
            } else
            {
                this->setScaleX(1);
                this->setPositionX(this->getPositionX() + speed);
            }

            if (true == is_onGround && false == is_jumping &&
                    false == is_shooting && curr_anim != RUN_GUN && timer < 250 )
            {
                run_fire();
            }
            else if (true == is_onGround && false == is_jumping &&
                     false == is_shooting && curr_anim != MOVING && timer >= 250)
            {
                move();
            }
            else if (true == is_onGround && false == is_jumping && true == is_shooting && curr_anim != RUN_GUN )
            {
                run_fire();
            }
        }

        if (is_jumping)
        {
            if ( curr_anim != JUMP_GUN && true == is_shooting)
            {
                jump_fire();
            }
            if ( curr_anim != JUMP_GUN && false == is_shooting && timer < 250 )
            {
                jump_fire();
            }
            if (true == is_onGround)
            {
                if ( curr_anim != JUMPING && false == is_shooting && timer >= 250 )
                {
                    jump();
                }
                else if ( curr_anim != JUMP_GUN && false == is_shooting && timer < 250 )
                {
                    jump_fire();
                }
                Vec2 body_velocity = this->getPhysicsBody()->getVelocity();
                body_velocity.y = 450;
                this->getPhysicsBody()->setVelocity(body_velocity);
                is_onGround = false;
            }
        }
        if ( is_onGround == false && curr_anim != JUMP_GUN && timer < 250 ){
            jump_fire();
        }
    }
    else
    {
        if( true == is_onGround && curr_anim != IDLING )
        {
            curr_anim = IDLING;
            idle();
        }
        else if( false == is_onGround && curr_anim != JATPACK )
        {
            fly();
        }
        if (is_moving) {

            if (direction == 0) {
                this->setScaleX(-1);
                this->setPositionX( this->getPositionX() - 1.3 * SPEED_OF_THE_PLAYER );
            } else {
                this->setScaleX(1);
                this->setPositionX( this->getPositionX() + 1.3 * SPEED_OF_THE_PLAYER );
            }
        }
        if( is_jumping )
        {
            Vec2 body_velocity = this->getPhysicsBody()->getVelocity();
            body_velocity.y = 450;
            is_onGround = false;
            this->getPhysicsBody()->setVelocity(body_velocity);
        }
    }
    ++timer;
}
