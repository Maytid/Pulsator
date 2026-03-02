#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <cmath>

using namespace geode::prelude;

ccColor3B lerpColorSafe(ccColor3B c1, ccColor3B c2, float blend) {
    float r = (float)c1.r + ((float)c2.r - (float)c1.r) * blend;
    float g = (float)c1.g + ((float)c2.g - (float)c1.g) * blend;
    float b = (float)c1.b + ((float)c2.b - (float)c1.b) * blend;

    return {
        static_cast<GLubyte>(r),
        static_cast<GLubyte>(g),
        static_cast<GLubyte>(b)
    };
}

class $modify(MyPlayLayer, PlayLayer) {
    struct Fields {
        float m_time = 0.f; 
    };

    void postUpdate(float dt) {
        PlayLayer::postUpdate(dt);

        float speedMult = static_cast<float>(Mod::get()->getSettingValue<double>("speed"));

        m_fields->m_time += (dt * speedMult);
        m_fields->m_time = std::fmod(m_fields->m_time, 3.14159f * 2.0f);
        float blend = (std::sin(m_fields->m_time * 3.0f) + 1.0f) / 2.0f;

        // --- PLAYER 1 ---
        if (Mod::get()->getSettingValue<bool>("enable-p1") && this->m_player1) {
            auto p1_c1 = Mod::get()->getSettingValue<ccColor3B>("p1-color1");
            auto p1_c2 = Mod::get()->getSettingValue<ccColor3B>("p1-color2");
            auto p1_s1 = Mod::get()->getSettingValue<ccColor3B>("p1-sec1");
            auto p1_s2 = Mod::get()->getSettingValue<ccColor3B>("p1-sec2");
            
            this->m_player1->setColor(lerpColorSafe(p1_c1, p1_c2, blend));
            this->m_player1->setSecondColor(lerpColorSafe(p1_s1, p1_s2, blend));

            if (this->m_player1->m_isDart && this->m_player1->m_waveTrail) {
                auto w1 = Mod::get()->getSettingValue<ccColor3B>("p1-wave1");
                auto w2 = Mod::get()->getSettingValue<ccColor3B>("p1-wave2");
                this->m_player1->m_waveTrail->setColor(lerpColorSafe(w1, w2, blend));
            }
        }

        // --- PLAYER 2 ---
        if (Mod::get()->getSettingValue<bool>("enable-p2") && this->m_player2) {
            auto p2_c1 = Mod::get()->getSettingValue<ccColor3B>("p2-color1");
            auto p2_c2 = Mod::get()->getSettingValue<ccColor3B>("p2-color2");
            auto p2_s1 = Mod::get()->getSettingValue<ccColor3B>("p2-sec1");
            auto p2_s2 = Mod::get()->getSettingValue<ccColor3B>("p2-sec2");
            
            this->m_player2->setColor(lerpColorSafe(p2_c1, p2_c2, blend));
            this->m_player2->setSecondColor(lerpColorSafe(p2_s1, p2_s2, blend));

            if (this->m_player2->m_isDart && this->m_player2->m_waveTrail) {
                auto w1 = Mod::get()->getSettingValue<ccColor3B>("p2-wave1");
                auto w2 = Mod::get()->getSettingValue<ccColor3B>("p2-wave2");
                this->m_player2->m_waveTrail->setColor(lerpColorSafe(w1, w2, blend));
            }
        }
    }
};