#include "SettingsMenu.h"
#include "../MainMenu/MainMenu.h"
#include "SettingsMenuData.h"

USING_NS_CC;
#include "ui/CocosGUI.h"
using namespace ui;

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

std::string name_file = "file.json";

parser parser(name_file);

bool SettingsMenu::init()
{
    if (!Layer::init()) { return false; }

    logger->log_event("Start init SettingsMenu");
    musicVolume = parser.get_volume();
    musicVolume *= 100;
    slider->setPercent(musicVolume);

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

    data.set_label("Name ",_visibleSize.height / 16,
                   _origin.x + _visibleSize.width / 5,
                   _origin.y + _visibleSize.height/1.5);
    data.set_label("Sound ",_visibleSize.height / 16,
                   _origin.x + _visibleSize.width / 5,
                   _origin.y + _visibleSize.height/1.8);


    slider->loadBarTexture("Slider_Back.png");
    slider->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png");
    slider->loadProgressBarTexture("Slider_PressBar.png");
    slider->setPosition(Point( _origin.x + _visibleSize.width / 2, _origin.y + _visibleSize.height/2.07));
    slider->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED: {
                musicVolume = slider->getPercent()*0.01;
                audio->setBackgroundMusicVolume(musicVolume);
                parser.set_volume(musicVolume);

                break;
            }
            default:
                break;
        }
    });

    this->addChild(slider);
    name_user="input your name here";
    if(parser.get_name() == " ") {
        parser.set_name(name_user);
    }else {
        name_user = parser.get_name();
    }

    auto textField = cocos2d::ui::TextField::create(name_user,"Arial",30);
    textField->ignoreContentAdaptWithSize(false);
    textField->setMaxLength(11);
    textField->setMaxLengthEnabled(true);
    textField->setTextHorizontalAlignment(TextHAlignment::CENTER);
    textField->setTextVerticalAlignment(TextVAlignment::CENTER);
    textField->setPosition(Point( _origin.x + _visibleSize.width / 2, _origin.y + _visibleSize.height/1.68));
    textField->addEventListener( CC_CALLBACK_2( SettingsMenu::textFieldEvent, this) );
    this->addChild(textField);


    data.set_button("Play",
                    _origin.x + _visibleSize.width / 1.5,
                    _origin.y + _visibleSize.height * 1 / 2.07,
                    CC_CALLBACK_1(SettingsMenu::callback_start_music, this));

    data.set_button("Stop",
                    _origin.x + _visibleSize.width / 1.3,
                    _origin.y + _visibleSize.height * 1 / 2.07,
                    CC_CALLBACK_1(SettingsMenu::callback_stop_music, this));

    return true;
}


void SettingsMenu::textFieldEvent(Ref *pSender,ui::TextField::EventType type){
    switch (type) {
        case TextField::EventType::ATTACH_WITH_IME: {
            TextField* textField = dynamic_cast<TextField*>(pSender);
        }
            break;

        case TextField::EventType::DETACH_WITH_IME: {
            TextField* textField = dynamic_cast<TextField*>(pSender);
            std::string curr_name_set = textField->getString();
            parser.set_name(curr_name_set);

        }
            break;

        case TextField::EventType::INSERT_TEXT: {
            break;
        }
        case TextField::EventType::DELETE_BACKWARD: {
            break;
        }

        default:
            break;
    }
}

void SettingsMenu::callback_start_music(Ref *pSender)
{
    musicVolume = (musicVolume == 0) ? (float)0.5 :musicVolume ;
    slider->setPercent(50);
    audio->setBackgroundMusicVolume(musicVolume);
    parser.set_volume(musicVolume);
}

void SettingsMenu::callback_stop_music(Ref *pSender)
{
    musicVolume = 0;
    slider->setPercent(0);
    audio->setBackgroundMusicVolume(musicVolume);

    parser.set_volume(musicVolume);
}

void SettingsMenu::callback_main(Ref *pSender)
{
    _director->pushScene(TransitionFade::create(0.7, MainMenu::createScene()));
}
