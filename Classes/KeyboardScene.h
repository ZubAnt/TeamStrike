//
// Created by pavel on 02.04.17.
//

#ifndef TEAMSTRIKE_KEYBOARDSCENE_H
#define TEAMSTRIKE_KEYBOARDSCENE_H
#include "cocos2d.h"


class KeyboardScene : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();
    virtual bool init();

    bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
    double keyPressedDuration(cocos2d::EventKeyboard::KeyCode);

    CREATE_FUNC(KeyboardScene);

private:
    static std::map<cocos2d::EventKeyboard::KeyCode,
    std::chrono::high_resolution_clock::time_point> keys;
    cocos2d::Label * label;
public:
    virtual void update(float delta) override;
};


#endif //TEAMSTRIKE_KEYBOARDSCENE_H
