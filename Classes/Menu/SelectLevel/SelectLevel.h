//
// Created by pavel on 05.05.17.
//

#ifndef TEAMSTRIKE_SELECTLEVEL_H
#define TEAMSTRIKE_SELECTLEVEL_H

#include <2d/CCLayer.h>
#include "cocos2d.h"
#include "../MenuLogger.h"

USING_NS_CC;

class SelectLevel: public cocos2d::Layer {
public:
    SelectLevel();
    ~SelectLevel();
    static cocos2d::Scene* createScene();
    bool init();
    CREATE_FUNC(SelectLevel)

    void callback_mainMenu(cocos2d::Ref *pSender);
    void callback_scene1(cocos2d::Ref *pSender);
    void callback_scene2(cocos2d::Ref *pSender);
    void callback_scene3(cocos2d::Ref *pSender);
    void callback_scene4(cocos2d::Ref *pSender);

private:

    cocos2d::Director *_director;
    cocos2d::Size _visibleSize;
    Vec2 _origin;

    MenuLogger *logger;
};


#endif //TEAMSTRIKE_SELECTLEVEL_H
