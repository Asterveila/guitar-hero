#include "GamerPopup.hpp"
#include "PlayLayer.hpp"
#include "Overlay.hpp"

#include <Geode/ui/GeodeUI.hpp>

GamerPopup::GamerPopup(int id)
    : m_id(id) {}

GamerPopup* GamerPopup::create(int id) {
    auto ret = new GamerPopup(id);

    if (ret->init()) {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

void GamerPopup::updateButton() {
    m_startBtn->setEnabled(Mod::get()->hasSavedValue(numToString(m_id)));
    m_startBtn->setOpacity(Mod::get()->hasSavedValue(numToString(m_id)) ? 255 : 90);
}

bool GamerPopup::init() {
    Popup::init(264, 161);

    this->setTitle("Game");

    auto btn = Button::createWithSpriteFrameName("GJ_optionsBtn_001.png", [](Button*) {
        geode::openSettingsPopup(Mod::get(), false);
    });
    btn->setScale(0.725f);
    btn->setPosition(m_size - CCPoint{2, 2});

    m_mainLayer->addChild(btn);

    bool end = false;

    if (auto pl = static_cast<ProPlayLayer*>(PlayLayer::get())) {
        end = pl->m_fields->started;
    }

    auto btnSpr = ButtonSprite::create(end ? "Stop" : "Start");
    btnSpr->setCascadeOpacityEnabled(true);

    m_startBtn = Button::createWithNode(btnSpr, [this, end](Button*) {
        if (auto pl = static_cast<ProPlayLayer*>(PlayLayer::get())) {
            this->onClose(nullptr);

            queueInMainThread([this, self = Ref(this), pl = Ref(pl), end] {
                if (end) {
                    auto f = pl->m_fields.self();
                  
                    if (f->overlay && f->started) {
                        f->overlay->setVisible(false);
                        f->started = false;
                    
                        auto popup = GamerPopup::create(m_id);
                        popup->m_noElasticity = true;
                        popup->show();
                    }

                    Mod::get()->setSavedValue(numToString(EditorIDs::getID(pl->m_level)) + "-started", false);
                    
                    return;
                }

                pl->startGuitarHero();
            });
        }
    });
    m_startBtn->setScale(0.75f);
    m_startBtn->setPosition({m_size.width / 2.f, 34});

    m_mainLayer->addChild(m_startBtn);

    auto container = CCNode::create();
    container->setContentSize({240, 20});
    container->setLayout(
        AxisLayout::create()
            ->setAxisAlignment(AxisAlignment::Center)
            ->setAutoScale(false)
            ->setGap(8.f)
            ->ignoreInvisibleChildren(false)
    );
    container->setAnchorPoint({0.5f, 0.5f});
    container->setPosition(m_size / 2.f + CCPoint{0, 5.5f});

    m_mainLayer->addChild(container);

    auto bg = NineSlice::create("square02b_001.png");
    bg->setContentSize({140, 31});
    bg->setColor({0, 0, 0});
    bg->setOpacity(85);

    container->addChild(bg);

    auto lbl = CCLabelBMFont::create("Macro file", "bigFont.fnt");
    lbl->setScale(0.305f);
    lbl->setOpacity(169);
    lbl->setPosition(bg->getContentSize() / 2.f + CCPoint{0, 25});

    bg->addChild(lbl);

    m_nameLbl = CCLabelBMFont::create("Not Selected", "bigFont.fnt");
    m_nameLbl->limitLabelWidth(126, 0.43f, 0.f);
    m_nameLbl->setPosition(bg->getContentSize() / 2.f);

    bg->addChild(m_nameLbl);

    if (Mod::get()->hasSavedValue(numToString(m_id))) {
        auto path = std::filesystem::path(Mod::get()->getSavedValue<std::string>(numToString(m_id)));
        m_nameLbl->setString(string::pathToString(path.filename()).c_str());
        m_nameLbl->limitLabelWidth(126, 0.43f, 0.f);
    }

    btnSpr = ButtonSprite::create("Select");

    btn = Button::createWithNode(btnSpr, [this](Button*) {
        async::spawn(file::pick(
            file::PickMode::OpenFile,
            { .defaultPath = dirs::getGameDir(), .filters = { { "GDR Files", { "*.gdr", "*.gdr.json", "*.gdr2" } } } }
        ),
        [this](Result<std::optional<std::filesystem::path>> result) {
            if (result.isOk()) {
                if (auto opt = result.unwrap()) {
                    auto path = opt.value();
                    Mod::get()->setSavedValue(numToString(m_id), path);
                    this->updateButton();
                    m_nameLbl->setString(string::pathToString(path.filename()).c_str());
                    m_nameLbl->limitLabelWidth(126, 0.43f, 0.f);

                    if (auto pl = static_cast<ProPlayLayer*>(PlayLayer::get())) {
                        if (auto overlay = pl->m_fields->overlay) {
                            if (pl->m_fields->started) {
                                pl->startGuitarHero(false);
                            }
                        }
                    }
                }
            }
        });
    });
    btn->setScaleMultiplier(1.1f);
    btn->setScale(0.65f);

    container->addChild(btn);
    container->updateLayout();

    this->updateButton();

    return true;
}