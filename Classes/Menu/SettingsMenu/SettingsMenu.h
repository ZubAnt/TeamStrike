#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include "cocos2d.h"
#include "../MenuLogger.h"
#include <ui/UIEditBox/UIEditBox.h>
#include <ui/UITextField.h>
#include <audio/include/SimpleAudioEngine.h>
//#include <cocos/audio/include/SimpleAudioEngine.h>
#include "ui/CocosGUI.h"
#include "Parser.h"
#include <iostream>
USING_NS_CC;

//#include <CocosDenshionMy.h>

class SettingsMenu: public cocos2d::Layer
{
public:

    SettingsMenu();
    ~SettingsMenu();
    static cocos2d::Scene* createScene();
    bool init();
    CREATE_FUNC(SettingsMenu)

    void callback_main(cocos2d::Ref *pSender);
    void callback_start_music(cocos2d::Ref *pSender);
    void callback_stop_music(cocos2d::Ref *pSender);
    void textFieldEvent(Ref *pSender,ui::TextField::EventType type);

private:

    CocosDenshion::SimpleAudioEngine* audio = CocosDenshion::SimpleAudioEngine::getInstance();
    cocos2d::ui::Slider* slider = cocos2d::ui::Slider::create();
    float musicVolume;
    std::string name_user;
    cocos2d::Director *_director;
    cocos2d::Size _visibleSize;
    Vec2 _origin;

    MenuLogger *logger;
};

#endif // SETTINGSMENU_H