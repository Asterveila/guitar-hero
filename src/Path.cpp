#include "Path.hpp"

Path::Path(const ccColor3B& color, const ccColor3B& colorBright)
    : m_color(color), m_colorBright(colorBright) {}

Path* Path::create(const ccColor3B& color, const ccColor3B& colorBright) {
    auto ret = new Path(color, colorBright);

    if (ret->init()) {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

bool Path::init() {
    auto winSize = CCDirector::get()->getWinSize();

    m_layer = CCLayerColor::create({m_colorBright.r, m_colorBright.g, m_colorBright.b, 120}, 50, winSize.height);

    this->setContentSize(m_layer->getContentSize());

    m_gradient = CCLayerGradient::create({255, 255, 255, 255}, {0, 0, 0, 0}, {0, -1});
    m_gradient->setOpacity(29);
    m_gradient->setAnchorPoint({0, 1});
    m_gradient->setContentSize({this->getContentWidth(), 65});
    m_gradient->setPositionY(this->getContentHeight());
    m_gradient->ignoreAnchorPointForPosition(false);

    m_layer->addChild(m_gradient);    
    
    auto line = CCSprite::createWithSpriteFrameName("floorLine_001.png");
    line->setColor(m_color);
    line->setScaleX(1.155f);
    line->setRotation(90);
    line->setPosition(this->getContentSize() / 2.f + CCPoint{-this->getContentWidth() / 2.f, 0});

    m_layer->addChild(line);

    m_lines[0] = line;

    line = CCSprite::createWithSpriteFrameName("floorLine_001.png");
    line->setColor(m_color);
    line->setScaleX(1.155f);
    line->setRotation(90);
    line->setPosition(this->getContentSize() / 2.f + CCPoint{this->getContentWidth() / 2.f, 0});

    m_layer->addChild(line);

    m_lines[1] = line;
    
    auto stencil = CCLayerColor::create({255, 255, 255, 255}, this->getContentWidth(), this->getContentHeight());
    stencil->setPositionY(49);
    
    m_clip = CCClippingNode::create();
    m_clip->setStencil(stencil);

    m_layer->addChild(m_clip);

    this->addChild(m_layer);

    return true;
}

CCClippingNode* Path::getClip() {
    return m_clip;
}

void Path::setGlowing(bool glowing) {
    if (glowing == m_glowing) {
        return;
    }

    m_glowing = glowing;

    m_layer->stopAllActions();

    if (!glowing) {
        m_layer->runAction(CCEaseSineInOut::create(CCTintTo::create(0.11f, m_colorBright.r, m_colorBright.g, m_colorBright.b)));

        for (auto line : m_lines) {
            line->runAction(CCEaseSineInOut::create(CCTintTo::create(0.11f, m_color.r, m_color.g, m_color.b)));
        }

        return;
    }

    m_layer->runAction(CCEaseSineInOut::create(CCTintTo::create(0.11f,
        m_colorBright.r + (255 - m_colorBright.r) * 0.45f,
        m_colorBright.g + (255 - m_colorBright.g) * 0.45f,
        m_colorBright.b + (255 - m_colorBright.b) * 0.45f
    )));

    for (auto line : m_lines) {
        line->runAction(CCEaseSineInOut::create(CCTintTo::create(0.11f,
            m_color.r + (255 - m_color.r) * 0.45f,
            m_color.g + (255 - m_color.g) * 0.45f,
            m_color.b + (255 - m_color.b) * 0.45f
        )));
    }
}

void Path::setError(bool erroring) {
    if (m_erroring == erroring) {
        return;
    }

    m_erroring = erroring;

    m_gradient->stopAllActions();

    if (!erroring) {
        m_gradient->runAction(CCSpawn::createWithTwoActions(
            CCEaseSineInOut::create(CCTintTo::create(0.26f, 255, 255, 255)),
            CCEaseSineInOut::create(CCFadeTo::create(0.26f, 29))
        ));
        return;
    }
 
    m_gradient->runAction(CCSpawn::createWithTwoActions(
        CCEaseSineInOut::create(CCTintTo::create(0.26f, 255, 50, 50)),
        CCEaseSineInOut::create(CCFadeTo::create(0.26f, 50))
    ));
}