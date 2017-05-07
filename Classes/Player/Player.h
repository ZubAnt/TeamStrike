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
#include "Character.h"
USING_NS_CC;

#include <unordered_map>
#include <string>
#include <vector>

class Player: public Character {
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

    bool key_A;
    bool key_D;

protected:

    bool initOptions();

    void initPhysicsPody();

    void initIdleAnimate();
    void initMoveAnimate();
    void initJumpAnimate();
    void initDeathAnimate();
    void initFlyingAnimate();
};


#endif /* PLAYER_H_ */
