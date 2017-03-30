#ifndef ABSTRACTMENUDATA_H
#define ABSTRACTMENUDATA_H


#include "cocos2d.h"

USING_NS_CC;

class AbstractMenuData
{
public:

    AbstractMenuData();
    virtual ~AbstractMenuData();

    virtual void set_background() = 0;
    virtual void set_header_Label() = 0;

    // Установить кнопку для главного меню в виде label с текстом на позицию x, y
    virtual void set_MenuLabel(const std::string &text, float x, float y, const ccMenuCallback& callback) = 0;
    
    virtual void set_style_MenuLabel(Label *label) = 0;
    virtual void set_style_header_label(Label *label) = 0;

    Label* create_lable(const std::string &label_text, float fontSize);
    Menu*  create_menu_label(Label *label, float x, float y, const ccMenuCallback &callback);

protected:

    cocos2d::Layer *_layer;
    Director *_director;

    std::string _background_img;
    std::string _font;
    Color4B _color_header;
    Color4B _color_MenuLabel;

    cocos2d::Size _visibleSize;
    Vec2 _origin;
};

#endif // ABSTRACTMENUDATA_H
