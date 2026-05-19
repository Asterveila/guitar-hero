#include "GJBaseGameLayer.hpp"
#include "PlayLayer.hpp"
#include "Overlay.hpp"

void ProGJBaseGameLayer::handleButton(bool p0, int p1, bool p2) {
    #ifndef GEODE_IS_MOBILE

    if (PlayLayer::get()) {
        auto f = reinterpret_cast<ProPlayLayer*>(this)->m_fields.self();

        if (f->started && !f->dontIgnore) {
            return;
        }
    }

    #else

    if (PlayLayer::get() && p1 == 1) {
        auto f = reinterpret_cast<ProPlayLayer*>(this)->m_fields.self();

        if (f->started && f->overlay) {
            f->overlay->tap(p0);
        }
    }

    #endif

    GJBaseGameLayer::handleButton(p0, p1, p2);
}