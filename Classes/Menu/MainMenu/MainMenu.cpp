#include "MainMenu.h"
#include "../SettingsMenu/SettingsMenu.h"
#include "../StartMenu/StartMenu.h"
#include "../ExitMenu/ExitMenu.h"
#include "Map/Map.h"

#include <iostream>

USING_NS_CC;

MainMenu::MainMenu()
{
    logger = new MenuLogger("ErrorMainMenu.log", "EventMainMenu.log");
}

MainMenu::~MainMenu()
{
    delete logger;
}

Scene *MainMenu::createScene()
{    
    auto scene = Scene::create();
    auto layer = MainMenu::create();
    scene->addChild(layer);
    return scene;
}

bool MainMenu::init()
{
    if (!Layer::init()) { return false; }

    logger->log_event("Start init MainMenu");

    _director = Director::getInstance();
    _visibleSize = _director->getVisibleSize();
    _origin = _director->getVisibleOrigin();

    MainMenuData data(this, _director);

    data.set_background();
    data.set_header_Label();

    data.set_MenuLabel("Start",
                        _origin.x + _visibleSize.width / 6, _origin.y + _visibleSize.height * 4 / 8,
                        CC_CALLBACK_1(MainMenu::callback_start, this));
    data.set_MenuLabel("Settings",
                        _origin.x + _visibleSize.width / 6, _origin.y + _visibleSize.height * 3 / 8,
                        CC_CALLBACK_1(MainMenu::callback_settings, this));
    data.set_MenuLabel("Exit",
                        _origin.x + _visibleSize.width / 6, _origin.y + _visibleSize.height * 2 / 8,
                        CC_CALLBACK_1(MainMenu::callback_exit, this));

    logger->log_event("set background, header, Start menu label, "
                      "Settings menu label, Exit menu label in MainMenu");

    return true;
}

void MainMenu::callback_start(cocos2d::Ref *pSender)
{
//    _director->pushScene(TransitionFade::create(0.7, StartMenu::createScene()));
    _director->pushScene(TransitionFade::create(0.7, MapScene::createScene()));

    logger->log_event("callback start");
}

void MainMenu::callback_settings(Ref *pSender)
{
    _director->pushScene(TransitionFade::create(0.7, SettingsMenu::createScene()));
    logger->log_event("callback settings");
}

void MainMenu::callback_exit(Ref *pSender)
{
    _director->pushScene(TransitionFade::create(0.7, ExitMenu::createScene()));
    logger->log_event("callback exit");
}


