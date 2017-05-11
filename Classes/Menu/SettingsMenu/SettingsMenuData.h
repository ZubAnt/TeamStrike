#ifndef SETTINGSMENUDATA_H
#define SETTINGSMENUDATA_H

#include <ui/UICheckBox.h>
#include "../AbstractMenuData.h"
#include <ui/UIEditBox/UIEditBox.h>
#include <ui/UIImageView.h>

class SettingsMenuData: public AbstractMenuData
{
public:
    SettingsMenuData(Layer *layer, Director *director);

    void set_background();
    void set_header_Label();
    void set_label(const std::string name_label,float fontSize,float x_position, float y_position);
    void set_scene_label(const std::string name_label,float fontSize,float x_position, float y_position);
    // Установить кнопку для главного меню в виде label с текстом на позицию x, y
    void set_MenuLabel(const std::string &text, float x, float y, const ccMenuCallback& callback);
    void set_SceneLabel(const std::string &text, float x, float y, const ccMenuCallback& callback);
    void set_style_SceneLabel(Label *label);

    void set_style_MenuLabel(Label *label);
    void set_style_header_label(Label *label);

    void set_button(const std::string name_label,float x, float y, const ccMenuCallback &callback );
    void set_MenuItemImage(const std::string &text1, const std::string &text2,float x, float y);
    void set_MenuItemImage_click(const std::string &text1, const std::string &text2, float x, float y,
                                 const ccMenuCallback &callback);
    void set_layer(cocos2d::ui::CheckBox* );
};

#endif // SETTINGSMENUDATA_H