//
// Created by pavel on 07.04.17.
//
#include "Bullet.h"

namespace
{
    static float kMaximumBulletSpeed = 200.0f;
    static int kDefaultDamage = 10;
}

Bullet::Bullet() {
    CCLOG("bullet create");
}
Bullet::~Bullet() {
    CCLOG("bullet destroy");
}

int Bullet::getDamage() {

    if ( this != NULL ){
        return _damage;
    }
    return NULL;

}

Bullet *Bullet::create(const Warrior *warrior) {

    Bullet* pBullet = new Bullet();

    if( pBullet->initWithFile("bullet.png") )
    {
        pBullet->autorelease();
        pBullet->initOptions(warrior);
        pBullet->addEvents();

        return pBullet;
    }

    CC_SAFE_DELETE(pBullet);
    return nullptr;
}

void Bullet::initOptions(const Warrior *warrior) {
    auto bullet_body = PhysicsBody::createCircle(1,PhysicsMaterial(0,0,0));
    bullet_body->setCollisionBitmask(3);
    this->setScaleY(0.25);
    this->setScaleX(0.1);
    bullet_body->setContactTestBitmask(true);
    bullet_body->setDynamic(true);
    this->setPhysicsBody(bullet_body);
    bullet_body->applyImpulse( Vec2( 500, 0 ) );

    setPosition(warrior->getPosition());

    _maxSpeed = kMaximumBulletSpeed;	// Should depend on bullet type.
    _damage = kDefaultDamage;

    _currentSpeed = Vec2(-1.0f, 0.0f);

    CCLOG("bullet init");


}

void Bullet::addEvents() {
    scheduleUpdate();
}




