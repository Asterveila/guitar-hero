#include "Overlay.hpp"
#include "InputNode.hpp"
#include "Path.hpp"
#include "PlayLayer.hpp"

Overlay::Overlay(PlayLayer* playLayer)
    : m_playLayer(playLayer) {}

Overlay* Overlay::create(PlayLayer* playLayer) {
    auto ret = new Overlay(playLayer);

    if (ret->init()) {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

bool Overlay::init() {
    CCLayerColor::init();

    auto winSize = CCDirector::get()->getWinSize();

    this->setContentSize(winSize);
    this->setColor({18, 20, 22});
    this->setVisible(false);
    
    m_gradient = CCLayerGradient::create(ccColor4B{ 45, 52, 59, 255 }, {0, 0, 0, 0}, {0, 0.5f});

    this->addChild(m_gradient);

    auto particle = GameToolbox::particleFromString("110a-1a1a0.3a153a0a0a24a15a569a320a0a0a0a0a0a0a2a1a0a0a1a0a1a0a1a0a0.069a0a1a1a0a0a1a0a1a0a1a0a0a0a0a0a0a0a0a0a0a0a0a0a0a2a1a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0", nullptr, false);
    particle->setPosition(winSize / 2.f);

    this->addChild(particle);

    auto container = CCNode::create();
    container->setAnchorPoint({0.5f, 0.5f});
    container->setPosition(winSize / 2.f);
    container->setLayout(
        AxisLayout::create()
            ->setAxisAlignment(AxisAlignment::Center)
            ->setAutoScale(false)
            ->setAutoGrowAxis(true)
            ->setGap(30.f)
            ->ignoreInvisibleChildren(false)
    );

    this->addChild(container);

    auto createPath = [winSize, container, this](const ccColor3B& color, const ccColor3B& colorBright) -> Path* {
        auto path = Path::create(color, colorBright);
        container->addChild(path);
        return path;
    };
    
    m_paths[0] = createPath(ccColor3B{58, 162, 237}, ccColor3B{ 130, 203, 255 });
    m_paths[1] = createPath(ccColor3B{246, 183, 27}, ccColor3B{ 255, 213, 106 });
    m_paths[2] = createPath(ccColor3B{238, 49, 51}, ccColor3B{ 255, 125, 127 });
    m_paths[3] = createPath(ccColor3B{92, 208, 68}, ccColor3B{ 134, 255, 110 });

    container->updateLayout();

    for (int i = 0; i < m_paths.size(); i++) {
        m_pathPositions[i] = m_paths[i]->getPosition();
    }

    auto line = CCSprite::createWithSpriteFrameName("floorLine_001.png");
    line->setScaleX(1.07f);
    line->setScaleY(0.695f);
    line->setPosition({winSize.width / 2.f, 62});
    line->setOpacity(156);

    this->addChild(line);

    particle = GameToolbox::particleFromString("11a-1a2a2a2a90a19a9a0a20a0a0a0a0a0a0a0a2a1a0a0a0.22a0a0.63a0a0.92a0a0.28a0a1a1a0a0a0.22a0a0.63a0a0.92a0a0.2a0a0a0a0a0a0a0a0a0a0a0a0a2a1a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0", nullptr, false);
    particle->setPosition(m_paths[0]->convertToWorldSpace({0, 0}) + CCPoint{m_paths[0]->getContentWidth() / 2.f, 5});

    this->addChild(particle);

    particle = GameToolbox::particleFromString("11a-1a2a2a2a90a19a9a0a20a0a0a0a0a0a0a0a2a1a0a0a0.96a0a0.71a0a0.1a0a0.28a0a1a1a0a0a0.96a0a0.71a0a0.1a0a0.2a0a0a0a0a0a0a0a0a0a0a0a0a2a1a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0", nullptr, false);
    particle->setPosition(m_paths[1]->convertToWorldSpace({0, 0}) + CCPoint{m_paths[1]->getContentWidth() / 2.f, 5});

    this->addChild(particle);

    particle = GameToolbox::particleFromString("11a-1a2a2a2a90a19a9a0a20a0a0a0a0a0a0a0a2a1a0a0a0.93a0a0.19a0a0.2a0a0.28a0a1a1a0a0a0.93a0a0.29a0a0.3a0a0.2a0a0a0a0a0a0a0a0a0a0a0a0a2a1a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0", nullptr, false);
    particle->setPosition(m_paths[2]->convertToWorldSpace({0, 0}) + CCPoint{m_paths[2]->getContentWidth() / 2.f, 5});

    this->addChild(particle);

    particle = GameToolbox::particleFromString("11a-1a2a2a2a90a19a9a0a20a0a0a0a0a0a0a0a2a1a0a0a0.36a0a0.81a0a0.26a0a0.28a0a1a1a0a0a0.36a0a0.81a0a0.26a0a0.2a0a0a0a0a0a0a0a0a0a0a0a0a2a1a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0", nullptr, false);
    particle->setPosition(m_paths[3]->convertToWorldSpace({0, 0}) + CCPoint{m_paths[3]->getContentWidth() / 2.f, 5});

    this->addChild(particle);

    auto gradient = CCLayerGradient::create({10, 10, 13, 255}, {0, 0, 0, 0}, {0, 1});
    gradient->setAnchorPoint({0.5f, 0.f});
    gradient->setPositionY(7);
    gradient->setContentHeight(48);
    
    this->addChild(gradient);
    this->addChild(CCLayerColor::create({10, 10, 13, 255}, winSize.width, 7));

    auto node = InputNode::create(ccColor3B{ 46, 154, 197 }, 17.f);
    node->setAnchorPoint({0.5f, 0.5f});
    node->setScaleY(-1);
    node->setPosition(m_paths[0]->convertToWorldSpace({0, 0}) + CCPoint{m_paths[0]->getContentWidth() / 2.f, 49});

    this->addChild(node, 2);

    m_hitButtons[0] = node;

    particle = GameToolbox::particleFromString("20a-1a0.26a0.26a18a90a43a77a0a11a0a0a0a0a0a0a0a2a1a0a0a0.160784a0a0.67451a0a1a0a1a0a0a1a0a0a0.160784a0a0.67451a0a1a0a1a0a0a0a0a0a0a0a0a0a0a0a0a2a1a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0", nullptr, false);
    particle->setPosition(node->getPosition() - CCPoint{0, 0.5f});
    particle->stopSystem();

    this->addChild(particle);

    m_particles[0] = particle;

    node = InputNode::create(ccColor3B{ 197, 169, 46 }, 17.f);
    node->setAnchorPoint({0.5f, 0.5f});
    node->setScaleY(-1);
    node->setPosition(m_paths[1]->convertToWorldSpace({0, 0}) + CCPoint{m_paths[1]->getContentWidth() / 2.f, 49});

    this->addChild(node, 2);

    m_hitButtons[1] = node;

    particle = GameToolbox::particleFromString("20a-1a0.26a0.26a18a90a43a77a0a11a0a0a0a0a0a0a0a2a1a0a0a1a0a0.894118a0a0.160784a0a1a0a0a1a0a0a1a0a0.894118a0a0.160784a0a1a0a0a0a0a0a0a0a0a0a0a0a0a2a1a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0", nullptr, false);
    particle->setPosition(node->getPosition() - CCPoint{0, 0.5f});
    particle->stopSystem();

    this->addChild(particle);

    m_particles[1] = particle;

    node = InputNode::create(ccColor3B{ 197, 46, 46 }, 17.f);
    node->setAnchorPoint({0.5f, 0.5f});
    node->setScaleY(-1);
    node->setPosition(m_paths[2]->convertToWorldSpace({0, 0}) + CCPoint{m_paths[2]->getContentWidth() / 2.f, 49});

    this->addChild(node, 2);

    m_hitButtons[2] = node;

    particle = GameToolbox::particleFromString("20a-1a0.26a0.26a18a90a43a77a0a11a0a0a0a0a0a0a0a2a1a0a0a1a0a0.168627a0a0.160784a0a1a0a0a1a0a0a1a0a0.168627a0a0.160784a0a1a0a0a0a0a0a0a0a0a0a0a0a0a2a1a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0", nullptr, false);
    particle->setPosition(node->getPosition() - CCPoint{0, 0.5f});
    particle->stopSystem();

    this->addChild(particle);

    m_particles[2] = particle;

    node = InputNode::create(ccColor3B{ 76, 197, 46 }, 17.f);
    node->setAnchorPoint({0.5f, 0.5f});
    node->setScaleY(-1);
    node->setPosition(m_paths[3]->convertToWorldSpace({0, 0}) + CCPoint{m_paths[3]->getContentWidth() / 2.f, 49});

    this->addChild(node, 2);

    m_hitButtons[3] = node;

    particle = GameToolbox::particleFromString("20a-1a0.26a0.26a18a90a43a77a0a11a0a0a0a0a0a0a0a2a1a0a0a0.160784a0a1a0a0.207843a0a1a0a0a1a0a0a0.160784a0a1a0a0.207843a0a1a0a0a0a0a0a0a0a0a0a0a0a0a2a1a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0", nullptr, false);
    particle->setPosition(node->getPosition() - CCPoint{0, 0.5f});
    particle->stopSystem();

    this->addChild(particle);

    m_particles[3] = particle;

    for (const auto& [key, path] : std::array<std::pair<std::string, int>, 4>{
        std::pair{"blue-key", 0},
        {"yellow-key", 1},
        {"red-key", 2},
        {"green-key", 3}
    }) {
        this->addEventListener(
            KeybindSettingPressedEventV3(Mod::get(), key),
            [this, path](Keybind const& keybind, bool down, bool repeat, double timestamp) {
                if (repeat) {
                    return;
                }

                if (!down || m_pathsAvailable[path] || m_pathsAvailable == std::array{false, false, false, false}) {
                    auto f = static_cast<ProPlayLayer*>(m_playLayer)->m_fields.self();

                    f->dontIgnore = true;

                    m_playLayer->handleButton(down, 1, true);
                 
                    f->dontIgnore = false;
                }

                m_paths[path]->setGlowing(down);
                m_hitButtons[path]->setPressed(down);
                m_pathsPressing[path] = down;
            }
        );
    }

    this->setOpacity(getSetting<"overlay-opacity", int>());

    return true;
}

void Overlay::update(float dt) {
    if (!m_playLayer->m_started || m_playLayer->m_gameState.m_currentProgress <= 0) {
        return;
    }

    if (m_dead) {
        m_timeDead += dt;
    }

    m_pathsAvailable = {false, false, false, false};
    m_killablePaths = {false, false, false, false};

    for (auto node : m_nodes) {
        if (node->getPositionY() < 40.f) {
            continue;
        }

        node->setPositionY(node->getPositionY() - (60.f * getSetting<"speed", float>()) * dt);

        if (node->getPositionY() - node->getContentHeight() < 62.f && node->getPositionY() > 40.f) {
            m_pathsAvailable[node->getPath()] = true;
        }

        auto shouldKill = node->getPositionY() - node->getContentHeight() <= 49.f && node->getPositionY() > 54.f;
        auto shouldDie = node->getPositionY() - node->getContentHeight() <= 39.f && node->getPositionY() > 54.f;

        if (shouldKill) {
            m_killablePaths[node->getPath()] = true;
        }

        auto killing = m_killablePaths[node->getPath()] && m_pathsPressing[node->getPath()];

        node->setGlowing(shouldKill && m_pathsPressing[node->getPath()]);

        auto particle = m_particles[node->getPath()];

        if (killing && !particle->getTag()) {
            particle->setTag(1);
            particle->resumeSystem();
            particle->resetSystem();
        } else if (!killing) {
            particle->setTag(0);
            particle->stopSystem();
        }

        auto path = m_paths[node->getPath()];

        if (shouldKill || shouldDie) {
            if (!path->getActionByTag(99) && (shouldDie || killing)) {
                auto action = CCRepeatForever::create(Shake::create(1.f, killing ? 0.09f : 0.25f));
                action->setTag(99);
                path->runAction(action);
                
                if (!killing) {
                    path->setError(true);
                }
            }
        } else if (!m_killablePaths[node->getPath()]) {
            path->stopAllActions();
            path->setError(false);

            queueInMainThread([this, path, node] {
                path->setPosition(m_pathPositions[node->getPath()]);
            });
        }
    }

    for (int i = 0; i < m_paths.size(); i++) {
        m_hitButtons[i]->setPosition(m_paths[i]->convertToWorldSpace({0, 0}) + CCPoint{m_paths[i]->getContentWidth() / 2.f, 49});
    }
}

void Overlay::loadGame(const std::vector<gdr::Input<>>& inputs) {
    for (auto node : m_nodes) {
        node->removeFromParent();
    }

    m_nodes.clear();

    this->setVisible(true);
    this->scheduleUpdate();

    struct Input {
        uint64_t frame;
        uint64_t duration;
    };

    auto cleanInputs = std::vector<Input>{};

    std::optional<uint64_t> pressFrame;
    bool prevDown = false;
    bool hasPrev = false;

    for (const auto& input : inputs) {
        if (input.player2) {
            continue;
        }

        const bool down = input.down;

        if (!hasPrev) {
            hasPrev = true;
            prevDown = down;

            if (down) {
                pressFrame = input.frame;
            }

            continue;
        }

        if (down == prevDown) {
            continue;
        }

        if (down) {
            pressFrame = input.frame;
        } else {
            if (pressFrame.has_value()) {
                cleanInputs.push_back({
                    .frame = *pressFrame,
                    .duration = input.frame - *pressFrame
                });

                pressFrame.reset();
            }
        }

        prevDown = down;
    }

    for (const auto& input : cleanInputs) {
        auto idx = random::generate<int>(0, 4);
        auto parent = m_paths[idx];
        auto color = std::array{ccColor3B{ 55, 180, 230 }, ccColor3B{ 221, 210, 52 }, ccColor3B{241, 60, 62}, ccColor3B{ 102, 224, 54 }}[idx];
        auto height = input.duration / 4.f * getSetting<"speed", float>();
        // auto height = std::max(static_cast<float>(input.duration / 4.f) + 17.f, 17.f);

        auto node = InputNode::create(color, height, input.frame, idx);
        node->setPositionX(parent->getContentWidth() / 2.f);

        parent->getClip()->addChild(node);
        m_nodes.push_back(node);
    }

    this->resetGame(0.f);
}

void Overlay::resetGame(float offset) {
    m_dead = false;
    m_timeDead = 0.f;
    m_pathsPressing = {false, false, false, false};
    m_killablePaths = {false, false, false, false};

    for (auto node : m_nodes) {
        node->setPositionY(node->getFrame() / 4.f * getSetting<"speed", float>() + node->getContentHeight() + 40.5f - offset * 60.f);
    }
}

void Overlay::died() {
    if (m_dead) {
        return;
    }

    m_dead = true;


}

void Overlay::setOpacity(GLubyte opacity) {
    CCLayerColor::setOpacity(opacity);
    m_gradient->setOpacity(opacity);
}