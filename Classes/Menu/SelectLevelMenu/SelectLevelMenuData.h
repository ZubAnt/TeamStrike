//
// Created by pavel on 03.05.17.
//

#ifndef TEAMSTRIKE_SELECTLEVELMENUDATA_H
#define TEAMSTRIKE_SELECTLEVELMENUDATA_H

#include "../AbstractMenuData.h"
#include <ui/UITextField.h>

class SelectLevelMenuData: public AbstractMenuData {
public:
    SelectLevelMenuData(Layer *layer, Director *director);

    void set_background();
    void set_header_Label();
    void set_textField();
    int &textFieldEvent(Ref *pSender, ui::TextField::EventType type);

    // Установить кнопку для главного меню в виде label с текстом на позицию x, y
    void set_MenuLabel(const std::string &text, float x, float y, const ccMenuCallback& callback);
    void set_MenuItemImage(const std::string &text1, const std::string &text2,float x, float y,
                           const ccMenuCallback &callback);
    void set_style_MenuLabel(Label *label);
    void set_style_header_label(Label *label);
};


#endif //TEAMSTRIKE_SELECTLEVELMENUDATA_H
