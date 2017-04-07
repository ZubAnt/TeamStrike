#include <iostream>
#include "Player.h"

Player* Player::create()
{
    Player * player = new Player();
    if(player && player->initWithFile("player/girl_1/Idle (1).png"))
    {
        player->autorelease();
        player->initOptions();
        return player;
    }

    CC_SAFE_DELETE(player);
    return NULL;
}

Player::~Player()
{
    CC_SAFE_RELEASE(idleAnimate);
    CC_SAFE_RELEASE(moveAnimate);
}

void Player::setPlayerPhysicsBody()
{
    PhysicsBody* physicsBody = PhysicsBody::createBox(Size(86.0f, 100.0f), PhysicsMaterial(0.1f, 1.0f, 0.0f));
//    PhysicsBody* physicsBody = PhysicsBody::createBox(Size(86.0f, 100.0f), PhysicsMaterial(0.0f, 0.0f, 100.0f));
    physicsBody->setRotationEnable(false);
    physicsBody->setContactTestBitmask( true );
    physicsBody->setCollisionBitmask( PLAYER_BITMASK );
    physicsBody->setGravityEnable( true );
    addComponent(physicsBody);
}

void Player::initOptions()
{
    setPlayerPhysicsBody();
    moving = false;
    jumping = true;
    idling = false;
    is_onGround = false;
    char str[100] = {0};

    Vector<SpriteFrame*> idleAnimFrames(10);
    for(int i = 1; i <= 10; i++) //Iterate for the number of images you have
    {
        sprintf(str, "player/girl_1/Idle (%i).png",i);
        auto frame = SpriteFrame::create(str,Rect(0,0, 80, 100)); //The size of the images in an action should be the same
        frame->setAnchorPoint(Vec2(0.5, 0));
        idleAnimFrames.pushBack(frame);
    }

    auto idleAnimation = Animation::createWithSpriteFrames(idleAnimFrames, 0.20f);

    idleAnimate = Animate::create(idleAnimation);
    idleAnimate->retain(); //Retain to use it later

    Vector<SpriteFrame*> moveAnimFrames(8);
    for(int i = 1; i <= 8; i++)
    {
        sprintf(str, "player/girl_1/Run (%i).png",i);
        auto frame = SpriteFrame::create(str, Rect(0,0,80,100));
        frame->setAnchorPoint(Vec2(0.5, 0));
        moveAnimFrames.pushBack(frame);
    }

    auto moveAnimation = Animation::createWithSpriteFrames(moveAnimFrames, 0.09f);
    moveAnimate = Animate::create(moveAnimation);
    moveAnimate->retain();

    Vector<SpriteFrame*> jumpAnimFrames(10);
    for(int i = 1; i <= 10; i++)
    {
        sprintf(str, "player/girl_1/Jump (%i).png",i);
        auto frame = SpriteFrame::create(str,Rect(0,0,80,100));
        frame->setAnchorPoint(Vec2(0.5, 0));
        jumpAnimFrames.pushBack(frame);
    }

    auto jumpAnimation = Animation::createWithSpriteFrames(jumpAnimFrames, 0.3f);
    jumpAnimate = Animate::create(jumpAnimation);
    jumpAnimate->retain();
    this->runAction(RepeatForever::create(jumpAnimate));

}

void Player::move(int directionParam)
{
    if(true == is_onGround )
    {
        idling = false;
        moving = true;
        this->stopAllActions();
        this->runAction(RepeatForever::create(moveAnimate));
        direction = directionParam;
    }
    else
    {
        idling = false;
        moving = true;
        direction = directionParam;
    }
}

void Player::idle()
{
    if(true == is_onGround)
    {
        moving = false;
        jumping = false;
        idling = true;
        this->stopAllActions();
        this->runAction(RepeatForever::create(idleAnimate));
    }
}

void Player::jump()
{
    if( true == is_onGround )
    {
        idling = false;
        jumping = true;
        this->stopAllActions();
        this->runAction(RepeatForever::create(jumpAnimate));
    }
}

void Player::update()
{
    if(idling) {
        if (true == is_onGround) {
            idle();
        }
    }
    if(moving) //check if moving
    {
        int speed = 0;
        if( true == is_onGround)
        {
            speed = SPEED_OF_THE_PLAYER;
        }
        else
        {
            speed = SPEED_OF_THE_PLAYER_IN_THE_AIR;
        }
        if(direction == 0) //check if going left
        {
            this->setScaleX(-1); //flip
            this->setPositionX(this->getPositionX() - speed);
        }
        else
        {
            this->setScaleX(1); //flip
            this->setPositionX(this->getPositionX() + speed);
        }
    }
    if(jumping)
    {
        if(true == is_onGround) {
            Vec2 body_velocity = this->getPhysicsBody()->getVelocity();
            body_velocity.y = 300;
            this->getPhysicsBody()->setVelocity( body_velocity );
            is_onGround = false;
        }
    }
}
