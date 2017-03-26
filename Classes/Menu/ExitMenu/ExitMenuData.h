#ifndef EXITMENUDATA_H
#define EXITMENUDATA_H


#include "../AbstractMenuData.h"

class ExitMenuData: public AbstractMenuData
{
public:
    ExitMenuData(Layer *layer, Director *director);

    void set_background();
    void set_header_Label();
    void set_label(const std::string name_label,float fontSize,float x_position, float y_position );

    // Установить кнопку для главного меню в виде label с текстом на позицию x, y
    void set_MenuLabel(const std::string &text, float x, float y, const ccMenuCallback& callback);

    void set_style_MenuLabel(Label *label);
    void set_style_header_label(Label *label);
};

#endif // EXITMENUDATA_H
