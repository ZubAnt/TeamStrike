#ifndef PLAYER_H_
#define PLAYER_H_

#define PLAYER_BITMASK 0x000001
#define GROUND_BITMASK  0x000002
#define NEW_BITMASK 0x001
#define OBSTACLE_COLLISION_BITMASK  0x000000

#define SPEED_OF_THE_PLAYER 36
#define SPEED_OF_THE_PLAYER_IN_THE_AIR 3
#define SPEED_OF_THE_PLAYER_VELOCITY 800
#define SPEED_OF_THE_PLAYER_IN_THE_AIR_VELOCITY 800
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

    static Player* create();
    ~Player();

    void update();
    void move();
    void jump();
    void idle();
    void die();
    void fly();


    bool is_moving;
    bool is_jumping;
    bool is_idling;
    bool is_shooting;
    bool is_dying;
    bool is_onJetpack;
    bool is_onGround;

    bool collision;

    unsigned int timer;
    int direction;
    int speed;
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

    void initPhysicsPody();

    bool initAnimFrames();
    std::string getFrame(std::string &pattern, int number);

    void initIdleAnimate();
    void initMoveAnimate();
    void initJumpAnimate();
    void initDeathAnimate();
    void initFlyingAnimate();
};


#endif /* PLAYER_H_ */
