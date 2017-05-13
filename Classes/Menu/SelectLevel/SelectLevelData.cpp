//
// Created by pavel on 07.05.17.
//

#include "SelectLevelData.h"

#include <ui/UIEditBox/UIEditBox.h>
#include <ui/UIImageView.h>
#include <Menu/MainMenu/MainMenu.h>
#include <ui/UICheckBox.h>
#include "cocos2d.h"
#include "iostream"

USING_NS_CC;

SelectLevelData::SelectLevelData(Layer *layer, Director *director) {
    _director = director;
    _layer = layer;
    _background_img = "background-clouds.png";
    _font = "fonts/FredokaOne-Regular.ttf";
    _font_select = "fonts/FredokaOne-Regular.ttf";
    _color_header = Color4B(51, 204, 255, 255);
    _color_MenuLabel = Color4B(71, 243, 255, 150);

    _visibleSize = _director->getVisibleSize();
    _origin = _director->getVisibleOrigin();
}

void SelectLevelData::set_background() {
    auto background = Sprite::create(_background_img);

    float scaleY = _visibleSize.height / background->getContentSize().height;
    float scaleX = _visibleSize.width / background->getContentSize().width;

    if (scaleX > scaleY) { background->setScale(scaleX); }
    else { background->setScale(scaleY); }

    background->setPosition(Point(_origin.x + _visibleSize.width / 2, _origin.y + _visibleSize.height / 2));
    _layer->addChild(background, -1);
}

void SelectLevelData::set_header_Label() {
    auto label_name = create_lable("SELECT MAP", _visibleSize.height / 8);
    label_name->setPosition(Vec2(_origin.x + _visibleSize.width / 2,
                                 _origin.y + _visibleSize.height - 1.1 * label_name->getContentSize().height));
    set_style_header_label(label_name);
    _layer->addChild(label_name, 1);
}

void SelectLevelData::set_MenuLabel(const std::string &text, float x, float y, const ccMenuCallback &callback) {
    auto label = create_lable(text, _visibleSize.width / 20);
    set_style_MenuLabel(label);
    auto menu = create_menu_label(label, x, y, callback);
    _layer->addChild(menu, 1);
}

void SelectLevelData::set_MenuItemImage(const std::string &text1, const std::string &text2, float x, float y,
                                        const ccMenuCallback &callback) {

    auto button = ui::Button::create(text1, text2, text1);
    //button->setTitleText("Button Text");
    button->addClickEventListener(callback);
    button->setPosition(Vec2(x, y));
    _layer->addChild(button);
}

void SelectLevelData::set_style_MenuLabel(Label *label) {
    label->setTextColor(_color_header);
    label->enableShadow(Color4B::BLACK, Size(5, -5), 2);
    label->enableOutline(Color4B::WHITE, 5);
}

void SelectLevelData::set_style_header_label(Label *label) {
    label->setTextColor(_color_MenuLabel);
    label->enableShadow(Color4B::BLACK, Size(2, -2), 1);
    label->enableOutline(Color4B::WHITE, 2);
}


void SelectLevelData::set_SceneLabel(const std::string &text, float x, float y, const ccMenuCallback &callback) {
    auto label = create_lable_select(text, _visibleSize.width / 30);
    set_style_SceneLabel(label);
    auto menu = create_menu_label(label, x, y, callback);
    _layer->addChild(menu, 1);
}

void SelectLevelData::set_style_SceneLabel(Label *label) {
    label->setTextColor(_color_header);
    label->enableShadow(Color4B::BLACK, Size(2, -2), 1);
    label->enableOutline(Color4B::ORANGE, 2);
}

void SelectLevelData::set_Label_select() {
    auto label_name = create_lable_select("SelectScene", _visibleSize.height / 8);
    label_name->setPosition(Vec2(_origin.x + _visibleSize.width / 2,
                                 _origin.y + _visibleSize.height - 1.1 * label_name->getContentSize().height));
    set_style_header_label(label_name);
    _layer->addChild(label_name, 1);
}

void SelectLevelData::callback_mainMenu(cocos2d::Ref *pSender) {
    _director->pushScene(TransitionFade::create(0.7, MainMenu::createScene()));
    //logger->log_event("callback start");
}

void SelectLevelData::set_check_box(const std::string &text_normal, const std::string &text_press,
                                    const std::string &text_active, const std::string &text_normal_disable,
                                    const std::string &text_active_disable, float x, float y,
                                    const ccMenuCallback &callback) {
    auto checkbox = ui::CheckBox::create( text_normal, text_press, text_active, text_normal_disable, text_active_disable );

    checkbox->addClickEventListener( callback );
    checkbox->setPosition( Vec2( x, y ) );
    _layer->addChild(checkbox);

}

