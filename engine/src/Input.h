#pragma once

#include "Core.h"
namespace Vortex {
    class VORTEX_API Input {
    public:
        inline static bool GetKeyDown(int keycode) {instance->GetKeyDownImpl(keycode);}

        inline static bool GetKeyUp(int keycode) {instance->GetKeyUpImpl(keycode);}

        inline static bool GetMouseButtonPressed(int button) {return instance->GetMouseButtonPressedImpl(button);}

        inline static float GetMouseX() {return instance->GetMouseXImpl();}

        inline static float GetMouseY() {return instance->GetMouseYImpl();}

        inline static std::pair<float, float> GetMousePosition() {return instance->GetMousePositionImpl();}

    protected:
        virtual bool GetKeyDownImpl(int keycode) = 0;
        virtual bool GetKeyUpImpl(int keycode) = 0;
        virtual bool GetMouseButtonPressedImpl(int button) = 0;
        virtual float GetMouseXImpl() = 0;
        virtual float GetMouseYImpl() = 0;
        virtual std::pair<float, float> GetMousePositionImpl() = 0;

    private:
        static Input* instance;
    };
}