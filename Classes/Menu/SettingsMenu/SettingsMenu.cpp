
#include "SettingsMenu.h"
#include "../MainMenu/MainMenu.h"
#include "SettingsMenuData.h"

#include "ui/CocosGUI.h"
#include <iostream>
USING_NS_CC;


SettingsMenu::SettingsMenu()
{
    logger = new MenuLogger("ErrorSettingsMenu.log", "EventSettingsMenu.log");
}

SettingsMenu::~SettingsMenu()
{
    delete logger;
}

Scene *SettingsMenu::createScene()
{
    auto scene = Scene::create();
    auto layer = SettingsMenu::create();
    scene->addChild(layer);
    return scene;
}

bool SettingsMenu::init()
{
    if (!Layer::init()) { return false; }

    logger->log_event("Start init SettingsMenu");

    _director = Director::getInstance();
    _visibleSize = _director->getVisibleSize();
    _origin = _director->getVisibleOrigin();

    SettingsMenuData data(this, _director);
    data.set_background();
    data.set_header_Label();

    data.set_MenuLabel("Menu",
                        _origin.x + _visibleSize.width / 5,
                        _origin.y + _visibleSize.height * 1 / 8,
                        CC_CALLBACK_1(SettingsMenu::callback_main, this));


    logger->log_event("set background, header, Menu label in SettingsMenu");

    /*
     * add Settings menu interface
     * */

    data.set_label("Name ",_visibleSize.height / 8,
                   _origin.x + _visibleSize.width / 5,
                   _origin.y + _visibleSize.height/1.3);
    data.set_label("Sound ",_visibleSize.height / 8,
                   _origin.x + _visibleSize.width / 4.7,
                   _origin.y + _visibleSize.height/1.8);


    /*************/

   /* auto checkbox = ui::CheckBox::create("check_box_normal.png",
                                     "check_box_normal_press.png",
                                     "check_box_active.png",
                                     "check_box_normal_disable.png",
                                     "check_box_active_disable.png");
    checkbox->setPosition(250.1,250.1);
    checkbox->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                std::cout << "checkbox 1 clicked" << std::endl;
                break;
            default:
                break;
        }
    });

    this->addChild(checkbox);*/

    /*************/
    return true;
}

void SettingsMenu::callback_main(Ref *pSender)
{
     _director->pushScene(TransitionFade::create(0.7, MainMenu::createScene()));
}


