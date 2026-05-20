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
    auto circle = getSetting<"note-style", std::string>() == "Circle";
    auto square = getSetting<"note-style", std::string>() != "Rounded Square";

    m_bg = NineSlice::create(square ? "square.png"_spr : "square02b_001.png");
    m_bg->setContentSize({circle ? 20.f : 26.f, circle ? std::max(0.f, height - 20.f) : height});
    m_bg->setAnchorPoint({0, 0});
    m_bg->setColor(ccc3(
        m_color.r + (255 - m_color.r) * 0.15f,
        m_color.g + (255 - m_color.g) * 0.15f,
        m_color.b + (255 - m_color.b) * 0.15f
    ));

    this->addChild(m_bg);

    m_fg = NineSlice::create(square ? "square.png"_spr : "square02b_001.png");
    m_fg->setContentSize({m_bg->getContentWidth(), circle ? m_bg->getContentHeight() : std::max(0.f, height - 1.6f)});
    m_fg->setAnchorPoint({0, 0});
    m_fg->setColor(m_color);

    m_bg->addChild(m_fg);

    if (circle) {
        m_bg->setPositionY(10.f);

        // auto spr = CCSprite::create("circle-but-2.png"_spr);
        // spr->setAnchorPoint({0.5f, 0.f});
        // spr->setScale(m_bg->getContentWidth() / spr->getContentWidth());
        // spr->setPosition({m_bg->getContentWidth() / 2.f, m_bg->getContentHeight() - 0.75f});
        // spr->setColor(ccc3(
        //     m_color.r + (255 - m_color.r) * 0.15f,
        //     m_color.g + (255 - m_color.g) * 0.15f,
        //     m_color.b + (255 - m_color.b) * 0.15f
        // ));

        // m_bg->addChild(spr);

        m_half = CCSprite::create("circle.png"_spr);
        m_half->setAnchorPoint({0.5f, 0.f});
        m_half->setScale(m_bg->getContentWidth() / m_half->getContentWidth());
        m_half->setPosition({m_bg->getContentWidth() / 2.f, m_bg->getContentHeight()});
        m_half->setColor(m_color);

        m_bg->addChild(m_half);

        m_otherHalf = CCSprite::create("circle.png"_spr);
        m_otherHalf->setAnchorPoint({0.5f, 1.f});
        m_otherHalf->setFlipY(true);
        m_otherHalf->setScale(m_bg->getContentWidth() / m_otherHalf->getContentWidth());
        m_otherHalf->setPositionX(m_bg->getContentWidth() / 2.f);
        m_otherHalf->setColor(m_color);

        m_bg->addChild(m_otherHalf);
    }

    auto line = CCSprite::createWithSpriteFrameName("floorLine_001.png");
    line->setScaleX(std::max(0.f, height - 5.f) / line->getContentWidth());
    line->setScaleY(3.275f);
    line->setRotation(90);
    line->setPosition(m_bg->getContentSize() / 2.f);
    line->setOpacity(32);

    m_bg->addChild(line);

    this->setAnchorPoint({0.5f, 1.f});
    this->setContentSize({m_bg->getContentWidth(), height});

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
    
    if (m_half) {
        m_half->stopAllActions();
        m_otherHalf->stopAllActions();
    }

    if (!pressed) {
        m_fg->runAction(CCEaseSineInOut::create(CCTintTo::create(0.11f, m_color.r, m_color.g, m_color.b)));
        m_bg->runAction(CCEaseSineInOut::create(CCTintTo::create(0.11f,
            m_color.r + (255 - m_color.r) * 0.15f,
            m_color.g + (255 - m_color.g) * 0.15f,
            m_color.b + (255 - m_color.b) * 0.15f
        )));

        if (m_half) {
            m_half->runAction(CCEaseSineInOut::create(CCTintTo::create(0.11f, m_color.r, m_color.g, m_color.b)));
            m_otherHalf->runAction(CCEaseSineInOut::create(CCTintTo::create(0.11f, m_color.r, m_color.g, m_color.b)));
        }
        
        return;
    }

    m_bg->runAction(CCEaseSineInOut::create(CCTintTo::create(0.11f, m_color.r, m_color.g, m_color.b)));
    m_fg->runAction(CCEaseSineInOut::create(CCTintTo::create(0.11f,
        m_color.r - (255 - m_color.r) * 0.15f,
        m_color.g - (255 - m_color.g) * 0.15f,
        m_color.b - (255 - m_color.b) * 0.15f
    )));

    if (m_half) {
        m_half->runAction(CCEaseSineInOut::create(CCTintTo::create(0.11f,
            m_color.r - (255 - m_color.r) * 0.15f,
            m_color.g - (255 - m_color.g) * 0.15f,
            m_color.b - (255 - m_color.b) * 0.15f
        )));

        m_otherHalf->runAction(CCEaseSineInOut::create(CCTintTo::create(0.11f,
            m_color.r - (255 - m_color.r) * 0.15f,
            m_color.g - (255 - m_color.g) * 0.15f,
            m_color.b - (255 - m_color.b) * 0.15f
        )));
    }
}

void InputNode::setGlowing(bool glowing) {
    if (m_glowing == glowing) {
        return;
    }

    m_glowing = glowing;

    m_bg->stopAllActions();
    m_fg->stopAllActions();
    
    if (m_half) {
        m_half->stopAllActions();
        m_otherHalf->stopAllActions();
    }

    if (!glowing) {
        m_fg->runAction(CCEaseSineInOut::create(CCTintTo::create(0.11f, m_color.r, m_color.g, m_color.b)));
        m_bg->runAction(CCEaseSineInOut::create(CCTintTo::create(0.11f,
            m_color.r + (255 - m_color.r) * 0.15f,
            m_color.g + (255 - m_color.g) * 0.15f,
            m_color.b + (255 - m_color.b) * 0.15f
        )));

        if (m_half) {
            m_half->runAction(CCEaseSineInOut::create(CCTintTo::create(0.11f, m_color.r, m_color.g, m_color.b)));
            m_otherHalf->runAction(CCEaseSineInOut::create(CCTintTo::create(0.11f, m_color.r, m_color.g, m_color.b)));
        }

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

    if (m_half) {
        m_half->runAction(CCEaseSineInOut::create(CCTintTo::create(0.11f,
            m_color.r + (255 - m_color.r) * 0.35f,
            m_color.g + (255 - m_color.g) * 0.35f,
            m_color.b + (255 - m_color.b) * 0.35f
        )));

        m_otherHalf->runAction(CCEaseSineInOut::create(CCTintTo::create(0.11f,
            m_color.r + (255 - m_color.r) * 0.35f,
            m_color.g + (255 - m_color.g) * 0.35f,
            m_color.b + (255 - m_color.b) * 0.35f
        )));
    }
}