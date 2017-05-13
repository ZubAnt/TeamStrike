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


parser parser;

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
                       _origin.x + _visibleSize.width / 2,
                       _origin.y + _visibleSize.height * 1 / 8,
                       CC_CALLBACK_1(SettingsMenu::callback_main, this));


    logger->log_event("set background, header, Menu label in SettingsMenu");

    data.set_scene_label("Name : ",_visibleSize.height / 16,
                         _origin.x + _visibleSize.width / 3.5,
                         _origin.y + _visibleSize.height/1.45);
    data.set_scene_label("Sound : ",_visibleSize.height / 16,
                         _origin.x + _visibleSize.width / 3.5,
                         _origin.y + _visibleSize.height/1.73);


    checkbox->loadTextureBackGround("check_box_normal.png");
    checkbox->loadTextureBackGroundSelected("check_box_active.png");
    checkbox->loadTextureFrontCross("check_box_normal_press.png");
    checkbox->loadTextureBackGroundDisabled("check_box_normal_disable.png");
    checkbox->loadTextureFrontCrossDisabled("check_box_active_disable.png");
    checkbox->setPosition( Vec2( _origin.x + _visibleSize.width / 1.55,
                                 _origin.y + _visibleSize.height * 1 / 2.07) );
    checkbox->addEventListener(CC_CALLBACK_2( SettingsMenu::selectedEvent, this));
    this->addChild(checkbox);



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
    name_user="Enter your name";
    if(parser.get_name() == " ") {
        parser.set_name(name_user);
    }else {
        name_user = parser.get_name();
    }
    name_user = parser.get_name();
    data.set_MenuItemImage("input_little.png", "input_little.png",
                           _origin.x + _visibleSize.width / 2, _origin.y + _visibleSize.height /1.68);
    auto textField = cocos2d::ui::TextField::create(name_user,"Arial",30);
    textField->ignoreContentAdaptWithSize(true);
    textField->setMaxLength(11);
    textField->setMaxLengthEnabled(true);
    textField->setTextHorizontalAlignment(TextHAlignment::CENTER);
    textField->setTextVerticalAlignment(TextVAlignment::CENTER);
    textField->setPosition(Point( _origin.x + _visibleSize.width / 2, _origin.y + _visibleSize.height/1.68));
    textField->addEventListener( CC_CALLBACK_2( SettingsMenu::textFieldEvent, this) );

    this->addChild(textField);


//    Size editBoxSize = Size(300, 30);
//    std::string pNormalSprite = "green_edit.png";
//    auto _editName = ui::EditBox::create(editBoxSize, ui::Scale9Sprite::create(pNormalSprite));
//    _editName->setPosition(Point( _origin.x + _visibleSize.width / 2, _origin.y + _visibleSize.height/1.68));
//    _editName->setFontName("Paint Boy");
//    _editName->setFontSize(14);
//    _editName->setFontColor(Color3B::RED);
//    _editName->setPlaceHolder("Name:");
//    _editName->setPlaceholderFontColor(Color3B::WHITE);
//    _editName->setMaxLength(8);
//    _editName->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
//    this->addChild(_editName);


//    data.set_button("Play",
//                    _origin.x + _visibleSize.width / 1.5,
//                    _origin.y + _visibleSize.height * 1 / 2.07,
//                    CC_CALLBACK_1(SettingsMenu::callback_start_music, this));

   /* data.set_MenuItemImage_click("play_little1.png", "play_little2.png", _origin.x + _visibleSize.width / 1.55, _origin.y + _visibleSize.height * 1 / 2.07,
                                 CC_CALLBACK_1(SettingsMenu::callback_start_music, this) );


    data.set_MenuItemImage_click("pause_little1.png", "pause_little2.png", _origin.x + _visibleSize.width / 1.40, _origin.y + _visibleSize.height * 1 / 2.07,
                                 CC_CALLBACK_1(SettingsMenu::callback_stop_music, this) );
*/

//    data.set_button("Stop",
//                    _origin.x + _visibleSize.width / 1.3,
//                    _origin.y + _visibleSize.height * 1 / 2.07,
//                    CC_CALLBACK_1(SettingsMenu::callback_stop_music, this));

    return true;
}


void SettingsMenu::textFieldEvent(Ref *pSender,ui::TextField::EventType type){
    switch (type) {
        case TextField::EventType::ATTACH_WITH_IME: {
            TextField* textField = dynamic_cast<TextField*>(pSender);
            name_user = textField->getString();
        }
            break;

        case TextField::EventType::DETACH_WITH_IME: {
            TextField* textField = dynamic_cast<TextField*>(pSender);
            name_user = textField->getString();
            parser.set_name(name_user);

        }
            break;

        case TextField::EventType::INSERT_TEXT: {
            TextField* textField = dynamic_cast<TextField*>(pSender);
            name_user = textField->getString();
            break;
        }
        case TextField::EventType::DELETE_BACKWARD: {
            TextField* textField = dynamic_cast<TextField*>(pSender);
            name_user = textField->getString();
            break;
        }

        default: {
            TextField *textField = dynamic_cast<TextField *>(pSender);
            name_user = textField->getString();
            break;
        }
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
    parser.set_name(name_user);
    _director->pushScene(TransitionFade::create(0.7, MainMenu::createScene()));
}

void SettingsMenu::selectedEvent(Ref *pSender, ui::CheckBox::EventType type) {
    switch (type) {
        case ui::CheckBox::EventType::SELECTED: {
            CCLog("yes");
            musicVolume = 0;
            slider->setPercent(0);
            audio->setBackgroundMusicVolume(musicVolume);
            parser.set_volume(musicVolume);
            break;
        }
        case ui::CheckBox::EventType::UNSELECTED: {
            CCLog("no");
            musicVolume = (musicVolume == 0) ? (float)0.5 :musicVolume ;
            slider->setPercent(50);
            audio->setBackgroundMusicVolume(musicVolume);
            parser.set_volume(musicVolume);
            break;
        }
        default:
            break;
    }
}
