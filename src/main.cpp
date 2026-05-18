#include "Includes.hpp"
#include "GamerPopup.hpp"
#include "PlayLayer.hpp"
#include "Overlay.hpp"

#include <Geode/modify/PauseLayer.hpp>
#include <Geode/ui/Button.hpp>

$on_mod(Loaded) {

    listenForAllSettingChanges([](std::string_view, std::shared_ptr<SettingV3>) {
        if (auto pl = PlayLayer::get()) {
            if (auto overlay = static_cast<ProPlayLayer*>(pl)->m_fields->overlay) {
                overlay->setOpacity(getSetting<"overlay-opacity", int>());
            }
        }
    });

}

class $modify(PauseLayer) {

    void customSetup() {
        PauseLayer::customSetup();

        auto btn = Button::createWithSpriteFrameName("GJ_plainBtn_001.png", [](Button*) {
            if (auto pl = PlayLayer::get()) {
                GamerPopup::create(EditorIDs::getID(pl->m_level))->show();
            }
        });
        btn->setPosition({50, 50});

        this->addChild(btn);
    }

};
