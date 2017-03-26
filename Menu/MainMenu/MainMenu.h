#ifndef MAINMENU_H
#define MAINMENU_H

#include "cocos2d.h"
#include "../MenuLogger.h"
#include "MainMenuData.h"

USING_NS_CC;

class MainMenu: public cocos2d::Layer
{
public:

    MainMenu();
    ~MainMenu();
    static cocos2d::Scene* createScene();
    bool init();
    CREATE_FUNC(MainMenu)

    void callback_start(cocos2d::Ref *pSender);
    void callback_settings(cocos2d::Ref *pSender);
    void callback_exit(cocos2d::Ref *pSender);

private:

    cocos2d::Director *_director;
    cocos2d::Size _visibleSize;
    Vec2 _origin;

    MenuLogger *logger;
};

#endif // MAINMENU_H
