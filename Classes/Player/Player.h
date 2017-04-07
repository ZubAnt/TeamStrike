#ifndef PLAYER_H_
#define PLAYER_H_

#define PLAYER_BITMASK 0x000001
#define GROUND_BITMASK  0x000002
#define OBSTACLE_COLLISION_BITMASK  0x000000

#define SPEED_OF_THE_PLAYER 4
#define SPEED_OF_THE_PLAYER_IN_THE_AIR 2

#include "cocos2d.h"
USING_NS_CC;

class Player:public cocos2d::Sprite {
public:

    static Player* create();
    ~Player();

    void update();
    void move(int directionParam);
    void jump();
    void idle();

    bool moving;
    bool jumping;
    bool idling;
    bool is_onGround;

private:

    Animate * idleAnimate;
    Animate * moveAnimate;
    Animate * jumpAnimate;

    void initOptions();
    void setPlayerPhysicsBody();

    int direction;
};

#endif /* PLAYER_H_ */
