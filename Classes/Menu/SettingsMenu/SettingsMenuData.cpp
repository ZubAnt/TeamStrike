#include "SettingsMenuData.h"

SettingsMenuData::SettingsMenuData(cocos2d::Layer *layer, Director* director)
{
    _director = director;
    _layer = layer;
    _background_img = "person/x4cFzOk.png";
    _font = "fonts/eurofontextendedc-bditalic.otf";
    _font_select = "fonts/Anton-Regular.ttf";
    _color_header = Color4B(222, 0, 0, 255);
    _color_MenuLabel = Color4B(222, 0, 0, 255);

    _visibleSize = _director->getVisibleSize();
    _origin = _director->getVisibleOrigin();
}

void SettingsMenuData::set_background()
{
    auto background = Sprite::create(_background_img);

    float scaleY = _visibleSize.height / background->getContentSize().height;
    float scaleX = _visibleSize.width / background->getContentSize().width;

    if (scaleX > scaleY) { background->setScale(scaleX); }
    else { background->setScale(scaleY); }

    background->setPosition(Point(_origin.x + _visibleSize.width / 2, _origin.y + _visibleSize.height / 2));
    _layer->addChild(background, -1);
}

void SettingsMenuData::set_header_Label()
{
    auto label_name = create_lable("TEAMSTRIKE", _visibleSize.height / 8);
    label_name->setPosition(Vec2(_origin.x + _visibleSize.width / 2,
                                 _origin.y + _visibleSize.height - 1.1 * label_name->getContentSize().height));
    set_style_header_label(label_name);
    _layer->addChild(label_name, 1);
}

void SettingsMenuData::set_label(const std::string name_label,float fontSize,float x_position, float y_position )
{
    auto label_name = create_lable(name_label,fontSize /*_visibleSize.height / 8*/);
    label_name->setPosition(Vec2(x_position /*_origin.x + _visibleSize.width / 2*/,
                                 y_position- 1.1 * label_name->getContentSize().height) /*_origin.y + _visibleSize.height - 1.1 * label_name->getContentSize().height)*/);
    set_style_header_label(label_name);
    _layer->addChild(label_name, 1);
}

void SettingsMenuData::set_button(const std::string name_label,float x, float y, const ccMenuCallback &callback )
{
    auto label = create_lable(name_label, _visibleSize.width / 40);
    set_style_MenuLabel(label);
    auto menu = create_menu_label(label, x, y, callback);
    _layer->addChild(menu, 1);
}

void SettingsMenuData::set_MenuLabel(const std::string &text, float x, float y, const ccMenuCallback &callback)
{
    auto label = create_lable(text, _visibleSize.width / 20);
    set_style_MenuLabel(label);
    auto menu = create_menu_label(label, x, y, callback);
    _layer->addChild(menu, 1);
}

void SettingsMenuData::set_style_MenuLabel(Label *label)
{
    label->setTextColor(_color_header);
    label->enableShadow(Color4B::BLACK, Size(5, -5), 2);
    label->enableOutline(Color4B::WHITE, 5);
}

void SettingsMenuData::set_style_header_label(Label *label)
{
    label->setTextColor(_color_MenuLabel);
    label->enableShadow(Color4B::BLACK, Size(2, -2), 1);
    label->enableOutline(Color4B::WHITE, 2);
}

void SettingsMenuData::set_layer(cocos2d::ui::CheckBox* lay) {
    _layer->addChild(lay, 1);
}

void SettingsMenuData::set_MenuItemImage( const std::string &text1, const std::string &text2, float x, float y) {
    auto sceneItem = MenuItemImage::create( text1, text2);
    sceneItem->setPosition(Vec2( x, y ));
    _layer->addChild( sceneItem, -1);
}

void SettingsMenuData::set_SceneLabel(const std::string &text, float x, float y, const ccMenuCallback &callback) {
    auto label = create_lable_select(text, _visibleSize.width / 30);
    set_style_SceneLabel(label);
    auto menu = create_menu_label(label, x, y, callback);
    _layer->addChild(menu, 1);
}

void SettingsMenuData::set_style_SceneLabel(Label *label) {
    label->setTextColor(_color_header);
    label->enableShadow(Color4B::BLACK, Size(2, -2), 1);
    label->enableOutline(Color4B::ORANGE, 2);
}

void SettingsMenuData::set_scene_label(const std::string name_label, float fontSize, float x_position, float y_position) {
    auto label_name = create_lable(name_label,fontSize /*_visibleSize.height / 8*/);
    label_name->setPosition(Vec2(x_position /*_origin.x + _visibleSize.width / 2*/,
                                 y_position- 1.1 * label_name->getContentSize().height) /*_origin.y + _visibleSize.height - 1.1 * label_name->getContentSize().height)*/);
    set_style_SceneLabel(label_name);
    _layer->addChild(label_name, 1);
}
