#pragma once

#include "Includes.hpp"

#include <Geode/modify/PlayLayer.hpp>

class Overlay;

class $modify(ProPlayLayer, PlayLayer) {

    struct Fields {
        Overlay* overlay = nullptr;
        bool started = false;
        bool dontIgnore = false;
    };

    void startGuitarHero();

    $override
    void setupHasCompleted();
    void resetLevel();
    void destroyPlayer(PlayerObject*, GameObject*);

};