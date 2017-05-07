#ifndef PLAYER_H_
#define PLAYER_H_

#define SPEED_OF_THE_PLAYER 36
#define SPEED_OF_THE_PLAYER_IN_THE_AIR 3
#define SPEED_OF_THE_PLAYER_VELOCITY 1100.0f
#define SPEED_OF_THE_PLAYER_IN_THE_AIR_VELOCITY 1100.0f
#define SPEED_PLAYER_LIMIT 2700.0f

#define PLAYER_DENSITY 500.0f
#define PLAYER_RESTITUTION 0.0000001f
#define PLAYER_FRICTION 1.0f

#include "cocos2d.h"
USING_NS_CC;

#include <unordered_map>
#include <string>
#include <vector>

class Player: public cocos2d::Sprite {
public:

    Player();
    Player(std::string _pathAnim,
           std::string _idleAnimFramesTemplate,
           std::string _moveAnimFramesTemplate,
           std::string _jumpAnimFramesTemplate,
           std::string _deathAnimFramesTemplate,
           std::string _flyingAnimFramesTemplate
           );

    ~Player();
    static Player* create();

    virtual void update();
    virtual void move();
    virtual void jump();
    virtual void idle();

    virtual void die();
    virtual void fly();
    bool is_moving;
    bool is_jumping;
    bool is_idling;
    bool is_shooting;
    bool is_dying;
    bool is_onJetpack;

    bool is_onGround;
    bool is_collisionPlatform_On;

    bool collision_right_platform;
    bool collision_left_platform;
    unsigned int timer;
    int direction;

    float speed;
    int hp = 100;


    bool key_A;
    bool key_D;

protected:
    Animate* idleAnimate;
    Animate* moveAnimate;
    Animate* jumpAnimate;
    Animate* deathAnimate;
    Animate* flyingAnimate;

    std::string pathAnim;

    std::unordered_map<std::string, std::string> AnimFiles;

    enum current_animation
    {
        IDLING,
        MOVING,
        JUMPING,
        DYING,
        JETPACK
    } curr_anim;

    bool initOptions();

    virtual void initPhysicsPody();

    bool initAnimFrames();
    std::string getFrame(std::string &pattern, int number);

    virtual void initIdleAnimate();
    virtual void initMoveAnimate();
    virtual void initJumpAnimate() ;
    virtual void initDeathAnimate();
    virtual void initFlyingAnimate();
};


#endif /* PLAYER_H_ */
