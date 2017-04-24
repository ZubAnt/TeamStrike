#ifndef PLAYER_H_
#define PLAYER_H_

#define PLAYER_BITMASK 0x000001
#define GROUND_BITMASK  0x000002
#define OBSTACLE_COLLISION_BITMASK  0x000000

#define SPEED_OF_THE_PLAYER 8
#define SPEED_OF_THE_PLAYER_IN_THE_AIR 8
#define PLAYER_DENSITY 100.0f
#define PLAYER_RESTITUTION 0.0f
#define PLAYER_FRICTION 100.0f

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
           std::string _move_fireAnimFramesTemplate,
           std::string _jumpAnimFramesTemplate,
           std::string _deathAnimFramesTemplate,
           std::string _flyingAnimFramesTemplate,
           std::string _shootingAnimFramesTemplate,
           std::string _stay_with_gunAnimFramesTemplate,
           std::string _jump_fireAnimFramesTemplate
           );
    static Player* create();
    ~Player();

    void update();
    void move();
    void move(int directionparam);
    void jump();
    void idle();
    void die();
    void fly();
    void shoot();
    void run_fire();
    void stay_with_gun();
    void jump_fire();

    bool is_moving;
    bool is_jumping;
    bool is_idling;
    bool is_shooting;
    bool is_dying;
    bool is_onJetpack;
    bool is_onGround;

    unsigned int timer;
    int direction;
    int speed;
    bool key_A;
    bool key_D;


protected:

    Animate* idleAnimate;
    Animate* moveAnimate;
    Animate* moveGunAnimate;
    Animate* jumpAnimate;
    Animate* deathAnimate;
    Animate* flyingAnimate;
    Animate* shootingAnimate;
    Animate* stayGunAnimate;
    Animate* jumpGunAnimate;

    std::string pathAnim;
    std::unordered_map<std::string, std::string> AnimFiles;

    PhysicsBody* moveBody;
    PhysicsBody* PlayerBody;

    enum current_animation
    {
        IDLING,
        MOVING,
        JUMPING,
        DYING,
        STAY_SHOOT,
        RUN_GUN,
        STAY_GUN,
        JUMP_GUN,
        JATPACK
    } curr_anim;

    bool initOptions();

    void initPhysicsPody();

    bool initAnimFrames();
    std::string getFrame(std::string &pattern, int number);

    void initIdleAnimate();
    void initMoveAnimate();
    void initMoveGunAnimation();
    void initJumpAnimate();
    void initDeathAnimate();
    void initFlyingAnimate();
    void initShootingAnimate();
    void initStayGunAnimate();
    void initJumpGunAnimate();
};


#endif /* PLAYER_H_ */
