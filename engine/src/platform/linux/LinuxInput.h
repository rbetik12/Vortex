#pragma once

#include "Input.h"
namespace Vortex {
    class VORTEX_API LinuxInput : public Input {
    protected:
        virtual bool GetKeyDownImpl(int keycode) override;

        bool GetKeyUpImpl(int keycode) override;

        bool GetMouseButtonPressedImpl(int button) override;

        float GetMouseXImpl() override;

        float GetMouseYImpl() override;

        std::pair<float, float> GetMousePositionImpl() override;
    };
}

