#ifndef EXITMENU_H
#define EXITMENU_H

#include "cocos2d.h"
#include "../MenuLogger.h"

USING_NS_CC;

class ExitMenu: public cocos2d::Layer
{
public:

    ExitMenu();
    ~ExitMenu();
    static cocos2d::Scene* createScene();
    bool init();
    CREATE_FUNC(ExitMenu)

    void callback_main(cocos2d::Ref *pSender);
    void menuCloseCallback(cocos2d::Ref* pSender);
private:

    cocos2d::Director *_director;
    cocos2d::Size _visibleSize;
    Vec2 _origin;

    MenuLogger *logger;
};

#endif // EXITMENU_H
