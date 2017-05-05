//
// Created by pavel on 03.05.17.
//

#include <Menu/MainMenu/MainMenu.h>
#include "SelectLevelMenu.h"
#include "Map/Map.h"

USING_NS_CC;

SelectLevelMenu::SelectLevelMenu() {
    logger = new MenuLogger("ErrorSelectLevelMenu.log", "EventSelectLevelMenu.log");
}

SelectLevelMenu::~SelectLevelMenu() {
    delete logger;
}

cocos2d::Scene *SelectLevelMenu::createScene() {
    auto scene = Scene::create();
    auto layer = SelectLevelMenu::create();
    scene->addChild(layer);
    return scene;
}

bool SelectLevelMenu::init() {
    if (!Layer::init()) { return false; }

    logger->log_event("Start init SelectLevelMenu");

    _director = Director::getInstance();
    _visibleSize = _director->getVisibleSize();
    _origin = _director->getVisibleOrigin();

    SelectLevelMenuData data(this, _director);

    data.set_background();
    data.set_header_Label();

    data.set_MenuLabel("Main menu",
                       _origin.x + _visibleSize.width / 3, _origin.y + _visibleSize.height * 1 / 8,
                       CC_CALLBACK_1(SelectLevelMenu::callback_mainMenu, this));
    data.set_MenuLabel("Scene1",
                       _origin.x + _visibleSize.width / 6, _origin.y + _visibleSize.height * 6 / 8,
                       CC_CALLBACK_1(SelectLevelMenu::callback_scene1, this));
    data.set_MenuItemImage("rain_level_little.png", "rain_level_little.png", _origin.x + _visibleSize.width / 6, _origin.y + _visibleSize.height * 5.2 / 8,
                           CC_CALLBACK_1(SelectLevelMenu::callback_scene1, this) );

    data.set_MenuLabel("Scene2",
                       _origin.x + _visibleSize.width / 2, _origin.y + _visibleSize.height * 6 / 8,
                       CC_CALLBACK_1(SelectLevelMenu::callback_scene2, this));
    data.set_MenuItemImage("water_level_little.jpeg", "water_level_little.jpeg", _origin.x + _visibleSize.width / 2, _origin.y + _visibleSize.height * 5.2 / 8,
                           CC_CALLBACK_1(SelectLevelMenu::callback_scene2, this) );

    data.set_MenuLabel("Scene3",
                       _origin.x + _visibleSize.width / 6, _origin.y + _visibleSize.height * 4 / 8,
                       CC_CALLBACK_1(SelectLevelMenu::callback_scene3, this));
    data.set_MenuItemImage("winter_level_little.jpeg", "winter_level_little.jpeg", _origin.x + _visibleSize.width / 6, _origin.y + _visibleSize.height * 3.2 / 8,
                           CC_CALLBACK_1(SelectLevelMenu::callback_scene2, this) );

    data.set_MenuLabel("Scene4",
                       _origin.x + _visibleSize.width / 2, _origin.y + _visibleSize.height * 4 / 8,
                       CC_CALLBACK_1(SelectLevelMenu::callback_scene4, this));
    data.set_MenuItemImage("fire_level_little.jpeg", "fire_level_little.jpeg", _origin.x + _visibleSize.width / 2, _origin.y + _visibleSize.height * 3.2 / 8,
                           CC_CALLBACK_1(SelectLevelMenu::callback_scene2, this) );

    data.set_textField();

    logger->log_event("set background, header, Main menu label, "
                              "Scene1 label, Scene2 label, Scene3 label, Scene4 label");

    return true;
}

void SelectLevelMenu::callback_mainMenu(cocos2d::Ref *pSender) {
    _director->pushScene(TransitionFade::create(0.7, MainMenu::createScene()));
    logger->log_event("callback start");
}

void SelectLevelMenu::callback_scene1(cocos2d::Ref *pSender) {
    _director->pushScene(TransitionFade::create(0.7, MapScene::createScene()));
    logger->log_event("callback start");
}

void SelectLevelMenu::callback_scene2(cocos2d::Ref *pSender) {
    _director->pushScene(TransitionFade::create(0.7, MapScene::createScene()));
    logger->log_event("callback start");
}

void SelectLevelMenu::callback_scene3(cocos2d::Ref *pSender) {
    _director->pushScene(TransitionFade::create(0.7, MapScene::createScene()));
    logger->log_event("callback start");
}

void SelectLevelMenu::callback_scene4(cocos2d::Ref *pSender) {
    _director->pushScene(TransitionFade::create(0.7, MapScene::createScene()));
    logger->log_event("callback start");
}
