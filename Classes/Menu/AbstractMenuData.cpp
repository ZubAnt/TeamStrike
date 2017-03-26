#include "AbstractMenuData.h"

AbstractMenuData::AbstractMenuData()
{}

AbstractMenuData::~AbstractMenuData()
{}

Label *AbstractMenuData::create_lable(const std::string &label_text, float fontSize)
{
    return Label::createWithTTF(label_text, _font, fontSize);
}

Menu *AbstractMenuData::create_menu_label(Label *label, float x, float y, const ccMenuCallback &callback)
{
    auto menu_item = MenuItemLabel::create(label, callback);
    menu_item->setPosition(x, y);
    auto menu = Menu::create(menu_item, nullptr);
    menu->setPosition(Vec2::ZERO);
    return menu;
}
