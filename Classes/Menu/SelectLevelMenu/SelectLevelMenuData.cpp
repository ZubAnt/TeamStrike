//
// Created by pavel on 03.05.17.
//

#include <ui/UIEditBox/UIEditBox.h>
#include <ui/UIImageView.h>
#include "SelectLevelMenuData.h"
#include "cocos2d.h"
#include "iostream"

USING_NS_CC;

SelectLevelMenuData::SelectLevelMenuData(Layer *layer, Director *director) {
    _director = director;
    _layer = layer;
    _background_img = "person/x4cFzOk.png";
    _font = "fonts/eurofontextendedc-bditalic.otf";
    _color_header = Color4B(222, 0, 0, 255);
    _color_MenuLabel = Color4B(222, 0, 0, 255);

    _visibleSize = _director->getVisibleSize();
    _origin = _director->getVisibleOrigin();
}

void SelectLevelMenuData::set_background() {
    auto background = Sprite::create(_background_img);

    float scaleY = _visibleSize.height / background->getContentSize().height;
    float scaleX = _visibleSize.width / background->getContentSize().width;

    if (scaleX > scaleY) { background->setScale(scaleX); }
    else { background->setScale(scaleY); }

    background->setPosition(Point(_origin.x + _visibleSize.width / 2, _origin.y + _visibleSize.height / 2));
    _layer->addChild(background, -1);
}

void SelectLevelMenuData::set_header_Label() {
    auto label_name = create_lable("SelectScene", _visibleSize.height / 8);
    label_name->setPosition(Vec2(_origin.x + _visibleSize.width / 2,
                                 _origin.y + _visibleSize.height - 1.1 * label_name->getContentSize().height));
    set_style_header_label(label_name);
    _layer->addChild(label_name, 1);
}

void SelectLevelMenuData::set_MenuLabel(const std::string &text, float x, float y, const ccMenuCallback &callback) {
    auto label = create_lable(text, _visibleSize.width / 20);
    set_style_MenuLabel(label);
    auto menu = create_menu_label(label, x, y, callback);
    _layer->addChild(menu, 1);
}

void SelectLevelMenuData::set_style_MenuLabel(Label *label) {
    label->setTextColor(_color_header);
    label->enableShadow(Color4B::BLACK, Size(5, -5), 2);
    label->enableOutline(Color4B::WHITE, 5);
}

void SelectLevelMenuData::set_style_header_label(Label *label) {
    label->setTextColor(_color_MenuLabel);
    label->enableShadow(Color4B::BLACK, Size(2, -2), 1);
    label->enableOutline(Color4B::WHITE, 2);
}

void SelectLevelMenuData::set_MenuItemImage( const std::string &text1, const std::string &text2, float x, float y,
                                            const ccMenuCallback &callback ) {
    auto sceneItem = MenuItemImage::create( text1, text2, callback);
    sceneItem->setPosition(Vec2( x, y ));
    _layer->addChild( sceneItem, 1 );
}


void SelectLevelMenuData::set_textField() {
    std::string pNormalSprite = "extensions/green_edit.png";

    auto imageView = ui::ImageView::create("space.jpg");
    imageView->setScale(0.15, 0.08);
    imageView->setPosition(Vec2(_visibleSize.width / 6, _visibleSize.height / 6));
    _layer->addChild(imageView);

    ui::TextField* textField = ui::TextField::create("input Name here","fonts/Marker Felt.ttf",30);
    textField->ignoreContentAdaptWithSize(false);
    textField->setContentSize(Size(240, 160));
    textField->setTextHorizontalAlignment(TextHAlignment::CENTER);
    textField->setTextVerticalAlignment(TextVAlignment::CENTER);
    textField->setPosition(Vec2(_visibleSize.width / 6, _visibleSize.height / 6));
    textField->addEventListener([&](Ref* pSender, ui::TextField::EventType type){
        /*switch (type)
        {
            case ui::TextField::EventType::ATTACH_WITH_IME:
            {
                ui::TextField* textField = dynamic_cast<ui::TextField*>(pSender);
                Size widgetSize = textField->getContentSize();
                textField->runAction(CCMoveTo::create(0.225f,
                                                      Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f + textField->getContentSize().height / 2)));
                textField->setTextHorizontalAlignment(TextHAlignment::LEFT);
                textField->setTextVerticalAlignment(TextVAlignment::TOP);

            textField->setString(CCString::createWithFormat("attach with IME")->getCString());
            }
                break;

            case ui::TextField::EventType::DETACH_WITH_IME:
            {
                ui::TextField* textField = dynamic_cast<ui::TextField*>(pSender);
                Size widgetSize = textField->getContentSize();
                textField->runAction(CCMoveTo::create(0.175f, Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f)));
                textField->setTextHorizontalAlignment(TextHAlignment::CENTER);
                textField->setTextVerticalAlignment(TextVAlignment::CENTER);

            textField->setString(CCString::createWithFormat("detach with IME")->getCString());
            }
                break;

            case ui::TextField::EventType::INSERT_TEXT:
            textField->setString(CCString::createWithFormat("insert words")->getCString());
                break;

            case ui::TextField::EventType::DELETE_BACKWARD:
            textField->setString(CCString::createWithFormat("delete word")->getCString());
                break;

            default:
                break;

        }*/
    });

    _layer->addChild(textField);
}


