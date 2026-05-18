#pragma once

#include "Includes.hpp"

#include <Geode/ui/Button.hpp>

class GamerPopup : public Popup {

private:

    CCLabelBMFont* m_nameLbl = nullptr;

    Button* m_startBtn = nullptr;
    
    int m_id;

    GamerPopup(int);

    bool init() override;
    
    void updateButton();

public:

    static GamerPopup* create(int);

};