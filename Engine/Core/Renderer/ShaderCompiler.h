#pragma once

#include"Core/Type/Object/RTTI.h"
#include"Core/Renderer/CommonDefine.h"

namespace VIEngine {
    class VI_API ShaderCompiler {
        DECLARE_RTTI
    public:
        static ShaderCompiler* Create();
        static ShaderCompiler* Create(const ShaderCompilerConfig& config);
    public:
        virtual ~ShaderCompiler() = default;
        VI_FORCE_INLINE const ShaderCompilerConfig& GetDefaultConfig() const { return mDefaultConfig; }
        VI_FORCE_INLINE void SetDefaultConfig(const ShaderCompilerConfig& config) { mDefaultConfig = config; }
    protected:
        ShaderCompiler() = default;
        ShaderCompiler(const ShaderCompilerConfig& config) noexcept : mDefaultConfig(config) {}
    protected:
        ShaderCompilerConfig mDefaultConfig;
    };
}