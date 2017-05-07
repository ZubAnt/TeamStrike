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

#define IDLE_ANIMATION_INDEX 0
#define MOVE_ANIMATION_INDEX 1
#define JUMP_ANIMATION_INDEX 2
#define DEATH_ANIMATION_INDEX 3
#define FLY_ANIMATION_INDEX 4

#include "cocos2d.h"
USING_NS_CC;

#include <unordered_map>
#include <string>
#include <vector>
#include <cstdlib>

class Player: public cocos2d::Sprite {
public:

    Player();
    Player(std::string _pathAnim1,
           std::string _pathAnim2,
           std::string _pathAnim3,
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

    void changePlayer();
    bool is_moving;
    bool is_jumping;
    bool is_idling;
    bool is_shooting;
    bool is_dying;
    bool is_onJetpack;
    bool change_player;

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
    enum current_player
    {
        player1 = 0,
        player2,
        player3
    } curr_player;
    current_player next(current_player& f ) { // int denotes postfix++
        if (f == player3) return f = player1; // rollover
        int temp = f;
        return f = static_cast<current_player> (++temp);
    }
    int amount_of_players;

    std::map<current_player, std::vector<Animate*> > animations;
    void initAllAnimations( current_player player );

    std::string pathAnim1;
    std::string pathAnim2;
    std::string pathAnim3;

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
    std::string getFrame( std::string &pattern, int number);

    virtual void initIdleAnimate();
    virtual void initMoveAnimate();
    virtual void initJumpAnimate() ;
    virtual void initDeathAnimate();
    virtual void initFlyingAnimate();
};


#endif /* PLAYER_H_ */
