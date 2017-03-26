#include "StartMenu.h"
#include "../MainMenu/MainMenu.h"
#include "StartMenuData.h"

USING_NS_CC;


StartMenu::StartMenu()
{
    logger = new MenuLogger("ErrorStartMenu.log", "EventStartMenu.log");
}

StartMenu::~StartMenu()
{
   delete logger;
}

Scene *StartMenu::createScene()
{
    auto scene = Scene::create();
    auto layer = StartMenu::create();
    scene->addChild(layer);
    return scene;
}

bool StartMenu::init()
{
    if (!Layer::init()) { return false; }

    logger->log_event("Start init() in StartMenu");

    _director = Director::getInstance();
    _visibleSize = _director->getVisibleSize();
    _origin = _director->getVisibleOrigin();

    StartMenuData data(this, _director);
    data.set_background();
    data.set_header_Label();

    data.set_MenuLabel("Menu",
                        _origin.x + _visibleSize.width / 5,
                        _origin.y + _visibleSize.height * 1 / 8,
                        CC_CALLBACK_1(StartMenu::callback_main, this));

    /*data.set_MenuLabel("add Start menu interface",
                        _origin.x + _visibleSize.width / 2,
                        _origin.y + _visibleSize.height / 2,
                        CC_CALLBACK_1(StartMenu::callback_main, this));
    */
    logger->log_event("set background, header, Menu label in SettingsMenu");

    /*
     *
     * add Start menu interface
     *
     * */


    return true;
}

void StartMenu::callback_main(cocos2d::Ref *pSender) {
    _director->pushScene(TransitionFade::create(0.7, MainMenu::createScene()));
    logger->log_event("callback menu");
}
