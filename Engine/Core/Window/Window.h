#pragma once

#include"Core/pch.h"
#include"Core/Type/Object/RTTI.h"

namespace VIEngine {
    struct WindowConfiguration {
        uint16_t Width = 1280;
        uint16_t Height = 720;
        std::string Title = "VIEngine Application";
        uint16_t MaxFPS = 60;
        float MaxAllowedDeltaTime = 0.05f;
    };

    class VI_API Window {
        DECLARE_RTTI
    public:
        static Window* Create(const WindowConfiguration& windowConfig);
    public:
        virtual ~Window() = default;
        virtual bool Init() = 0;
        virtual void Update() = 0;
        virtual void Close() = 0;
        virtual void Shutdown() = 0;
        VI_FORCE_INLINE const WindowConfiguration& GetWindowConfiguration() const { return mConfiguration; }
        VI_FORCE_INLINE uint16_t GetWidth() const { return mConfiguration.Width; }
        VI_FORCE_INLINE uint16_t GetHeight() const { return mConfiguration.Height; }
        VI_FORCE_INLINE const std::string& GetTitle() const { return mConfiguration.Title; }
        VI_FORCE_INLINE uint16_t GetMaxFPS() const { return mConfiguration.MaxFPS; }
        VI_FORCE_INLINE float GetMaxAllowedDeltaTime() const { return mConfiguration.MaxAllowedDeltaTime; }
    protected:
        Window() = default;
        Window(uint16_t width, uint16_t height, const std::string& title);
        Window(const WindowConfiguration& windowConfig);
    protected:
        WindowConfiguration mConfiguration;
    };
}