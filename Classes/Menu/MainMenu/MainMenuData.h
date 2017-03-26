#ifndef MAINMENUDATA_H
#define MAINMENUDATA_H

#include "../AbstractMenuData.h"

class MainMenuData: public AbstractMenuData
{
public:
    MainMenuData(Layer *layer, Director *director);

    void set_background();
    void set_header_Label();

    // Установить кнопку для главного меню в виде label с текстом на позицию x, y
    void set_MenuLabel(const std::string &text, float x, float y, const ccMenuCallback& callback);

    void set_style_MenuLabel(Label *label);
    void set_style_header_label(Label *label);
};

#endif // MAINMENUDATA_H
