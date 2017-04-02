//
// Created by pavel on 10.03.17.
//

#ifndef MYGAME_LEVEL1SCENE_H
#define MYGAME_LEVEL1SCENE_H

#include "cocos2d.h"
#include "Player/Warrior.h"


class Level1Scene : public cocos2d::Layer {
public:
	Warrior* _sprRobot;
	void initPhisics();
	bool onCollision(cocos2d::PhysicsContact& contact);
	void setPhysicsBody(cocos2d::Sprite* sprite);
	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
	double keyPressedDuration(cocos2d::EventKeyboard::KeyCode);

    static cocos2d::Scene* createScene();
    virtual bool init();
    void pauseCallback(cocos2d::Ref* pSender);
    Warrior* getWarrior();
    CREATE_FUNC(Level1Scene)
private:
    bool isJump;
    static std::map<cocos2d::EventKeyboard::KeyCode,
            std::chrono::high_resolution_clock::time_point> keys;
public:
    virtual void update(float delta) override;
};


#endif //MYGAME_LEVEL1SCENE_H
