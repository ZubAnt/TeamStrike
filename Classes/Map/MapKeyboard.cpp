#include "Map.h"
#include "Player/Player.h"
#include "Bullet/Bullet.h"

//void MapScene::update(float delta)
//{
//    player->update();
//}


//bool MapScene::onContactBegin(PhysicsContact &contact)
//{
//    PhysicsBody *a = contact.getShapeA( )->getBody();
//    PhysicsBody *b = contact.getShapeB( )->getBody();

//    if ( ( PLAYER_BITMASK == a->getCollisionBitmask() && GROUND_BITMASK == b->getCollisionBitmask() ) ||
//         ( PLAYER_BITMASK == b->getCollisionBitmask() && GROUND_BITMASK == a->getCollisionBitmask() ) )
//    {
//        player->is_onGround = true;
//        player->is_jumping = false;
//        if(false == player->is_moving)
//        {
//            player->is_idling = true;
//        }
//        else
//        {
//            player->is_moving = true;
//        }
//    }

//    return true;
//}


//void MapScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event)
//{
//    switch (keyCode) {
//    case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
//    case cocos2d::EventKeyboard::KeyCode::KEY_A:
//        player->move(0);
//        break;
//    case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
//    case cocos2d::EventKeyboard::KeyCode::KEY_D:
//        player->move(1);
//        break;
//    case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
//    case cocos2d::EventKeyboard::KeyCode::KEY_W:
//        player->jump();
//        break;
//    case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
//    case cocos2d::EventKeyboard::KeyCode::KEY_S:
//        break;
//    default:
//        player->idle();
//        break;
//    }
//}


//void MapScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event)
//{
//    switch (keyCode) {
//    case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
//    case cocos2d::EventKeyboard::KeyCode::KEY_A:
//        if(true == player->is_onGround)
//        {
//            player->is_moving = false;
//            player->is_jumping = false;
//            player->is_idling = true;
//        }
//        else
//        {
//            player->is_moving = false;
//            player->is_jumping = true;
//            player->is_idling = false;
//        }
//        break;
//    case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
//    case cocos2d::EventKeyboard::KeyCode::KEY_D:
//        if(true == player->is_onGround)
//        {
//            player->is_moving = false;
//            player->is_jumping = false;
//            player->is_idling = true;
//        }
//        else
//        {
//            player->is_moving = false;
//            player->is_jumping = true;
//            player->is_idling = false;
//        }
//        break;
//    case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
//    case cocos2d::EventKeyboard::KeyCode::KEY_W:
//        if(true == player->is_moving )
//        {
//            player->is_jumping = false;
//            player->is_idling = false;
//        }
//        else
//        {
//            player->is_jumping = false;
//            player->is_idling = true;
//        }
//        break;
//    case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
//    case cocos2d::EventKeyboard::KeyCode::KEY_S:
//        break;
//    default:
//        break;
//    }
//}


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

    if ((PLAYER_BITMASK == a->getCollisionBitmask() && GROUND_BITMASK == b->getCollisionBitmask()) ||
        (PLAYER_BITMASK == b->getCollisionBitmask() && GROUND_BITMASK == a->getCollisionBitmask()))
    {
        player->is_onGround = true;
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

