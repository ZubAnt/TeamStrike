//
// Created by pavel on 03.05.17.
//

#include "cocos2d.h"
#include "../MenuLogger.h"
#include "SelectLevelMenuData.h"

USING_NS_CC;

#ifndef TEAMSTRIKE_SELECTLEVELMENU_H
#define TEAMSTRIKE_SELECTLEVELMENU_H


class SelectLevelMenu: public cocos2d::Layer {
public:
    SelectLevelMenu();
    ~SelectLevelMenu();
    static cocos2d::Scene* createScene();
    bool init();
    CREATE_FUNC(SelectLevelMenu)

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



#endif //TEAMSTRIKE_SELECTLEVELMENU_H
