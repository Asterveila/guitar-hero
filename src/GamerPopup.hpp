#pragma once

#include "Includes.hpp"

#include <Geode/ui/Button.hpp>

class GamerPopup : public Popup {

private:

    CCLabelBMFont* m_nameLbl = nullptr;

    Button* m_startBtn = nullptr;
    
    GJGameLevel* m_level = nullptr;

    GamerPopup(GJGameLevel*);

    bool init() override;
    
    void updateButton();

public:

    static GamerPopup* create(GJGameLevel*);

};