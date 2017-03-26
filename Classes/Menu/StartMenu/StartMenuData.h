#ifndef STARTMENUDATA_H
#define STARTMENUDATA_H


#include "../AbstractMenuData.h"

class StartMenuData: public AbstractMenuData
{
public:
    StartMenuData(Layer *layer, Director *director);

    void set_background();
    void set_header_Label();

    // Установить кнопку для главного меню в виде label с текстом на позицию x, y
    void set_MenuLabel(const std::string &text, float x, float y, const ccMenuCallback& callback);

    void set_style_MenuLabel(Label *label);
    void set_style_header_label(Label *label);
};


#endif // STARTMENUDATA_H
