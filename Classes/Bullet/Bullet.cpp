#include "Bullet.h"

Bullet::Bullet()
{
    CCLOG("bullet create");
}

Bullet::~Bullet()
{
    CCLOG("bullet destroy");
}

int Bullet::getDamage()
{
    if (this != NULL)
    {
        return _damage;
    }
    return 0;
}

Bullet *Bullet::create( const Player* player )
{
    Bullet* pBullet = new Bullet();

    if (pBullet->initWithFile("Bullet-1.png"))
    {
        pBullet->autorelease();
        pBullet->initOptions(player);

        return pBullet;
    }

    CC_SAFE_DELETE(pBullet);
    return nullptr;
}

void Bullet::initOptions(const Player* player)
{
    life = true;

    auto bullet_body = PhysicsBody::createCircle(1, PhysicsMaterial(0,0,0));

    bullet_body->setCollisionBitmask(BULLET_COLLISION_BITMASK);
    bullet_body->setDynamic(true);
    bullet_body->setGravityEnable(false);
    bullet_body->setRotationEnable(false);
    bullet_body->setContactTestBitmask(true);

    this->setPhysicsBody(bullet_body);

    Rect size_of_sprite = getTextureRect( );
    if (player->direction == 0)
    {
        bullet_body->applyImpulse(Vec2(-900, 0));
        setPosition( Vec2( player->getPositionX() - size_of_sprite.size.width / 2 - 20, player->getPositionY() + 45));
    }
    else
    {
        bullet_body->applyImpulse(Vec2(900, 0));
        setPosition(Vec2( player->getPositionX() + size_of_sprite.size.width / 2 + 20, player->getPositionY() + 45));
    }

    _maxSpeed = kMaximumBulletSpeed;	// Should depend on bullet type.
    _damage = kDefaultDamage;

    _currentSpeed = Vec2(-1.0f, 0.0f);

    CCLOG("bullet init");
}
