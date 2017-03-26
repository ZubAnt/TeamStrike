#ifndef STARTMENU_H
#define STARTMENU_H

#include "cocos2d.h"
#include "../MenuLogger.h"

USING_NS_CC;

class StartMenu: public cocos2d::Layer
{
public:

    StartMenu();
    ~StartMenu();
    static cocos2d::Scene* createScene();
    bool init();
    CREATE_FUNC(StartMenu)

    void callback_main(cocos2d::Ref *pSender);

private:

    cocos2d::Director *_director;
    cocos2d::Size _visibleSize;
    Vec2 _origin;

    MenuLogger *logger;
};

#endif // STARTMENU_H
