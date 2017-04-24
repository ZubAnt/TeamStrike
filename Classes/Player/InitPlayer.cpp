#include "Player.h"
#include <stdexcept>
#include <cstdlib>
#include "Logging/logger.h"

void Player::initPhysicsPody()
{
    PlayerBody = PhysicsBody::createBox(Size(70.0f,150.0f), PhysicsMaterial(PLAYER_DENSITY, PLAYER_RESTITUTION, PLAYER_FRICTION));
    PlayerBody->setDynamic(true);
    PlayerBody->setGravityEnable(true);
    PlayerBody->setRotationEnable(false);
    PlayerBody->setContactTestBitmask(true);
    PlayerBody->setCollisionBitmask(PLAYER_BITMASK);
    addComponent(PlayerBody);
}


bool Player::initAnimFrames()
{
    try
    {
        initIdleAnimate();
        initMoveAnimate();
        initMoveGunAnimation();
        initJumpAnimate();
        initDeathAnimate();
        initFlyingAnimate();
        initShootingAnimate();
        initStayGunAnimate();
        initJumpGunAnimate();
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


void Player::initIdleAnimate()
{

    std::string idleAnimTemplate = AnimFiles.at("Idle");

    int numbFrames = 12;
    Vector<SpriteFrame*> idleAnimFrames(numbFrames);

    for(int i = 0; i < numbFrames; ++i)
    {
        std::string frame_str = getFrame(idleAnimTemplate, i);
        SpriteFrame* frame = SpriteFrame::create(frame_str,
                                                 Rect(0,0,69,142)
                                                 );
        if (frame == nullptr)
        {
            std::string err =  "cannot create frame form" + frame_str;
            throw std::invalid_argument(err);
        }
        frame->setAnchorPoint(Vec2(0.5, 0));
        idleAnimFrames.pushBack(frame);

    }

    Animation* idleAnimation = Animation::createWithSpriteFrames(idleAnimFrames, 0.3f);
    idleAnimate = Animate::create(idleAnimation);

    if (idleAnimate == nullptr || idleAnimation == nullptr)
    {
        throw std::invalid_argument("cannot create idleAnimation");
    }

    idleAnimate->retain();
    runAction(RepeatForever::create(idleAnimate));
}

void Player::initMoveAnimate()
{
    std::string moveAnimTemplate = AnimFiles.at("Move");

    int numbFrames = 8;
    Vector<SpriteFrame*> moveAnimFrames(numbFrames);

    for(int i = 0; i < numbFrames; ++i)
    {
        std::string frame_str = getFrame(moveAnimTemplate, i);
        SpriteFrame* frame = SpriteFrame::create(frame_str,
                                                 Rect(0, 0, 79, 149)
                                                 );
        if (frame == nullptr)
        {
            std::string err =  "cannot create frame form" + frame_str;
            throw std::invalid_argument(err);
        }

        frame->setAnchorPoint(Vec2(0.5, 0));
        moveAnimFrames.pushBack(frame);
    }

    Animation* moveAnimation = Animation::createWithSpriteFrames(moveAnimFrames, 0.06f);
    moveAnimate = Animate::create(moveAnimation);

    if (moveAnimate == nullptr || moveAnimation == nullptr)
    {
        throw std::invalid_argument("cannot create moveAnimation");
    }

    moveAnimate->retain();
}

void Player::initMoveGunAnimation()
{
    std::string moveGunAnimTemplate = AnimFiles.at("MoveGun");

    int numbFrames = 8;
    Vector<SpriteFrame*> moveGunAnimFrames(numbFrames);

    for(int i = 0; i < numbFrames; ++i)
    {
        std::string frame_str = getFrame(moveGunAnimTemplate, i);
        SpriteFrame* frame = SpriteFrame::create(frame_str,
                                                 Rect(0, 0, 79, 149)
                                                 );
        if (frame == nullptr)
        {
            std::string err =  "cannot create frame form" + frame_str;
            throw std::invalid_argument(err);
        }

        frame->setAnchorPoint(Vec2(0.5, 0));
        moveGunAnimFrames.pushBack(frame);
    }

    Animation* moveGunAnimation = Animation::createWithSpriteFrames(moveGunAnimFrames, 0.06f);
    moveGunAnimate = Animate::create(moveGunAnimation);

    if (moveAnimate == nullptr || moveGunAnimation == nullptr)
    {
        throw std::invalid_argument("cannot create moveAnimation");
    }

    moveGunAnimate->retain();
}

void Player::initJumpAnimate()
{
    std::string jumpAnimTemplate = AnimFiles.at("Jump");

    int numbFrames = 8;
    Vector<SpriteFrame*> jumpAnimFrames(numbFrames);

    for(int i = 0; i < numbFrames; ++i)
    {
        std::string frame_str = getFrame(jumpAnimTemplate, i);
        SpriteFrame* frame = SpriteFrame::create(frame_str,
                                                 Rect(0, 0, 87, 152)
                                                 );
        if (frame == nullptr)
        {
            std::string err =  "cannot create frame form" + frame_str;
            throw std::invalid_argument(err);
        }

        frame->setAnchorPoint(Vec2(0.5, 0));
        jumpAnimFrames.pushBack(frame);
    }

    auto jumpAnimation = Animation::createWithSpriteFrames(jumpAnimFrames, 0.15f);
    jumpAnimate = Animate::create(jumpAnimation);

    if (jumpAnimate == nullptr || jumpAnimation == nullptr)
    {
        throw std::invalid_argument("cannot create jumpAnimation");
    }

    jumpAnimate->retain();
}

void Player::initDeathAnimate()
{
    std::string deathAnimTemplate = AnimFiles.at("Death");

    int numbFrames = 10;

    Vector<SpriteFrame*> deathAnimFrames(numbFrames);//не забывать менять
    for(int i = 0; i < numbFrames; ++i)
    {

        std::string frame_str = getFrame(deathAnimTemplate, i);
        SpriteFrame* frame = SpriteFrame::create(frame_str,
                                                 Rect(0, 0, 152, 149)
                                                 );
        if (frame == nullptr)
        {
            std::string err =  "cannot create frame form" + frame_str;
            throw std::invalid_argument(err);
        }

        frame->setAnchorPoint(Vec2(0.5, 0));
        deathAnimFrames.pushBack(frame);
    }

    Animation* deathAnimation = Animation::createWithSpriteFrames(deathAnimFrames, 0.3f, 10);
    deathAnimate = Animate::create(deathAnimation);

    if (deathAnimate == nullptr || deathAnimation == nullptr)
    {
        throw std::invalid_argument("cannot create deathAnimation");
    }

    deathAnimate->retain();
}

void Player::initFlyingAnimate()
{
    std::string flyAnimTemplate = AnimFiles.at("Fly");

    int numbFrames = 6;

    Vector<SpriteFrame*> flyingAnimFrames(numbFrames);//не забывать менять
    for(int i = 0; i < numbFrames; ++i)
    {

        std::string frame_str = getFrame(flyAnimTemplate, i);
        SpriteFrame* frame = SpriteFrame::create(frame_str,
                                                 Rect(0, 0, 153, 128)
                                                 );
        if (frame == nullptr)
        {
            std::string err =  "cannot create frame form" + frame_str;
            throw std::invalid_argument(err);
        }

        frame->setAnchorPoint(Vec2(0.5, 0));
        flyingAnimFrames.pushBack(frame);
    }

    Animation* flyingAnimation = Animation::createWithSpriteFrames(flyingAnimFrames, 0.15f, 10);
    flyingAnimate = Animate::create(flyingAnimation);

    if (flyingAnimate == nullptr || flyingAnimation == nullptr)
    {
        throw std::invalid_argument("cannot create flyingAnimation");
    }

    flyingAnimate->retain();
}

void Player::initShootingAnimate()
{
    std::string shootAnimTemplate = AnimFiles.at("Shoot");

    int numbFrames = 4;

    Vector<SpriteFrame*> shootingAnimFrames(numbFrames);
    for(int i = 0; i < numbFrames; ++i)
    {

        std::string frame_str = getFrame(shootAnimTemplate, i);
        SpriteFrame* frame = SpriteFrame::create(frame_str,
                                                 Rect(0, 0, 105, 142)
                                                 );
        if (frame == nullptr)
        {
            std::string err =  "cannot create frame form" + frame_str;
            throw std::invalid_argument(err);
        }

        frame->setAnchorPoint(Vec2(0.5, 0));
        shootingAnimFrames.pushBack(frame);
    }
    auto shootingAnimation = Animation::createWithSpriteFrames(shootingAnimFrames, 0.09f, 10);
    shootingAnimate = Animate::create(shootingAnimation);

    if (shootingAnimate == nullptr || shootingAnimation == nullptr)
    {
        throw std::invalid_argument("cannot create shootingAnimation");
    }

    shootingAnimate->retain();
}

void Player::initStayGunAnimate()
{
    std::string stayGunAnimTemplate = AnimFiles.at("StayGun");

    int numbFrames = 12;

    Vector<SpriteFrame*> stay_with_gunAnimFrames(numbFrames);
    for(int i = 0; i < numbFrames; ++i)
    {

        std::string frame_str = getFrame(stayGunAnimTemplate, i);
        SpriteFrame* frame = SpriteFrame::create(frame_str,
                                                 Rect(0, 0, 86, 142)
                                                 );
        if (frame == nullptr)
        {
            std::string err =  "cannot create frame form" + frame_str;
            throw std::invalid_argument(err);
        }

        frame->setAnchorPoint(Vec2(0.5, 0));
        stay_with_gunAnimFrames.pushBack(frame);
    }
    auto stayGunAnimation = Animation::createWithSpriteFrames(stay_with_gunAnimFrames, 0.2f, 10);
    stayGunAnimate = Animate::create(stayGunAnimation);

    if (stayGunAnimate == nullptr || stayGunAnimation == nullptr)
    {
        throw std::invalid_argument("cannot create stayGunAnimation");
    }

    stayGunAnimate->retain();
}

void Player::initJumpGunAnimate()
{
    std::string jumpGunAnimTemplate = AnimFiles.at("JumpGun");

    int numbFrames = 8;

    Vector<SpriteFrame*> jump_fireAnimFrames(numbFrames);
    for(int i = 0; i < numbFrames; ++i)
    {
        std::string frame_str = getFrame(jumpGunAnimTemplate, i);
        SpriteFrame* frame = SpriteFrame::create(frame_str,
                                                 Rect(0, 0, 90, 152)
                                                 );
        if (frame == nullptr)
        {
            std::string err =  "cannot create frame form" + frame_str;
            throw std::invalid_argument(err);
        }

        frame->setAnchorPoint(Vec2(0.5, 0));
        jump_fireAnimFrames.pushBack(frame);
    }
    auto jumpGunAnimation = Animation::createWithSpriteFrames(jump_fireAnimFrames, 0.15f, 10);
    jumpGunAnimate = Animate::create(jumpGunAnimation);

    if (jumpGunAnimate == nullptr || jumpGunAnimation == nullptr)
    {
        throw std::invalid_argument("cannot create jumpGunAnimation");
    }

    jumpGunAnimate->retain();
}
