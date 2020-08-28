#pragma once

#include <Window.h>
#include <GLFW/glfw3.h>

namespace Vortex {
    class LinuxWindow : public Window {
    public:
        LinuxWindow(const WindowProps& props);

        virtual ~LinuxWindow();

        void OnUpdate() override;

        inline unsigned int GetWidth() const override { return data.width; }

        inline unsigned int GetHeight() const override { return data.height; }

        inline void SetEventCallback(const EventCallbackFn& callback) override { data.eventCallback = callback; }

        void SetVSync(bool enabled) override;

        bool IsVSync() const override;

        inline virtual void* GetNativeWindow() const { return window; }

    private:
        virtual void Init(const WindowProps& props);

        virtual void Shutdown();

        GLFWwindow* window;

        struct WindowData {
            std::string title;
            unsigned int width, height;
            bool vSync;

            EventCallbackFn eventCallback;
        };

        WindowData data;
    };
}