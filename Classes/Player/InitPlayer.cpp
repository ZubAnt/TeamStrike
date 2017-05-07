#include "Player.h"
#include <stdexcept>
#include <cstdlib>
#include "BitMask.h"
#include "Logging/logger.h"

void Player::initPhysicsPody() {
    auto PlayerBody = PhysicsBody::createBox(Size(70.0f, 121.0f),
                                             PhysicsMaterial(PLAYER_DENSITY, PLAYER_RESTITUTION, PLAYER_FRICTION));
    PlayerBody->PhysicsBody::setMass(0.1f);
    PlayerBody->setDynamic(true);
    PlayerBody->setVelocityLimit(SPEED_PLAYER_LIMIT);
    PlayerBody->setGravityEnable(true);
    PlayerBody->setRotationEnable(false);
    PlayerBody->setContactTestBitmask(true);
    PlayerBody->setCollisionBitmask(BitMask::PLAYER);
    addComponent(PlayerBody);
}

void Player::initAllAnimations( current_player player )
{
    current_player temp = curr_player;//запомнили который установлен
    curr_player = player;//установим нового потому что с ним аботают методы ниже
    switch( curr_player ){
        case player1:
            print_event(__FILE__, __LINE__,"initPhysicsPody()");
            initIdleAnimate(PLAYER1_INDEX);
            print_event(__FILE__, __LINE__,"initPhysicsPody()");
            initMoveAnimate(PLAYER1_INDEX);
            initJumpAnimate(PLAYER1_INDEX);
            initDeathAnimate(PLAYER1_INDEX);
            initFlyingAnimate(PLAYER1_INDEX);
            break;
        case player2:
            initIdleAnimate(PLAYER2_INDEX);
            initMoveAnimate(PLAYER2_INDEX);
            initJumpAnimate(PLAYER2_INDEX);
            initDeathAnimate(PLAYER2_INDEX);
            initFlyingAnimate(PLAYER2_INDEX);
            break;
        case player3:
            initIdleAnimate(PLAYER3_INDEX);
            initMoveAnimate(PLAYER3_INDEX);
            initJumpAnimate(PLAYER3_INDEX);
            initDeathAnimate(PLAYER3_INDEX);
            initFlyingAnimate(PLAYER3_INDEX);
            break;
        default:
            break;
    }
    curr_player = temp;//обратно
    print_event(__FILE__, __LINE__,"initPhysicsPody()");
}

void Player::initIdleAnimate( int PLAYER_INDEX )
{
    std::string idleAnimTemplate = AnimFiles.at("Idle");
    int numbFrames = 12;
    Vector<SpriteFrame *> idleAnimFrames(numbFrames);

    for (int i = 1; i <= numbFrames; ++i) {
        std::string frame_str = getFrame(idleAnimTemplate, i);
        SpriteFrame *frame = SpriteFrame::create(frame_str,
                                                 Rect(0, 0, 74, 121)
        );
        if (frame == nullptr) {
            std::string err = "cannot create frame form" + frame_str;
            throw std::invalid_argument(err);
        }
        frame->setAnchorPoint(Vec2(0.5, 0));
        idleAnimFrames.pushBack(frame);
    }
    Animation* idleAnimation = Animation::createWithSpriteFrames(idleAnimFrames, 0.3f);

    animations[PLAYER_INDEX].push_back( Animate::create(idleAnimation) );

    if (animations[PLAYER_INDEX][IDLE_ANIMATION_INDEX] == nullptr || idleAnimation == nullptr)
    {
        throw std::invalid_argument("cannot create idleAnimation");
    }

    animations[PLAYER_INDEX][IDLE_ANIMATION_INDEX]->retain();
}

void Player::initMoveAnimate( int PLAYER_INDEX )
{
    std::string moveAnimTemplate = AnimFiles.at("Move");
    int numbFrames = 8;
    Vector<SpriteFrame*> moveAnimFrames(numbFrames);

    for (int i = 1; i <= numbFrames; ++i) {
        std::string frame_str = getFrame(moveAnimTemplate, i);
        SpriteFrame *frame = SpriteFrame::create(frame_str,
                                                 Rect(0, 0, 70, 126)
        );
        if (frame == nullptr) {
            std::string err = "cannot create frame form" + frame_str;
            throw std::invalid_argument(err);
        }

        frame->setAnchorPoint(Vec2(0.5, 0));
        moveAnimFrames.pushBack(frame);
    }

    Animation* moveAnimation = Animation::createWithSpriteFrames(moveAnimFrames, 0.3f);
    animations[PLAYER_INDEX].push_back( Animate::create(moveAnimation) );

    if (animations[PLAYER_INDEX][MOVE_ANIMATION_INDEX] == nullptr || moveAnimation == nullptr)
    {
        throw std::invalid_argument("cannot create idleAnimation");
    }
    animations[PLAYER_INDEX][MOVE_ANIMATION_INDEX]->retain();
}

void Player::initJumpAnimate( int PLAYER_INDEX )
{
    std::string jumpAnimTemplate = AnimFiles.at("Jump");
    int numbFrames = 8;
    Vector<SpriteFrame*> jumpAnimFrames(numbFrames);


    for (int i = 1; i <= numbFrames; ++i) {
        std::string frame_str = getFrame(jumpAnimTemplate, i);
        SpriteFrame *frame = SpriteFrame::create(frame_str,
                                                 Rect(0, 0, 95, 130)
        );
        if (frame == nullptr) {
            std::string err = "cannot create frame form" + frame_str;
            throw std::invalid_argument(err);
        }

        frame->setAnchorPoint(Vec2(0.5, 0));
        jumpAnimFrames.pushBack(frame);
    }

    Animation* jumpAnimation = Animation::createWithSpriteFrames(jumpAnimFrames, 0.3f);
    animations[PLAYER_INDEX].push_back( Animate::create(jumpAnimation) );

    if (animations[PLAYER_INDEX][JUMP_ANIMATION_INDEX] == nullptr || jumpAnimation == nullptr)
    {
        throw std::invalid_argument("cannot create idleAnimation");
    }
    animations[PLAYER_INDEX][JUMP_ANIMATION_INDEX]->retain();
}

void Player::initDeathAnimate( int PLAYER_INDEX )
{
    std::string deathAnimTemplate = AnimFiles.at("Death");
    int numbFrames = 10;
    Vector<SpriteFrame*> deathAnimFrames(numbFrames);//не забывать менять

    for (int i = 1; i <= numbFrames; ++i) {

        std::string frame_str = getFrame(deathAnimTemplate, i);
        SpriteFrame *frame = SpriteFrame::create(frame_str,
                                                 Rect(0, 0, 187, 139)
        );
        if (frame == nullptr) {
            std::string err = "cannot create frame form" + frame_str;
            throw std::invalid_argument(err);
        }

        frame->setAnchorPoint(Vec2(0.5, 0));
        deathAnimFrames.pushBack(frame);
    }

    Animation* deathAnimation = Animation::createWithSpriteFrames(deathAnimFrames, 0.3f);
    animations[PLAYER_INDEX].push_back( Animate::create(deathAnimation) );

    if (animations[PLAYER_INDEX][DEATH_ANIMATION_INDEX] == nullptr || deathAnimation == nullptr)
    {
        throw std::invalid_argument("cannot create idleAnimation");
    }
    animations[PLAYER_INDEX][DEATH_ANIMATION_INDEX]->retain();
}

void Player::initFlyingAnimate( int PLAYER_INDEX )
{
    std::string flyAnimTemplate = AnimFiles.at("Fly");
    int numbFrames = 6;
    Vector<SpriteFrame*> flyingAnimFrames(numbFrames);//не забывать менять

    for (int i = 0; i < numbFrames; ++i) {

        std::string frame_str = getFrame(flyAnimTemplate, i);
        SpriteFrame *frame = SpriteFrame::create(frame_str,
                                                 Rect(0, 0, 153, 128)
        );
        if (frame == nullptr) {
            std::string err = "cannot create frame form" + frame_str;
            throw std::invalid_argument(err);
        }

        frame->setAnchorPoint(Vec2(0.5, 0));
        flyingAnimFrames.pushBack(frame);
    }

    Animation* flyAnimation = Animation::createWithSpriteFrames(flyingAnimFrames, 0.3f);
    animations[PLAYER_INDEX].push_back( Animate::create(flyAnimation) );

    if (animations[PLAYER_INDEX][FLY_ANIMATION_INDEX] == nullptr || flyAnimation == nullptr)
    {
        throw std::invalid_argument("cannot create idleAnimation");
    }
    animations[PLAYER_INDEX][FLY_ANIMATION_INDEX]->retain();
}
