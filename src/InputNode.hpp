#pragma once

#include "Includes.hpp"

class InputNode : public CCNode {

private:

    NineSlice* m_fg = nullptr;
    NineSlice* m_bg = nullptr;
    CCSprite* m_half = nullptr;
    CCSprite* m_otherHalf = nullptr;

    ccColor3B m_color;

    int m_frame;
    int m_path;

    bool m_pressed = false;
    bool m_glowing = false;

    InputNode(const ccColor3B&, int, int);

    bool init(float);

public:

    static InputNode* create(const ccColor3B&, float, int = 0, int = 0);

    int getFrame();
    int getPath();

    void setPressed(bool);
    void setGlowing(bool);

};