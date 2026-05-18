#include "PlayLayer.hpp"
#include "Overlay.hpp"

#include <gdr_convert.hpp>

void ProPlayLayer::startGuitarHero() {
    auto f = m_fields.self();
    
    if (!f->overlay || !Mod::get()->hasSavedValue(numToString(EditorIDs::getID(m_level)))) {
        return;
    }

    if (auto scene = CCScene::get()) {
        if (auto pause = scene->getChildByType<PauseLayer>(0)) {
            pause->onRestartFull(nullptr);
        }
    }

    auto path = Mod::get()->getSavedValue<std::filesystem::path>(numToString(EditorIDs::getID(m_level)));

    if (!std::filesystem::exists(path)) {
        return;
    }

    std::vector<gdr::Input<>> inputs;

    if (path.extension() == ".gdr" || path.extension() == ".json") {
        std::ifstream f(path, std::ios::binary);

        f.seekg(0, std::ios::end);
        size_t fileSize = f.tellg();
        f.seekg(0, std::ios::beg);

        std::vector<std::uint8_t> macroData(fileSize);

        f.read(reinterpret_cast<char *>(macroData.data()), fileSize);
        f.close();
        
        auto convertRes = gdr::convert<Replay, gdr::Input<>>(std::span<std::uint8_t>(macroData));

        if (!convertRes.isOk()) {
            return;
        }

        inputs = convertRes.unwrap().inputs;
    } else {
        auto importRes = Replay::importData(path);

        if (!importRes.isOk()) {
            return;
        }

        inputs = importRes.unwrap().inputs;
    }

    f->overlay->loadGame(inputs);
    f->started = true;
}

void ProPlayLayer::setupHasCompleted() {
    PlayLayer::setupHasCompleted();

    auto f = m_fields.self();

    f->overlay = Overlay::create(this);
    f->overlay->setID("overlay"_spr);

    this->insertBefore(f->overlay, m_percentageLabel);
}

void ProPlayLayer::resetLevel() {
    PlayLayer::resetLevel();

    if (auto overlay = m_fields->overlay) {
        overlay->resetGame(m_gameState.m_levelTime);
    }
}

void ProPlayLayer::destroyPlayer(PlayerObject* p0, GameObject* p1) {
    PlayLayer::destroyPlayer(p0, p1);

    auto f = m_fields.self();

    if (p1 != m_anticheatSpike && f->overlay && p0->isVanillaPlayer()) {
        f->overlay->died();
    }
}