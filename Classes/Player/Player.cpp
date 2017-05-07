#include <iostream>
#include "Player.h"
#include "BitMask.h"
#include "Logging/logger.h"

Player::Player()
{}

Player::Player(std::string _pathAnim,
               std::string _idleAnimFramesTemplate,
               std::string _moveAnimFramesTemplate,
               std::string _jumpAnimFramesTemplate,
               std::string _deathAnimFramesTemplate,
               std::string _flyingAnimFramesTemplate)
{
    pathAnim = _pathAnim;
    AnimFiles.insert({"Idle",        _idleAnimFramesTemplate});
    AnimFiles.insert({"Move",        _moveAnimFramesTemplate});
    AnimFiles.insert({"Jump",        _jumpAnimFramesTemplate});
    AnimFiles.insert({"Death",       _deathAnimFramesTemplate});
    AnimFiles.insert({"Fly",         _flyingAnimFramesTemplate});
}

Player* Player::create()
{
//    Player * player = new Player();
//    print_event(__FILE__, __LINE__," in create()");
    Player * player = new Player("player/1/",
                                 "idle",
                                 "run",
                                 "jump",
                                 "die",
                                 "jetpack");

//    print_event(__FILE__, __LINE__,"new Player()");
    if (player && player->initWithFile("player/1/idle_001.png"))
    {

        player->autorelease();
//        print_event(__FILE__, __LINE__,"in if");
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

    initPhysicsPody();
    print_event(__FILE__, __LINE__,"initPhysicsPody()");
    bool initanimate = initAnimFrames();
    if (initanimate == false)
    {
        print_error(__FILE__, __LINE__, "BAD INIT ANIMATE");
    }

    return initanimate;
}


bool Player::initAnimFrames()
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

std::string Player::getFrame(std::string &pattern, int number)
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

void Player::update()
{

//    if( false == is_onJetpack ) {

        if (true == is_dying) {
            if (curr_anim != DYING) {
                die();
            }
            return;
        }

        if (false == is_jumping && false == is_moving) {

            if( curr_anim != IDLING && true == is_onGround ) {
                    idle();
            }
        }

        if (is_moving)
        {
            float speed2 = 0;
            speed = 0;
            if (true == is_onGround) {

                speed = SPEED_OF_THE_PLAYER;
                speed2 = SPEED_OF_THE_PLAYER_VELOCITY;
            } else {
                speed = SPEED_OF_THE_PLAYER_IN_THE_AIR;
                speed2 = SPEED_OF_THE_PLAYER_IN_THE_AIR_VELOCITY;
            }
            if (direction == 0 && collision_left_platform == false )
            {
                this->setScaleX(-1);
                Vec2 body_velocity = this->getPhysicsBody()->getVelocity();
                body_velocity.x = -speed2;
                this->getPhysicsBody()->setVelocity( body_velocity );
            }
             if ( direction == 1 && collision_right_platform == false )
            {
                this->setScaleX(1);
                Vec2 body_velocity = this->getPhysicsBody()->getVelocity();
                body_velocity.x = speed2;
                this->getPhysicsBody()->setVelocity( body_velocity );
            }

            if (true == is_onGround && false == is_jumping &&
                    curr_anim != MOVING )
            {
                move();
            }
        }

        if (is_jumping)
        {
            if ( curr_anim != JUMPING )
            {
                jump();
            }

            if (true == is_onGround)
            {
//                Vec2 body_velocity = this->getPhysicsBody()->getVelocity();
//                body_velocity.y = 3.000;
//                this->getPhysicsBody()->setVelocity( body_velocity );
                this->getPhysicsBody()->applyImpulse( Vec2(0, 400));
//                is_onGround = false;
            }
        }
//    }
//    else
//    {
//        if( true == is_onGround && curr_anim != IDLING )
//        {
//            curr_anim = IDLING;
//            idle();
//        }
//        else if( false == is_onGround && curr_anim != JATPACK )
//        {
//            fly();
//        }
//        if (is_moving) {
//
//            if (direction == 0) {
//                this->setScaleX(-1);
//                this->setPositionX( this->getPositionX() - 1.3 * SPEED_OF_THE_PLAYER );
//            } else {
//                this->setScaleX(1);
//                this->setPositionX( this->getPositionX() + 1.3 * SPEED_OF_THE_PLAYER );
//            }
//        }
//        if( is_jumping )
//        {
//            Vec2 body_velocity = this->getPhysicsBody()->getVelocity();
//            body_velocity.y = 450;
//            is_onGround = false;
//            this->getPhysicsBody()->setVelocity(body_velocity);
//        }
//    }
    ++timer;
}


void Player::move()
{
    curr_anim = MOVING;
    this->stopAllActions();
    this->runAction(RepeatForever::create( moveAnimate ));
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

void Player::die()
{
    curr_anim = DYING;
    is_idling = false;
    is_moving = false;
    is_jumping = false;
    is_shooting = false;
    this->stopAllActions();
    this->runAction(Repeat::create( deathAnimate, 1 ));
}

void Player::fly()
{
    curr_anim = JETPACK;
    this->stopAllActions();
    this->runAction(RepeatForever::create( flyingAnimate ));
}
