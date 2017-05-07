#include <iostream>
#include "Player.h"
#include "BitMask.h"
#include "Logging/logger.h"

Player::Player()
{}

Player::Player(std::string _pathAnim1,
               std::string _pathAnim2,
               std::string _pathAnim3,
               std::string _idleAnimFramesTemplate,
               std::string _moveAnimFramesTemplate,
               std::string _jumpAnimFramesTemplate,
               std::string _deathAnimFramesTemplate,
               std::string _flyingAnimFramesTemplate)
{
    pathAnim1= _pathAnim1;
    pathAnim2= _pathAnim2;
    pathAnim3= _pathAnim3;
    AnimFiles.insert({"Idle",        _idleAnimFramesTemplate});
    AnimFiles.insert({"Move",        _moveAnimFramesTemplate});
    AnimFiles.insert({"Jump",        _jumpAnimFramesTemplate});
    AnimFiles.insert({"Death",       _deathAnimFramesTemplate});
    AnimFiles.insert({"Fly",         _flyingAnimFramesTemplate});
}

Player* Player::create()
{
    Player * player = new Player("player/1/",
                                 "player/2/",
                                 "player/3/",
                                 "idle",
                                 "run",
                                 "jump",
                                 "die",
                                 "jetpack");

//    print_event(__FILE__, __LINE__,"new Player()");
    if (player && player->initWithFile("player/2/idle_001.png"))
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
    CC_SAFE_RELEASE(idleAnimate[0]);
    CC_SAFE_RELEASE(moveAnimate[0]);
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
    change_player = false;
    timer = 0;
    direction = 1;
    speed = 0;
    hp = 100;
//    curr_anim = IDLING;
    amount_of_players = 3;
    curr_player = player2;

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

std::string Player::getFrame( int player_num, std::string &pattern, int number)
{
    if (number < 0 || number >= 100) { throw std::out_of_range("number < 0"); }

    std::string frame;
    switch( player_num ){
        case 0:
            frame = pathAnim1 + pattern;
            break;
        case 1:
            frame = pathAnim2 + pattern;
            break;
        case 2:
            frame = pathAnim3 + pattern;
            break;
    }

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

void Player::changePlayer()
{
    int player_num = rand() % 3 + 1;
    std::cout<< curr_player << ' ';
    if( curr_player != player_num ){
        switch( player_num ){
            case 1:
                curr_player = player1;
                break;
            case 2:
                curr_player = player2;
                break;
            case 3:
                curr_player = player3;
                break;
            default:
                break;
        }

        switch( curr_anim ){
            case IDLING:
                idle();
                break;
            case MOVING:
                move();
                break;
            case JUMPING:
                jump();
                break;
            case DYING:
                die();
                break;
            case JETPACK:
                fly();
                break;
            default:
                break;
        }
        change_player = false;
    }
    else{
        return changePlayer();
    }
    return;
}

void Player::update()
{
//    if( change_player == true ){
//        changePlayer();
//        change_player = false;
//    }
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
    switch( curr_player ){
        case player1:
            this->runAction(RepeatForever::create( moveAnimate[0] ));
            break;
        case player2:

            this->runAction(RepeatForever::create( moveAnimate[1] ));
            break;
        case player3:

            this->runAction(RepeatForever::create( moveAnimate[2] ));
            break;
        default:
            break;
    }

}

void Player::idle()
{
    curr_anim = IDLING;
    this->stopAllActions();
    switch( curr_player ){
        case player1:
            std::cout<<"1";
            this->runAction(RepeatForever::create(idleAnimate[0]));
            break;
        case player2:
            std::cout<<"2";
            this->runAction(RepeatForever::create(idleAnimate[1]));
            break;
        case player3:
            std::cout<<"3";
            this->runAction(RepeatForever::create(idleAnimate[2]));
            break;
        default:
            break;
    }

}

void Player::jump()
{
    curr_anim = JUMPING;
    this->stopAllActions();
    switch( curr_player ){
        case player1:
            this->runAction(RepeatForever::create(jumpAnimate[0]));
            break;
        case player2:
            this->runAction(RepeatForever::create(jumpAnimate[1]));
            break;
        case player3:
            this->runAction(RepeatForever::create(jumpAnimate[2]));
            break;
        default:
            break;
    }

}

void Player::die()
{
    curr_anim = DYING;
    is_idling = false;
    is_moving = false;
    is_jumping = false;
    is_shooting = false;
    this->stopAllActions();
    switch( curr_player ){
        case player1:
            this->runAction(Repeat::create( deathAnimate[0], 1 ));
            break;
        case player2:
            this->runAction(Repeat::create( deathAnimate[1], 1 ));
            break;
        case player3:
            this->runAction(Repeat::create( deathAnimate[2], 1 ));
            break;
        default:
            break;
    }

}

void Player::fly()
{
    curr_anim = JETPACK;
    this->stopAllActions();
    switch( curr_player ){
        case player1:
            this->runAction(RepeatForever::create( flyingAnimate[0] ));
            break;
        case player2:
            this->runAction(RepeatForever::create( flyingAnimate[1] ));
            break;
        case player3:
            this->runAction(RepeatForever::create( flyingAnimate[2] ));
            break;
        default:
            break;
    }

}
