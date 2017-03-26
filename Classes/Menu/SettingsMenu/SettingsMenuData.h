#ifndef SETTINGSMENUDATA_H
#define SETTINGSMENUDATA_H

#include "../AbstractMenuData.h"

class SettingsMenuData: public AbstractMenuData
{
public:
    SettingsMenuData(Layer *layer, Director *director);

    void set_background();
    void set_header_Label();
    void set_label(const std::string name_label,float fontSize,float x_position, float y_position);
    // Установить кнопку для главного меню в виде label с текстом на позицию x, y
    void set_MenuLabel(const std::string &text, float x, float y, const ccMenuCallback& callback);

    void set_style_MenuLabel(Label *label);
    void set_style_header_label(Label *label);
};

#endif // SETTINGSMENUDATA_H
