#pragma once

#include"Core/Type/Object/RTTI.h"
#include"Core/Renderer/CommonDefine.h"

namespace VIEngine {
    class VI_API Shader {
        DECLARE_RTTI
    public:
        static Shader* Create(const ShaderAttribute& attribute);
    public:
        virtual ~Shader() = default;
        virtual const void* GetShaderByteCode(EShaderStageFlag stage) const = 0;
        virtual size_t GetShaderByteCodeSize(EShaderStageFlag stage) const = 0;
    protected:
        Shader() = default;
        Shader(const ShaderAttribute& attribute) noexcept : mAttribute(attribute) {}
        VI_FORCE_INLINE const std::vector<ShaderStage>& GetStages() const { return mAttribute.Stages; }
    protected:
        ShaderAttribute mAttribute;
    };
}