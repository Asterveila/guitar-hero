#pragma once

#include "Includes.hpp"

#include <Geode/modify/PlayLayer.hpp>

class Overlay;

class $modify(ProPlayLayer, PlayLayer) {

    struct Fields {
        Overlay* overlay = nullptr;
        bool started = false;
        bool dontIgnore = false;
        bool completed = false;
        
        ~Fields() {
            setHookEnabled("PlayLayer::postUpdate", false);
        }

    };

    static void onModify(auto& self) {
        (void)self.setHookPriorityPre("PlayLayer::destroyPlayer", Priority::Last + 21903809);
    }

    void startGuitarHero(bool = true);

    $override
    void setupHasCompleted();
    void resetLevel();
    void destroyPlayer(PlayerObject*, GameObject*);
    void postUpdate(float);

};