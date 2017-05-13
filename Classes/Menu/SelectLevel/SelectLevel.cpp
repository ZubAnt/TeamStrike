//
// Created by pavel on 07.05.17.
//

#include "SelectLevel.h"
#include <Menu/MainMenu/MainMenu.h>
#include "Map/Map.h"
#include "SelectLevelData.h"

USING_NS_CC;

SelectLevel::SelectLevel() {
    logger = new MenuLogger("ErrorSelectLevelMenu.log", "EventSelectLevelMenu.log");
}

SelectLevel::~SelectLevel() {
    delete logger;
}

cocos2d::Scene *SelectLevel::createScene() {
    auto scene = Scene::create();
    auto layer = SelectLevel::create();
    scene->addChild(layer);
    return scene;
}

bool SelectLevel::init() {
    if (!Layer::init()) { return false; }

    logger->log_event("Start init SelectLevelMenu");

    _director = Director::getInstance();
    _visibleSize = _director->getVisibleSize();
    _origin = _director->getVisibleOrigin();

    SelectLevelData data( this, _director );

//    SelectLevel data (this, _director);

    data.set_background();
    data.set_header_Label();

    data.set_MenuLabel("Main menu",
                       _origin.x + _visibleSize.width / 2, _origin.y + _visibleSize.height * 1 / 8,
                       CC_CALLBACK_1(SelectLevel::callback_mainMenu, this));
    data.set_SceneLabel("Scene1",
                        _origin.x + _visibleSize.width / 4.3, _origin.y + _visibleSize.height * 3.3 / 8,
                        CC_CALLBACK_1(SelectLevel::callback_scene1, this));
    data.set_MenuItemImage("rain_level_little.png", "rain_level_little.png", _origin.x + _visibleSize.width / 4.3, _origin.y + _visibleSize.height * 3.6 / 8,
                           CC_CALLBACK_1(SelectLevel::callback_scene1, this) );

    data.set_SceneLabel("Scene2",
                        _origin.x + _visibleSize.width / 2, _origin.y + _visibleSize.height * 4.7 / 8,
                        CC_CALLBACK_1(SelectLevel::callback_scene2, this));
    data.set_MenuItemImage("water_level_little.jpeg", "water_level_little.jpeg", _origin.x + _visibleSize.width / 2, _origin.y + _visibleSize.height * 5 / 8,
                           CC_CALLBACK_1(SelectLevel::callback_scene2, this) );


    data.set_SceneLabel("Scene3",
                        _origin.x + _visibleSize.width / 1.3, _origin.y + _visibleSize.height * 3.3 / 8,
                        CC_CALLBACK_1(SelectLevel::callback_scene3, this));
    data.set_MenuItemImage("winter_level_little.jpeg", "winter_level_little.jpeg", _origin.x + _visibleSize.width / 1.3, _origin.y + _visibleSize.height * 3.6 / 8,
                           CC_CALLBACK_1(SelectLevel::callback_scene2, this) );

    data.set_SceneLabel("Scene4",
                        _origin.x + _visibleSize.width / 2, _origin.y + _visibleSize.height * 2 / 8,
                        CC_CALLBACK_1(SelectLevel::callback_scene4, this));
    data.set_MenuItemImage("fire_level_little.jpeg", "fire_level_little.jpeg", _origin.x + _visibleSize.width / 2, _origin.y + _visibleSize.height * 2.3 / 8,
                           CC_CALLBACK_1(SelectLevel::callback_scene2, this) );

//    data.set_textField();

    logger->log_event("set background, header, Main menu label, "
                              "Scene1 label, Scene2 label, Scene3 label, Scene4 label");

    return true;
}

void SelectLevel::callback_mainMenu(cocos2d::Ref *pSender) {
    _director->pushScene(TransitionFade::create(0.7, MainMenu::createScene()));
    logger->log_event("callback start");
}

void SelectLevel::callback_scene1(cocos2d::Ref *pSender) {
    _director->pushScene(TransitionFade::create(0.7, MapScene::createScene()));
    logger->log_event("callback start");
}

void SelectLevel::callback_scene2(cocos2d::Ref *pSender) {
    _director->pushScene(TransitionFade::create(0.7, MapScene::createScene()));
    logger->log_event("callback start");
}

void SelectLevel::callback_scene3(cocos2d::Ref *pSender) {
    _director->pushScene(TransitionFade::create(0.7, MapScene::createScene()));
    logger->log_event("callback start");
}

void SelectLevel::callback_scene4(cocos2d::Ref *pSender) {
    _director->pushScene(TransitionFade::create(0.7, MapScene::createScene()));
    logger->log_event("callback start");
}
