#include "InputNode.hpp"

InputNode::InputNode(const ccColor3B& color, int frame, int path)
    : m_color(color), m_frame(frame), m_path(path) {}

InputNode* InputNode::create(const ccColor3B& color, float height, int frame, int path) {
    auto ret = new InputNode(color, frame, path);

    if (ret->init(height)) {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

bool InputNode::init(float height) {
    m_bg = NineSlice::create("square02b_001.png");
    m_bg->setContentSize({26, height});
    m_bg->setAnchorPoint({0, 0});
    m_bg->setColor(ccc3(
        m_color.r + (255 - m_color.r) * 0.15f,
        m_color.g + (255 - m_color.g) * 0.15f,
        m_color.b + (255 - m_color.b) * 0.15f
    ));

    this->addChild(m_bg);

    m_fg = NineSlice::create("square02b_001.png");
    m_fg->setContentSize({26, height - 1.6f});
    m_fg->setAnchorPoint({0, 0});
    m_fg->setColor(m_color);

    m_bg->addChild(m_fg);

    auto line = CCSprite::createWithSpriteFrameName("floorLine_001.png");
    line->setScaleX((height - 5.f) / line->getContentWidth());
    line->setScaleY(3.275f);
    line->setRotation(90);
    line->setPosition(m_bg->getContentSize() / 2.f);
    line->setOpacity(32);

    m_bg->addChild(line);

    this->setAnchorPoint({0.5f, 1.f});
    this->setContentSize(m_bg->getContentSize());

    return true;
}

int InputNode::getFrame() {
    return m_frame;
}

int InputNode::getPath() {
    return m_path;
}

void InputNode::setPressed(bool pressed) {
    if (m_pressed == pressed) {
        return;
    }

    m_pressed = pressed;

    m_bg->stopAllActions();
    m_fg->stopAllActions();

    if (!pressed) {
        m_fg->runAction(CCEaseSineInOut::create(CCTintTo::create(0.11f, m_color.r, m_color.g, m_color.b)));
        m_bg->runAction(CCEaseSineInOut::create(CCTintTo::create(0.11f,
            m_color.r + (255 - m_color.r) * 0.15f,
            m_color.g + (255 - m_color.g) * 0.15f,
            m_color.b + (255 - m_color.b) * 0.15f
        )));

        return;
    }

    m_bg->runAction(CCEaseSineInOut::create(CCTintTo::create(0.11f, m_color.r, m_color.g, m_color.b)));
    m_fg->runAction(CCEaseSineInOut::create(CCTintTo::create(0.11f,
        m_color.r - (255 - m_color.r) * 0.15f,
        m_color.g - (255 - m_color.g) * 0.15f,
        m_color.b - (255 - m_color.b) * 0.15f
    )));
}

void InputNode::setGlowing(bool glowing) {
    if (m_glowing == glowing) {
        return;
    }

    m_glowing = glowing;

    m_bg->stopAllActions();
    m_fg->stopAllActions();

    if (!glowing) {
        m_fg->runAction(CCEaseSineInOut::create(CCTintTo::create(0.11f, m_color.r, m_color.g, m_color.b)));
        m_bg->runAction(CCEaseSineInOut::create(CCTintTo::create(0.11f,
            m_color.r + (255 - m_color.r) * 0.15f,
            m_color.g + (255 - m_color.g) * 0.15f,
            m_color.b + (255 - m_color.b) * 0.15f
        )));

        return;
    }

    m_bg->runAction(CCEaseSineInOut::create(CCTintTo::create(0.11f,
        m_color.r + (255 - m_color.r) * 0.15f,
        m_color.g + (255 - m_color.g) * 0.15f,
        m_color.b + (255 - m_color.b) * 0.15f
    )));

    m_fg->runAction(CCEaseSineInOut::create(CCTintTo::create(0.11f,
        m_color.r + (255 - m_color.r) * 0.35f,
        m_color.g + (255 - m_color.g) * 0.35f,
        m_color.b + (255 - m_color.b) * 0.35f
    )));
}