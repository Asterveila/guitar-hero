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
    this->LABELS();
    this->initButtons();

    for (const auto& [key, path] : std::array<std::pair<std::string, int>, 4>{
        std::pair{"blue-key", 0},
        {"yellow-key", 1},
        {"red-key", 2},
        {"green-key", 3}
    }) {
        this->addEventListener(
            KeybindSettingPressedEventV3(Mod::get(), key),
            [this, path](Keybind const& keybind, bool down, bool repeat, double timestamp) {
                if (repeat || m_completed) {
                    return;
                }

                // if (!down || m_pathsAvailable[path] || m_pathsAvailable == std::array{false, false, false, false}) {
                if (!down || m_pathsAvailable[path] || (getSetting<"any-key", bool>() && m_pathsAvailable != std::array{false, false, false, false})) {
                    auto f = static_cast<ProPlayLayer*>(m_playLayer)->m_fields.self();

                    f->dontIgnore = true;

                    m_playLayer->handleButton(down, 1, true);
                 
                    f->dontIgnore = false;
                }

                m_pathsPressing[path] = down;

                if (getSetting<"any-key", bool>()) {
                    auto pressingAnything = false;

                    for (auto pressing : m_pathsPressing) {
                        if (pressing) {
                            pressingAnything = true;
                            break;
                        }   
                    }
                    
                    for (int i = 0; i < 4; i++) {
                        m_paths[i]->setGlowing(pressingAnything);
                        m_hitButtons[i]->setPressed(pressingAnything);
                    }
                } else {
                    m_paths[path]->setGlowing(down);
                    m_hitButtons[path]->setPressed(down);
                }
            }
        );
    }

    m_ded = CCLayerColor::create({150, 0, 0, 0});

    this->addChild(m_ded);
    this->setOpacity(getSetting<"overlay-opacity", int>());

    return true;
}

void Overlay::update(float dt) {
    if (!m_playLayer->m_started || m_playLayer->m_gameState.m_currentProgress <= 0) {
        return;
    }

    if (m_dead || m_completed) {
        m_timeDead += dt;
    }

    m_pathsAvailable = {false, false, false, false};
    m_killablePaths = {false, false, false, false};

    for (auto node : m_nodes) {
        if (node->getPositionY() < -1.f) {
            continue;
        }

        node->setPositionY(node->getPositionY() - (60.f * getSetting<"speed", float>()) * dt * (1.f - std::min(m_timeDead / 0.65f, 1.f)));

        if (m_completed) {
            return;
        }

        if (node->getPositionY() - node->getContentHeight() < 62.f && node->getPositionY() > 40.f) {
            m_pathsAvailable[node->getPath()] = true;
        }

        auto shouldKill = node->getPositionY() - node->getContentHeight() <= 49.f && node->getPositionY() > 54.f;
        auto shouldDie = node->getPositionY() - node->getContentHeight() <= 35.f && node->getPositionY() > 54.f;
        auto pressing = m_pathsPressing[node->getPath()];

        if (getSetting<"any-key", bool>()) {
            auto pressingAnything = false;

            for (auto pressing : m_pathsPressing) {
                if (pressing) {
                    pressingAnything = true;
                    break;
                }   
            }

            pressing = pressingAnything;
        }

        if (shouldKill) {
            m_killablePaths[node->getPath()] = true;
        }

        auto killing = m_killablePaths[node->getPath()] && pressing;

        if (node->getPositionY() < 33.f) {
            node->setPositionY(-2.f);

            if (m_currentNote != m_currentInput) {
                m_score -= 1.f;
                m_combo = 0;
                m_currentInput = m_currentNote;
                this->spawnThingy(node->getPath(), 0);
                this->updateHeheheha();
            }

            m_currentNote++;
        } else if (m_currentNote != m_currentInput) {
            if (pressing && node->getPositionY() - node->getContentHeight() <= 49.f + (getSetting<"note-style", std::string>() == "Circle" ? 10.f : 8.5f)) {
                m_currentInput = m_currentNote;
                
                auto diff = abs(node->getPositionY() - node->getContentHeight() - 40.5f + (getSetting<"note-style", std::string>() == "Circle" ? 4.6f : 0.f));

                if (diff > 5.1f && diff < 8.f) {
                    this->spawnThingy(node->getPath(), 3);
                    m_score -= 0.1f;
                } else if (diff > 8.f && diff < 13.f) {
                    this->spawnThingy(node->getPath(), 2);
                    m_score -= 0.4f;
                } else if (diff > 13.f) {
                    m_score -= 0.7f;
                    this->spawnThingy(node->getPath(), 1);
                } else {
                    this->spawnThingy(node->getPath(), 4);
                }

                m_combo++;

                if (node->getContentHeight() > (getSetting<"note-style", std::string>() == "Circle" ? 40.f : 34.f)) {
                    m_longy = node->getPath();
                }

                this->updateHeheheha();
            }
        }

        if (m_longy == node->getPath() && node->getPositionY() < 49.f + 2 * (getSetting<"note-style", std::string>() == "Circle" ? 11.6f : 8.5f)) {
            m_longy = -1;
        }

        if (m_wasPressing[node->getPath()] && !pressing && m_longy == node->getPath()) {
            m_score -= 0.01f;
            m_combo = 0;
            this->spawnThingy(node->getPath(), -1);
            this->updateHeheheha();
        }

        m_wasPressing[node->getPath()] = pressing;

        node->setGlowing(shouldKill && pressing);

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

            queueInMainThread([this, path, node, _ = Ref(this)] {
                path->setPosition(m_pathPositions[node->getPath()]);
            });
        }
    }

    for (int i = 0; i < m_paths.size(); i++) {
        m_hitButtons[i]->setPosition(m_paths[i]->convertToWorldSpace({0, 0}) + CCPoint{m_paths[i]->getContentWidth() / 2.f, 49});
    }
}

void Overlay::loadGame(const std::vector<gdr::Input<>>& inputs, float offset) {
    for (auto node : m_nodes) {
        node->removeFromParent();
    }

    m_nodes.clear();

    this->initButtons();

    auto seed = EditorIDs::getID(m_playLayer->m_level) + inputs.size() + getSetting<"seed-offset", int>();

    this->setVisible(true);
    // this->scheduleUpdate();

    struct Input {
        uint64_t frame;
        uint64_t duration;
    };

    auto cleanInputs = std::vector<Input>{};

    std::optional<uint64_t> pressFrame;
    bool prevDown = false;
    bool hasPrev = false;

    for (const auto& input : inputs) {
        // if (input.player2) {
        //     continue;
        // }

        seed += input.frame;

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
        } else if (pressFrame.has_value()) {
            cleanInputs.push_back({
                .frame = *pressFrame,
                .duration = input.frame - *pressFrame
            });

            if (cleanInputs.back().duration / 240.f * 1000 < getSetting<"click-threshold", int>()) {
                cleanInputs.back().duration = 0;
            }

            pressFrame.reset();
        }

        prevDown = down;
    }

    auto generator = random::Generator(seed);

    m_totalInputs = cleanInputs.size();

    for (const auto& input : cleanInputs) {
        auto idx = generator.generate<int>(0, 4);
        auto parent = m_paths[idx];
        auto color = std::array{ccColor3B{ 55, 180, 230 }, ccColor3B{ 221, 210, 52 }, ccColor3B{241, 60, 62}, ccColor3B{ 102, 224, 54 }}[idx];
        auto height = input.duration / 4.f * getSetting<"speed", float>() + 17.f;

        auto node = InputNode::create(color, height, input.frame, idx);
        node->setPositionX(parent->getContentWidth() / 2.f);

        parent->getClip()->addChild(node);
        m_nodes.push_back(node);
    }

    this->resetGame(offset);

    this->schedule(schedule_selector(Overlay::updateAccuracy), 1.f / 60.f, kCCRepeatForever, 0.f);
}

void Overlay::resetGame(float offset) {
    m_dead = false;
    m_timeDead = 0.f;
    m_pathsAvailable = {false, false, false, false};
    m_pathsPressing = {false, false, false, false};
    m_killablePaths = {false, false, false, false};
    m_wasPressing = {false, false, false, false};
    m_longy = -1;
    m_combo = 0;
    m_currentAccuracy = 100.f;
    m_targetAccuracy = 100.f;

    if (m_accuracyLabel) {
        m_accuracyLabel->stopAllActions();
        m_accuracyBlur->stopAllActions();
        m_accuracyBlur->setOpacity(190);
        m_accuracyLabel->setOpacity(182);
    }

    m_ded->stopAllActions();
    m_ded->runAction(CCEaseSineInOut::create(CCFadeTo::create(0.05f, 0)));

    m_currentInput = 1;

    for (auto node : m_nodes) {
        node->setPositionY(node->getFrame() / 4.f * getSetting<"speed", float>() + node->getContentHeight() + 49.f - (getSetting<"note-style", std::string>() == "Circle" ? 11.6f : 8.5f) - offset * (60.f * getSetting<"speed", float>()));
        
        if (node->getPositionY() - node->getContentHeight() < 49.f - (getSetting<"note-style", std::string>() == "Circle" ? 20.f : 17.f)) {
            m_currentInput++;
        }
    }

    m_currentNote = m_currentInput - 1;

    if (m_comboLabel) {
        m_comboLabel->stopAllActions();
        m_comboBlur->stopAllActions();
        m_comboBlur->setOpacity(190);
        m_comboLabel->setOpacity(182);
        m_comboLabel->setString(numToString(m_currentInput).c_str());
    }

    m_totalInputs = m_nodes.size() - m_currentNote;
    m_score = m_totalInputs;

    this->updateHeheheha();
}

void Overlay::died() {
    if (m_dead) {
        return;
    }

    m_dead = true;

    m_ded->stopAllActions();
    m_ded->runAction(CCEaseSineInOut::create(CCFadeTo::create(0.25f, 17)));
}

void Overlay::setOpacity(GLubyte opacity) {
    CCLayerColor::setOpacity(opacity);
    m_gradient->setOpacity(opacity);
}

void Overlay::completed() {
    if (m_completed) {
        return;
    }

    m_completed = true;

    this->setID("");

    this->runAction(CCSequence::create(
        CCFadeTo::create(1.f, 0),
        CallFuncExt::create([this] {
            this->removeFromParent();
        }),
        nullptr
    ));
    this->fadeOut(this);

    for (auto particle : m_particles) {
        particle->setVisible(false);
    }
}

void Overlay::tap(bool down) {
    for (int i = 0; i < 4; i++) {
        m_paths[i]->setGlowing(down);
        m_hitButtons[i]->setPressed(down);
        m_pathsPressing[i] = down;
    }
}

void Overlay::fadeOut(CCNode* node) {
    for (auto child : node->getChildrenExt<CCNodeRGBA*>()) {
        if (typeinfo_cast<CCNodeRGBA*>(child) || typeinfo_cast<CCLayerRGBA*>(child)) {
            child->stopAllActions();
            child->runAction(CCFadeTo::create(1.f, 0));
        }

        this->fadeOut(child);
    }
}

void Overlay::initButtons() {
    for (auto node : m_hitButtons) {
        if (node) {
            node->removeFromParent();
        }
    }

    for (auto light : m_lights) {
        if (light) {
            light->removeFromParent();
        }
    }
    
    for (auto particle : m_particles) {
        if (particle) {
            particle->removeFromParent();
        }
    }

    auto node = InputNode::create(ccColor3B{ 46, 154, 197 }, 17.f);
    node->setAnchorPoint({0.5f, 0.5f});
    node->setScaleY(-1);
    node->setPosition(m_paths[0]->convertToWorldSpace({0, 0}) + CCPoint{m_paths[0]->getContentWidth() / 2.f, 49});

    this->addChild(node, 2);

    m_hitButtons[0] = node;

    auto light = NineSlice::create("blur.png"_spr);
    light->setContentSize(getSetting<"note-style", std::string>() == "Circle" ? CCSize{35, 35} : CCSize{39, 30});
    light->setPosition(node->getPosition() + CCPoint{0, getSetting<"note-style", std::string>() == "Circle" ? -1.5f : 0.f});
    light->setOpacity(0);

    this->addChild(light, 2);

    m_lights[0] = light;

    auto particle = GameToolbox::particleFromString("20a-1a0.26a0.26a18a90a43a77a0a11a0a0a0a0a0a0a0a2a1a0a0a0.160784a0a0.67451a0a1a0a1a0a0a1a0a0a0.160784a0a0.67451a0a1a0a1a0a0a0a0a0a0a0a0a0a0a0a0a2a1a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0", nullptr, false);
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

    light = NineSlice::create("blur.png"_spr);
    light->setContentSize(getSetting<"note-style", std::string>() == "Circle" ? CCSize{35, 35} : CCSize{39, 30});
    light->setPosition(node->getPosition() + CCPoint{0, getSetting<"note-style", std::string>() == "Circle" ? -1.5f : 0.f});
    light->setOpacity(0);

    this->addChild(light, 2);

    m_lights[1] = light;

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

    light = NineSlice::create("blur.png"_spr);
    light->setContentSize(getSetting<"note-style", std::string>() == "Circle" ? CCSize{35, 35} : CCSize{39, 30});
    light->setPosition(node->getPosition() + CCPoint{0, getSetting<"note-style", std::string>() == "Circle" ? -1.5f : 0.f});
    light->setOpacity(0);

    this->addChild(light, 2);

    m_lights[2] = light;

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

    light = NineSlice::create("blur.png"_spr);
    light->setContentSize(getSetting<"note-style", std::string>() == "Circle" ? CCSize{35, 35} : CCSize{39, 30});
    light->setPosition(node->getPosition() + CCPoint{0, getSetting<"note-style", std::string>() == "Circle" ? -1.5f : 0.f});
    light->setOpacity(0);

    this->addChild(light, 2);

    m_lights[3] = light;

    particle = GameToolbox::particleFromString("20a-1a0.26a0.26a18a90a43a77a0a11a0a0a0a0a0a0a0a2a1a0a0a0.160784a0a1a0a0.207843a0a1a0a0a1a0a0a0.160784a0a1a0a0.207843a0a1a0a0a0a0a0a0a0a0a0a0a0a0a2a1a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0", nullptr, false);
    particle->setPosition(node->getPosition() - CCPoint{0, 0.5f});
    particle->stopSystem();

    this->addChild(particle);

    m_particles[3] = particle;
}

void Overlay::updateHeheheha() {
    if (m_accuracyLabel) {
        m_targetAccuracy = m_score / m_totalInputs * 100.f;
        m_accuracyLabel->setString(fmt::format("{:.2f}%", m_currentAccuracy).c_str());
        m_accuracyBlur->setContentWidth(m_accuracyLabel->getScaledContentWidth() + 15.f);
        m_accuracyLabel->getParent()->updateLayout();
        m_accuracyLabel->setOpacity(210);
        m_accuracyBlur->setOpacity(255);
        m_accuracyBlur->stopAllActions();
        m_accuracyBlur->runAction(CCEaseSineInOut::create(CCFadeTo::create(0.2f, 190)));
        m_accuracyLabel->stopAllActions();
        m_accuracyLabel->runAction(CCEaseSineInOut::create(CCFadeTo::create(0.2f, 182)));
    }

    if (m_comboLabel) {
        std::string prev = m_comboLabel->getString();

        m_comboLabel->setString(fmt::format("{}x", m_combo).c_str());
        
        if (prev != std::string_view(m_comboLabel->getString())) {
            auto mult = std::clamp(m_combo / std::min(30.f, static_cast<float>(m_totalInputs)), 0.f, 1.f);
            auto scale = 0.6f + mult * 0.1f;
            ccColor4B color;

            m_comboParticles->resumeSystem();
            m_comboParticles->resetSystem();

            if (mult < 0.1f) {
                color = { 179, 179, 179, 40 };
                m_comboParticles->stopSystem();
            } else if (mult < 0.38f) {
                color = { 255, 255, 255, 40 };
                m_comboParticles->stopSystem();
            } else if (mult < 0.48f) {
                color = { 225, 207, 255, 40 };
                m_comboParticles->stopSystem();
            } else if (mult < 0.68f) {
                color = { 255, 210, 240, 40 };
            } else if (mult < 0.88f) {
                color = { 255, 231, 203, 40 };
            } else {
                color = { 255, 242, 178, 40 };
            }

            m_comboParticles->setStartColor(ccc4FFromccc4B(color));
            m_comboParticles->setEndColor(ccc4FFromccc4B(color));
            
            m_comboLabel->stopAllActions();
            m_comboLabel->setScale(scale);
            m_comboLabel->setOpacity(222);
            m_comboLabel->runAction(CCSpawn::create(
                CCSequence::create(
                    CCEaseSineInOut::create(CCScaleTo::create(0.1f, scale * 1.053846f)),
                    CCEaseSineInOut::create(CCScaleTo::create(0.1f, scale)),
                    nullptr
                ),
                CCFadeTo::create(0.35f, 182),
                CCEaseSineInOut::create(CCTintTo::create(0.3f, color.r, color.g, color.b)),
                nullptr
            ));
            m_comboBlur->setContentWidth(m_comboLabel->getScaledContentWidth() + 15.f);
            m_comboLabel->getParent()->updateLayout();
            m_comboBlur->stopAllActions();
            m_comboBlur->setOpacity(255);
            m_comboBlur->runAction(CCFadeTo::create(0.35f, 190));
            m_comboParticles->setPosition(m_comboBlur->convertToWorldSpace(m_comboBlur->getContentSize() / 2.f));
        }
    }
}

void Overlay::updateAccuracy(float) {
    if (m_targetAccuracy == m_currentAccuracy) {
        return;
    }

    if (m_targetAccuracy < m_currentAccuracy) {
        m_currentAccuracy -= 0.05f;

        if (m_currentAccuracy < m_targetAccuracy) {
            m_currentAccuracy = m_targetAccuracy;
        }
    } else {
        m_currentAccuracy += 0.05f;
        
        if (m_currentAccuracy > m_targetAccuracy) {
            m_currentAccuracy = m_targetAccuracy;
        }
    }
    
    if (!m_accuracyLabel) {
        return;
    }

    auto mult = 1.f - std::clamp(m_currentAccuracy / 80.f, 0.4f, 1.f);

    if (m_currentAccuracy > 80.f) {
        mult = 0.f;
    }

    auto labelScale = 0.65f - 0.44f * mult;
    int color = 255 - 200 * mult;

    m_accuracyLabel->setColor(ccc3(color, color, color));
    m_accuracyLabel->setString(fmt::format("{:.2f}%", m_currentAccuracy).c_str());
    m_accuracyBlur->setContentWidth(m_accuracyLabel->getScaledContentWidth() + 15.f);
    m_accuracyBlur->stopAllActions();
    m_accuracyBlur->runAction(CCEaseSineInOut::create(CCFadeTo::create(0.2f, 190)));
    m_accuracyLabel->stopAllActions();
    m_accuracyLabel->setScale(labelScale);
    m_accuracyLabel->runAction(CCSequence::create(
        CCEaseSineInOut::create(CCScaleTo::create(0.1f, labelScale * 1.053846f)),
        CCSpawn::createWithTwoActions(CCEaseSineInOut::create(CCFadeTo::create(0.2f, 182)), CCEaseSineInOut::create(CCScaleTo::create(0.1f, labelScale))),
        nullptr
    ));

    m_accuracyLabel->getParent()->updateLayout();
}

void Overlay::spawnThingy(int path, int accuracy) {
    auto spawn = [this, path, accuracy](ZStringView text, const ccColor3B& color) {
        if (!getSetting<"show-judgements", bool>()) {
            return;
        }

        auto lbl = CCLabelBMFont::create(text.c_str(), "bigFont.fnt");
        lbl->setScale(0.256f);
        lbl->setAnchorPoint({0, 0});

        auto renderTexture = CCRenderTexture::create(lbl->getScaledContentWidth(), lbl->getScaledContentHeight());
    
        renderTexture->begin();

        lbl->visit();

        renderTexture->end();

        auto mult = random::generate<bool>() ? 1 : -1;

        auto sprite = CCSprite::createWithTexture(renderTexture->getSprite()->getTexture());
        sprite->setFlipY(true);
        sprite->setPosition(m_hitButtons[path]->getPosition()
            + ccp(random::generate<float>(10.f, 14.f) * mult, random::generate<float>(13.f, 18.f))
        );

        this->addChild(sprite, 5);

        auto shader = CCShaderCache::sharedShaderCache()->programForKey(fmt::format("gradient-shader-{}"_spr, accuracy).c_str());

        if (!shader) {
            shader = new CCGLProgram();
            shader->initWithVertexShaderByteArray(vert.c_str(), gradient.c_str());
            shader->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
            shader->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
            shader->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
            shader->link();
            shader->updateUniforms();
            shader->autorelease();
            shader->use();
        }

        auto color1 = ccc4FFromccc3B(color);
        auto color2 = color1;

        color1.r = color1.r + (1.f - color1.r) * 0.52f;
        color1.g = color1.g + (1.f - color1.g) * 0.52f;
        color1.b = color1.b + (1.f - color1.b) * 0.52f;

        glUniform3f(glGetUniformLocation(shader->getProgram(), "u_colorLeft"), color1.r, color1.g, color1.b);
        glUniform3f(glGetUniformLocation(shader->getProgram(), "u_colorRight"), color2.r, color2.g, color2.b);

        sprite->setShaderProgram(shader);

        auto loc = glGetUniformLocation(shader->getProgram(), "u_opacity");

        shader->setUniformLocationWith1f(loc, 0.5f);

        sprite->runAction(CCSpawn::create(
            CCFadeOut::create(0.5f),
            CCEaseSineOut::create(CCMoveBy::create(0.65f, ccp(random::generate<float>(4.f, 10.f) * mult, random::generate<float>(5.f, 11.f)))),
            CCEaseSineOut::create(CCRotateBy::create(0.65f, random::generate<float>(5.f, 15.f) * mult)),
            nullptr
        ));
        sprite->runAction(CCRepeatForever::create(CCSequence::create(
            CallFuncExt::create([sprite, shader = Ref(shader), loc] {
                shader->use();
                shader->setUniformLocationWith1f(loc, sprite->getOpacity() / 255.f);
            }),
            nullptr
        )));
    };

    switch (accuracy) {
        case -1: spawn("Early!", ccColor3B{ 255, 97, 97 }); break;
        case 0: spawn("Miss", ccColor3B{ 129, 0, 0 }); break;
        case 1: spawn("Bad", ccColor3B{ 255, 115, 0 }); break;
        case 2: spawn("Ok", ccColor3B{ 255, 211, 67 }); break;
        case 3: spawn("Good!", ccColor3B{ 31, 189, 0 }); break;
        case 4: spawn("Perfect!", ccColor3B{ 79, 249, 255 }); break;
    }

    if (accuracy <= 0) {
        return;
    }

    auto light = m_lights[path];
    light->stopAllActions();
    light->runAction(CCSequence::create(
        CCFadeTo::create(0.05f, 190),
        CCEaseSineOut::create(CCFadeTo::create(0.7f, 0)),
        nullptr
    ));
}

void Overlay::LABELS() {
    m_accuracyLabel = nullptr;
    m_comboLabel = nullptr;

    if (m_labelsContainer) {
        m_labelsContainer->removeFromParent();
    }

    m_labelsContainer = CCNode::create();
    m_labelsContainer->setContentWidth(200);
    m_labelsContainer->setAnchorPoint({0, 1});
    m_labelsContainer->setLayout(static_cast<SimpleAxisLayout*>(ScrollLayer::createDefaultListLayout(-5.f))->setCrossAxisAlignment(CrossAxisAlignment::Start));
    m_labelsContainer->setPosition({18, CCDirector::get()->getWinSize().height - 18});

    this->addChild(m_labelsContainer);

    if (getSetting<"show-accuracy", bool>()) {
        m_accuracyLabel = CCLabelBMFont::create("100.00%", "bigFont.fnt");
        m_accuracyLabel->setAnchorPoint({0, 1});
        m_accuracyLabel->setScale(0.65f);
        m_accuracyLabel->setOpacity(182);
        m_accuracyLabel->setAnchorPoint({0, 0.5f});

        m_labelsContainer->addChild(m_accuracyLabel);

        auto sub = CCNode::create();
        sub->setContentHeight(20);

        m_labelsContainer->addChild(sub);

        m_accuracyBlur = NineSlice::create("blur.png"_spr);
        m_accuracyBlur->setContentSize({m_accuracyLabel->getScaledContentWidth() + 15, 20});
        m_accuracyBlur->setAnchorPoint({0, 0});
        m_accuracyBlur->setPositionX(-8.f);
        m_accuracyBlur->setOpacity(190);

        sub->addChild(m_accuracyBlur);
    }

    if (getSetting<"show-combo", bool>()) {
        m_comboLabel = CCLabelBMFont::create("0x", "bigFont.fnt");
        m_comboLabel->setAnchorPoint({0, 1});
        m_comboLabel->setScale(0.65f);
        m_comboLabel->setPosition({17, 280});
        m_comboLabel->setOpacity(182);
        m_comboLabel->setAnchorPoint({0, 0.5f});

        m_labelsContainer->addChild(m_comboLabel);

        auto sub = CCNode::create();
        sub->setContentHeight(20);

        m_labelsContainer->addChild(sub);

        m_comboBlur = NineSlice::create("blur.png"_spr);
        m_comboBlur->setContentSize({m_comboLabel->getScaledContentWidth() + 15, 20});
        m_comboBlur->setAnchorPoint({0, 0});
        m_comboBlur->setPositionX(-8.f);
        m_comboBlur->setOpacity(190);

        sub->addChild(m_comboBlur);
        
        m_labelsContainer->updateLayout();

        m_comboParticles = GameToolbox::particleFromString("36a-1a1a0.3a35a90a90a29a0a36a0a0a0a0a0a0a0a2a1a0a0a1a0a1a0a1a0a0a0a1a1a0a0a1a0a1a0a1a0a0.34a0a0a0a0a0a0a0a0a0a0a0a0a2a1a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0", nullptr, false);
        m_comboParticles->stopSystem();
        m_comboParticles->setScaleX(0.25f);
        m_comboParticles->setScaleY(-0.25f);
        
        this->addChild(m_comboParticles);
    }

    this->updateHeheheha();
}