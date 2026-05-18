#pragma once

#include "Includes.hpp"

#include <Geode/modify/GJBaseGameLayer.hpp>

class $modify(ProGJBaseGameLayer, GJBaseGameLayer) {

    $override
    void handleButton(bool, int, bool);

};