#include "Map.h"
#include "Player/Player.h"
#include "Bullet/Bullet.h"


void MapScene::update(float dt)
{

    player->update();
    if (true == player->is_shooting && player->timer % 10 == 0)
    {
        Bullet* bulllet = Bullet::create(player);
        bullets.push_back(bulllet);
        addChild(bulllet);
    }
}

void MapScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode) {
    case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
    case cocos2d::EventKeyboard::KeyCode::KEY_A:
        player->is_moving = true;
        player->direction = 0;
        player->key_A = true;
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
    case cocos2d::EventKeyboard::KeyCode::KEY_D:
        player->is_moving = true;
        player->direction = 1;
        player->key_D = true;
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
    case cocos2d::EventKeyboard::KeyCode::KEY_W:
        player->is_jumping = true;
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
    case cocos2d::EventKeyboard::KeyCode::KEY_S:

        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_U:
        player->is_dying = true;
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_O:
        player->is_onJetpack = true;
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_P:
        player->is_onJetpack = false;
        break;
    default:
        break;
    }
}

void MapScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode) {

    case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
    case cocos2d::EventKeyboard::KeyCode::KEY_A:
        player->key_A = false;
        if( false == player->key_D ){
            player->is_moving = false;
        }
        else{
            player->direction = 1;
        }
        if( false == player->is_jumping && false == player->is_moving ){
            player->is_idling = true;
        }
        break;

    case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
    case cocos2d::EventKeyboard::KeyCode::KEY_D:
        player->key_D = false;
        if( false == player->key_A ){
            player->is_moving = false;
        }
        else{
            player->direction = 0;
        }
        if( false == player->is_jumping && false == player->is_moving ){
            player->is_idling = true;
        }
        break;

    case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
    case cocos2d::EventKeyboard::KeyCode::KEY_W:
        player->is_jumping = false;
        break;

    case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
    case cocos2d::EventKeyboard::KeyCode::KEY_S:
        break;

    default:
        break;
    }
}

bool MapScene::onContactBegin( cocos2d::PhysicsContact &contact)
{
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();

    if ((BitMask::PLAYER == a->getCollisionBitmask() && BitMask::GROUND == b->getCollisionBitmask()) ||
        (BitMask::PLAYER == b->getCollisionBitmask() && BitMask::GROUND == a->getCollisionBitmask()))
    {
        player->is_onGround = true;
        return true;
    }
//
//    if ((BitMask::PLAYER == a->getCollisionBitmask() && BitMask::PLATFORMS == b->getCollisionBitmask()))
//    {
//        std::cout << "player: " << a->getPosition().y << ' ';
//        std::cout << "plat: " << b->getPosition().y << ' ';
//        if( a->getPosition().y >= b->getPosition().y )
//        {
//            player->is_onGround = true;
//            return true;
//        }
//        else
//        {
//            return false;
//        }
//    }
//    if( (BitMask::PLAYER == b->getCollisionBitmask() && BitMask::PLATFORMS == a->getCollisionBitmask()))
//    {
//        std::cout << "player: " << b->getPosition().y << ' ';
//        std::cout << "plat: " << a->getPosition().y << ' ';
//        if( b->getPosition().y >= a->getPosition().y )
//        {
//            player->is_onGround = true;
//            return true;
//        }
//        else
//        {
//            return false;
//        }
//    }
//        ||

    if ((BitMask::PLAYER == a->getCollisionBitmask() && BitMask::PLATFORMS == b->getCollisionBitmask()) ||
        (BitMask::PLAYER == b->getCollisionBitmask() && BitMask::PLATFORMS == a->getCollisionBitmask()))
    {
        Vec2 vel = player->getPhysicsBody()->getVelocity();
        if( vel.y <= 0 ){
//        if( player->getPhysicsBody()->getPosition().y >= )
            player->is_onGround = true;
//            player->collision = true;
            return true;
        }
        else{
            return false;
        }
    }

    if ((BitMask::PLAYER == a->getCollisionBitmask() && BitMask::StartCOLUMN == b->getCollisionBitmask()) ||
        (BitMask::PLAYER == b->getCollisionBitmask() && BitMask::StartCOLUMN == a->getCollisionBitmask()))
    {
        player->collision = true;
        return true;
    }

    return true;
}

bool MapScene::onContactPreSolve( cocos2d::PhysicsContact &contact)
{
    return true;
}

bool MapScene::onContactPostSolve(cocos2d::PhysicsContact &contact)
{
}

bool MapScene::onContactSeparate(cocos2d::PhysicsContact &contact)
{
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();

    if ((BitMask::PLAYER == a->getCollisionBitmask() && BitMask::GROUND == b->getCollisionBitmask()) ||
        (BitMask::PLAYER == b->getCollisionBitmask() && BitMask::GROUND == a->getCollisionBitmask()))
    {
        player->is_onGround = false;
    }

    if ((BitMask::PLAYER == a->getCollisionBitmask() && BitMask::PLATFORMS == b->getCollisionBitmask()) ||
        (BitMask::PLAYER == b->getCollisionBitmask() && BitMask::PLATFORMS == a->getCollisionBitmask()))
    {
        if( player->is_onGround == true )
        {
            player->is_onGround = false;
        }
    }
    if ((BitMask::PLAYER == a->getCollisionBitmask() && BitMask::StartCOLUMN == b->getCollisionBitmask()) ||
        (BitMask::PLAYER == b->getCollisionBitmask() && BitMask::StartCOLUMN == a->getCollisionBitmask()))
    {
        player->collision = false;
    }

    return true;
}

void MapScene::onMouseUp(Event *event)
{
    player->is_shooting = false;
    player->timer = 0;
}

void MapScene::onMouseDown(Event *event)
{
    player->is_shooting = true;
}

