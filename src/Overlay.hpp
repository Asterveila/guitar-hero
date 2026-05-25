#pragma once

#include "Includes.hpp"

inline const ZStringView vert = R"(
    attribute vec4 a_position;
    attribute vec2 a_texCoord;
    attribute vec4 a_color;
    
    #ifdef GL_ES
    varying lowp vec4 v_fragmentColor;
    varying mediump vec2 v_texCoord;
    #else
    varying vec4 v_fragmentColor;
    varying vec2 v_texCoord;
    #endif
    
    void main() {
        gl_Position = CC_MVPMatrix * a_position;
        v_fragmentColor = a_color;
        v_texCoord = a_texCoord;
    }
)";

inline const ZStringView gradient = R"(
    #ifdef GL_ES
    precision mediump float;
    #endif

    varying vec2 v_texCoord;
    uniform sampler2D u_texture;

    uniform vec3 u_colorRight;
    uniform vec3 u_colorLeft;
    uniform float u_opacity;

    void main() {
        vec4 tex = texture2D(u_texture, v_texCoord);
        vec3 gradient = mix(u_colorLeft, u_colorRight, clamp(v_texCoord.x + 0.27, 0.0, 1.0));
        vec3 finalColor = tex.rgb * gradient;
        gl_FragColor = vec4(finalColor, tex.a * u_opacity);
    }
)";

class InputNode;
class Path;

class Overlay : public CCLayerColor {
  
private:

    PlayLayer* m_playLayer = nullptr;
    CCLayerGradient* m_gradient = nullptr;
    CCLayerColor* m_ded = nullptr;
    CCLabelBMFont* m_accuracyLabel = nullptr;
    CCLabelBMFont* m_comboLabel = nullptr;
    NineSlice* m_accuracyBlur = nullptr;
    NineSlice* m_comboBlur = nullptr;
    CCParticleSystemQuad* m_comboParticles = nullptr;
    CCNode* m_labelsContainer = nullptr;

    std::array<bool, 4> m_pathsAvailable;
    std::array<bool, 4> m_killablePaths;
    std::array<bool, 4> m_pathsPressing;
    std::array<CCPoint, 4> m_pathPositions;
    std::array<CCParticleSystemQuad*, 4> m_particles = {nullptr, nullptr, nullptr, nullptr};
    std::array<InputNode*, 4> m_hitButtons = {nullptr, nullptr, nullptr, nullptr};
    std::array<Path*, 4> m_paths;
    std::vector<InputNode*> m_nodes;
    std::vector<NineSlice*> m_lights = {nullptr, nullptr, nullptr, nullptr};
    std::array<bool, 4> m_wasPressing = {false, false, false, false};

    int m_longy = -1;
    bool m_dead = false;
    bool m_completed = false;
    float m_timeDead = 0.f;
    int m_totalInputs = 0;
    int m_currentNote = 0;
    int m_currentInput = 0;
    float m_score = 0.f;
    int m_combo = 0;
    float m_currentAccuracy = 0.f;
    float m_targetAccuracy = 0.f;

    Overlay(PlayLayer*);

    bool init() override;

    void fadeOut(CCNode*);
    void initButtons();
    void updateHeheheha();
    void updateAccuracy(float);
    void spawnThingy(int, int);

public:

    static Overlay* create(PlayLayer*);

    void loadGame(const std::vector<gdr::Input<>>&, float = 0.f);
    void resetGame(float);
    void died();
    void completed();
    void tap(bool);
    void LABELS();
    
    void update(float) override;
    void setOpacity(GLubyte) override;

};