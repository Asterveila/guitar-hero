#pragma once

#include "Includes.hpp"

class InputNode;
class Path;

class Overlay : public CCLayerColor {
  
private:

    PlayLayer* m_playLayer = nullptr;
    CCLayerGradient* m_gradient = nullptr;
    CCLayerColor* m_ded = nullptr;

    std::array<bool, 4> m_pathsAvailable;
    std::array<bool, 4> m_killablePaths;
    std::array<bool, 4> m_pathsPressing;
    std::array<CCPoint, 4> m_pathPositions;
    std::array<CCParticleSystemQuad*, 4> m_particles;
    std::array<Path*, 4> m_paths;
    std::array<InputNode*, 4> m_hitButtons;
    std::vector<InputNode*> m_nodes;

    bool m_dead = false;
    bool m_completed = false;
    float m_timeDead = 0.f;

    Overlay(PlayLayer*);

    bool init() override;

    void fadeOut(CCNode*);

public:

    static Overlay* create(PlayLayer*);

    void loadGame(const std::vector<gdr::Input<>>&, float = 0.f);
    void resetGame(float);
    void died();
    void completed();
    
    void update(float) override;
    void setOpacity(GLubyte) override;

};