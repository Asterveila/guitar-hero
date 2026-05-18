#pragma once

using namespace geode::prelude;

#include <cvolton.level-id-api/include/EditorIDs.hpp>
#include <gdr/gdr.hpp>

struct Replay : gdr::Replay<Replay, gdr::Input<>> {};

class Shake : public CCActionInterval {

private:

    CCPoint m_initialPosition = {0, 0};

    float m_strength = 0.f;

    Shake(float strength)
        : m_strength(strength) {}

    void startWithTarget(CCNode* target) override {
        CCActionInterval::startWithTarget(target);

        m_initialPosition = target->getPosition();
    }

    void update(float time) override {
        m_pTarget->setPosition(m_initialPosition + CCPoint{(CCRANDOM_0_1() * 2 - 1) * m_strength, 0});
    }

public:

    static Shake* create(float duration, float strength) {
        Shake* ret = new Shake(strength);

        if (ret->initWithDuration(duration)) {
            ret->autorelease();
            return ret;
        }

        delete ret;
        return nullptr;
    }

};

template <string::ConstexprString S, typename T>
const T& getSetting() {
    static T value = (
        listenForSettingChanges<T>(S.data(), [](T val) {
            value = val;
        }),
        Mod::get()->getSettingValue<T>(S.data())
    );

    return value;
}