#include "MainMenuData.h"


MainMenuData::MainMenuData(cocos2d::Layer *layer, Director* director)
{
    _director = director;
    _layer = layer;
    _background_img = "person/x4cFzOk.png";
    _font = "fonts/eurofontextendedc-bditalic.otf";
    _color_header = Color4B(222, 0, 0, 255);
    _color_MenuLabel = Color4B(222, 0, 0, 255);

    _visibleSize = _director->getVisibleSize();
    _origin = _director->getVisibleOrigin();
}

void MainMenuData::set_background()
{
    auto background = Sprite::create(_background_img);

    float scaleY = _visibleSize.height / background->getContentSize().height;
    float scaleX = _visibleSize.width / background->getContentSize().width;

    if (scaleX > scaleY) { background->setScale(scaleX); }
    else { background->setScale(scaleY); }

    background->setPosition(Point(_origin.x + _visibleSize.width / 2, _origin.y + _visibleSize.height / 2));
    _layer->addChild(background, -1);
}

void MainMenuData::set_header_Label()
{
    auto label_name = create_lable("TEAMSTRIKE", _visibleSize.height / 8);
    label_name->setPosition(Vec2(_origin.x + _visibleSize.width / 2,
                                 _origin.y + _visibleSize.height - 1.1 * label_name->getContentSize().height));
    set_style_header_label(label_name);
    _layer->addChild(label_name, 1);
}

void MainMenuData::set_MenuLabel(const std::string &text, float x, float y, const ccMenuCallback &callback)
{
    auto label = create_lable(text, _visibleSize.width / 20);
    set_style_MenuLabel(label);
    auto menu = create_menu_label(label, x, y, callback);
    _layer->addChild(menu, 1);
}

void MainMenuData::set_style_MenuLabel(Label *label)
{
    label->setTextColor(_color_header);
    label->enableShadow(Color4B::BLACK, Size(5, -5), 2);
    label->enableOutline(Color4B::WHITE, 5);
}

void MainMenuData::set_style_header_label(Label *label)
{
    label->setTextColor(_color_MenuLabel);
    label->enableShadow(Color4B::BLACK, Size(2, -2), 1);
    label->enableOutline(Color4B::WHITE, 2);
}
