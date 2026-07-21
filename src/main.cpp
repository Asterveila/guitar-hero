#include "Includes.hpp"
#include "GamerPopup.hpp"
#include "PlayLayer.hpp"
#include "Overlay.hpp"

#include <Geode/modify/PauseLayer.hpp>
#include <Geode/ui/Button.hpp>
#include <Geode/loader/SettingV3.hpp>

$on_mod(Loaded) {

    setHookEnabled("PlayLayer::postUpdate", false);

    listenForSettingChanges<int>("overlay-opacity", [](int value) {
        if (auto pl = static_cast<ProPlayLayer*>(PlayLayer::get())) {
            if (auto overlay = pl->m_fields->overlay) {
                overlay->setOpacity(value);
            }
        }
    });

    listenForSettingChanges<float>("speed", [](float) {
        if (auto pl = static_cast<ProPlayLayer*>(PlayLayer::get())) {
            if (auto overlay = pl->m_fields->overlay) {
                if (pl->m_fields->started) {
                    queueInMainThread([pl = Ref(pl)] {
                        pl->startGuitarHero(false);
                    });
                }
            }
        }
    });

    listenForSettingChanges<std::string>("note-style", [](std::string) {
        if (auto pl = static_cast<ProPlayLayer*>(PlayLayer::get())) {
            if (auto overlay = pl->m_fields->overlay) {
                if (pl->m_fields->started) {
                    queueInMainThread([pl = Ref(pl)] {
                        pl->startGuitarHero(false);
                    });
                }
            }
        }
    });

    listenForSettingChanges<int>("click-threshold", [](int) {
        if (auto pl = static_cast<ProPlayLayer*>(PlayLayer::get())) {
            if (auto overlay = pl->m_fields->overlay) {
                if (pl->m_fields->started) {
                    queueInMainThread([pl = Ref(pl)] {
                        pl->startGuitarHero(false);
                    });
                }
            }
        }
    });

    listenForSettingChanges<bool>("show-accuracy", [](bool) {
        if (auto pl = static_cast<ProPlayLayer*>(PlayLayer::get())) {
            if (auto overlay = pl->m_fields->overlay) {
                if (pl->m_fields->started) {
                    queueInMainThread([overlay = Ref(overlay)] {
                        overlay->LABELS();
                    });
                }
            }
        }
    });

    listenForSettingChanges<bool>("show-combo", [](bool) {
        if (auto pl = static_cast<ProPlayLayer*>(PlayLayer::get())) {
            if (auto overlay = pl->m_fields->overlay) {
                if (pl->m_fields->started) {
                    queueInMainThread([overlay = Ref(overlay)] {
                        overlay->LABELS();
                    });
                }
            }
        }
    });

    // listenForSettingChanges<bool>("show-combo", [](bool) {
    //     if (auto pl = static_cast<ProPlayLayer*>(PlayLayer::get())) {
    //         if (auto overlay = pl->m_fields->overlay) {
    //             if (pl->m_fields->started) {
    //                 queueInMainThread([pl = Ref(pl), overlay = Ref(overlay)] {
    //                     overlay->LABELS();
    //                 });
    //             }
    //         }
    //     }
    // });

}

class $modify(PauseLayer) {

    void customSetup() {
        PauseLayer::customSetup();

        auto menu = this->getChildByID("left-button-menu");

        if (!menu) {
            return;
        }

        auto spr = CCSprite::createWithSpriteFrameName("GJ_plainBtn_001.png");

        auto spr2 = CCSprite::create("icon.png"_spr);
        spr2->setPosition(spr->getContentSize() / 2.f + CCPoint{0.5f, -0.5f});

        spr->addChild(spr2);

        auto btn = Button::createWithNode(spr, [](Button*) {
            if (auto pl = PlayLayer::get()) {
                GamerPopup::create(pl->m_level)->show();
            }
        });
        btn->setScale(0.6f);
        btn->setPosition({35, 35});

        menu->addChild(btn);
        menu->updateLayout();
    }

};
