#include "Map.h"
#include "Player/Player.h"
#include "Bullet/Bullet.h"
#include "Logging/logger.h"


static void increment_life_all_bullet(std::list<Bullet*> &list_bullets)
{
    for(auto &it: list_bullets)
    {
        it->increment_cnt_life();
    }
}

void MapScene::update(float dt)
{

    player->update();

    size_t size_list_bullet = list_bullets.size();

    if (true == player->is_shooting && player->timer % 10 == 0)
    {
        if(size_list_bullet > 0)
        {
            increment_life_all_bullet(list_bullets);
            Bullet *back = list_bullets.back();
            if(back->cnt_life() > MAX_CNT_LIFE_BULLET)
            {
                back->removeFromParent();
                list_bullets.pop_back();
            }
        }

        Bullet* bulllet = Bullet::create(player);
        list_bullets.push_front(bulllet);
        addChild(bulllet);

    }
    else if (size_list_bullet != 0 && false == player->is_shooting &&  player->timer % 10 == 0)
    {
        increment_life_all_bullet(list_bullets);
        Bullet *back = list_bullets.back();
        if(back->cnt_life() > MAX_CNT_LIFE_BULLET)
        {
            back->removeFromParent();
            list_bullets.pop_back();
        }
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

    if (BitMask::BULLET == a->getCollisionBitmask() && BitMask::PLAYER != b->getCollisionBitmask())
    {
        Node *node = a->getNode();

        for(auto ptr_bullet_iter = list_bullets.begin();
            ptr_bullet_iter != list_bullets.end();
            ptr_bullet_iter++)
        {
            if((*ptr_bullet_iter)->isEqual(node))
            {
                list_bullets.erase(ptr_bullet_iter);
                break;
            }
        }
        node->removeFromParent();

        return true;
    }
    else if (BitMask::BULLET == b->getCollisionBitmask() && BitMask::PLAYER != a->getCollisionBitmask())
    {
        Node *node = b->getNode();

        for(auto ptr_bullet_iter = list_bullets.begin();
            ptr_bullet_iter != list_bullets.end();
            ptr_bullet_iter++)
        {
            if((*ptr_bullet_iter)->isEqual(node))
            {
                list_bullets.erase(ptr_bullet_iter);
                break;
            }
        }
        node->removeFromParent();
        return true;
    }
    else if ((BitMask::PLAYER == a->getCollisionBitmask() && BitMask::BORDER == b->getCollisionBitmask()) ||
            (BitMask::PLAYER == b->getCollisionBitmask() && BitMask::BORDER == a->getCollisionBitmask()))
    {
        player->is_collisionPlatform_On = false;
        return false;
    }
    else if ((BitMask::PLAYER == a->getCollisionBitmask() && BitMask::GROUND == b->getCollisionBitmask()) ||
            (BitMask::PLAYER == b->getCollisionBitmask() && BitMask::GROUND == a->getCollisionBitmask()))
    {
        player->is_onGround = true;
        return true;
    }

    else if ((BitMask::PLAYER == a->getCollisionBitmask() && BitMask::PLATFORMS == b->getCollisionBitmask()) ||
            (BitMask::PLAYER == b->getCollisionBitmask() && BitMask::PLATFORMS == a->getCollisionBitmask()))
    {
        Vec2 vel = player->getPhysicsBody()->getVelocity();
        if( vel.y <= 0 )
        {
            if(player->is_collisionPlatform_On == true)
            {
                player->is_onGround = true;
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }

    else if ((BitMask::PLAYER == a->getCollisionBitmask() && BitMask::START_LEFT_COL == b->getCollisionBitmask()) ||
            (BitMask::PLAYER == b->getCollisionBitmask() && BitMask::START_LEFT_COL == a->getCollisionBitmask()))
    {
        //        player->collision = true;
        return true;
    }
    return true;
}

bool MapScene::onContactPreSolve( cocos2d::PhysicsContact &contact)
{
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();

    if ((BitMask::PLAYER == a->getCollisionBitmask() && BitMask::GROUND == b->getCollisionBitmask()) ||
        (BitMask::PLAYER == b->getCollisionBitmask() && BitMask::GROUND == a->getCollisionBitmask()))
    {
        player->is_onGround = true;
    }

    return true;
}

bool MapScene::onContactPostSolve(cocos2d::PhysicsContact &contact)
{
    return true;
}

bool MapScene::onContactSeparate(cocos2d::PhysicsContact &contact)
{
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();

    if ((BitMask::PLAYER == a->getCollisionBitmask() && BitMask::BORDER == b->getCollisionBitmask()) ||
            (BitMask::PLAYER == b->getCollisionBitmask() && BitMask::BORDER == a->getCollisionBitmask()))
    {
        player->is_collisionPlatform_On = true;
    }

    else if ((BitMask::PLAYER == a->getCollisionBitmask() && BitMask::GROUND == b->getCollisionBitmask()) ||
            (BitMask::PLAYER == b->getCollisionBitmask() && BitMask::GROUND == a->getCollisionBitmask()))
    {
        player->is_onGround = false;
    }

    else if ((BitMask::PLAYER == a->getCollisionBitmask() && BitMask::PLATFORMS == b->getCollisionBitmask()) ||
            (BitMask::PLAYER == b->getCollisionBitmask() && BitMask::PLATFORMS == a->getCollisionBitmask()))
    {
        if( player->is_onGround == true )
        {
            player->is_onGround = false;
        }
    }
    else if ((BitMask::PLAYER == a->getCollisionBitmask() && BitMask::START_LEFT_COL == b->getCollisionBitmask()) ||
            (BitMask::PLAYER == b->getCollisionBitmask() && BitMask::START_LEFT_COL == a->getCollisionBitmask()))
    {
        //        player->collision = false;
        return true;
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

