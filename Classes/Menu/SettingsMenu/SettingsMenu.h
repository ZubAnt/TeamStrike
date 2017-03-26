#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include "cocos2d.h"
#include "../MenuLogger.h"

USING_NS_CC;

class SettingsMenu: public cocos2d::Layer
{
public:

    SettingsMenu();
    ~SettingsMenu();
    static cocos2d::Scene* createScene();
    bool init();
    CREATE_FUNC(SettingsMenu)

    void callback_main(cocos2d::Ref *pSender);

private:

    cocos2d::Director *_director;
    cocos2d::Size _visibleSize;
    Vec2 _origin;

    MenuLogger *logger;
};

#endif // SETTINGSMENU_H
