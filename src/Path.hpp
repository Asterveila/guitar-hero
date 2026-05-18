#pragma once

#include "Includes.hpp"

class Path : public CCNode {

private:

    CCLayerColor* m_layer = nullptr;
    CCClippingNode* m_clip = nullptr;
    CCLayerGradient* m_gradient = nullptr;

    std::array<CCSprite*, 2> m_lines = {nullptr, nullptr};

    ccColor3B m_color;
    ccColor3B m_colorBright;

    bool m_glowing = false;
    bool m_erroring = false;

    Path(const ccColor3B&, const ccColor3B&);

    bool init();

public:

    static Path* create(const ccColor3B&, const ccColor3B&);

    CCClippingNode* getClip();
    
    void setGlowing(bool);
    void setError(bool);

};