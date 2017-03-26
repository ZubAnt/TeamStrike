#include "ExitMenu.h"
#include "../MainMenu/MainMenu.h"
#include "ExitMenuData.h"
#include "../AbstractMenuData.h"

USING_NS_CC;


ExitMenu::ExitMenu()
{
    logger = new MenuLogger("ErrorSettingsMenu.log", "EventSettingsMenu.log");
}

ExitMenu::~ExitMenu()
{
    delete logger;
}

Scene *ExitMenu::createScene()
{
    auto scene = Scene::create();
    auto layer = ExitMenu::create();
    scene->addChild(layer);
    return scene;
}

bool ExitMenu::init()
{
    if (!Layer::init()) { return false; }

    logger->log_event("Start init SettingsMenu");

    _director = Director::getInstance();
    _visibleSize = _director->getVisibleSize();
    _origin = _director->getVisibleOrigin();

    ExitMenuData data(this, _director);
    data.set_background();
    data.set_header_Label();

    logger->log_event("set background, header, Menu label in ExitMenu");


    const std::string label_name = "Are you sure?";
    data.set_label(label_name,_visibleSize.height / 14,
                   _origin.x + _visibleSize.width / 2,
                   _origin.y + _visibleSize.height/1.6);
    data.set_MenuLabel("Yes",
                       _origin.x + _visibleSize.width * 2.5 / 6,
                       _origin.y + _visibleSize.height / 2.5,
                       CC_CALLBACK_1(ExitMenu::menuCloseCallback, this));

    data.set_MenuLabel("No",
                           _origin.x + _visibleSize.width * 3.5 / 6,
                           _origin.y + _visibleSize.height / 2.5,
                       CC_CALLBACK_1(ExitMenu::callback_main, this));


    return true;
}

void ExitMenu::callback_main(Ref *pSender)
{
     _director->pushScene(TransitionFade::create(0.7, MainMenu::createScene()));
}

void ExitMenu::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application

    Director::getInstance()->end();
}
