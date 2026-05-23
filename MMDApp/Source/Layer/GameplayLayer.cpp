#include"Layer/GameplayLayer.h"
#include<Core/Input/InputEvent.h>
#include<Core/Logger/Logger.h>
#include<Core/Application.h>
#include<Core/Math/Math.h>
#include<Core/Renderer/RenderCommand.h>
#include<Core/Application.h>

namespace MMDApp {
    GameplayLayer::GameplayLayer() {
    }

    GameplayLayer::~GameplayLayer() {
    }

    void GameplayLayer::OnAttach() {
        using namespace VIEngine;

        mRenderCommand = RenderCommand::Create(VIEngine::ERenderCommandType::MAIN);

        struct Vertex {
            Math::Vector3 Position;
            Math::Vector2 TexCoords;
        };
        Vertex vertices[] = {
            {{-0.4f,  -0.7f,  0.0f}, {0.0f, 1.0f}},	// 左下
            {{-0.4f,   0.7f,  0.0f}, {0.0f, 0.0f}},	// 左上
            {{ 0.4f,  -0.7f,  0.0f}, {1.0f, 1.0f}},	// 右下
            {{ 0.4f,   0.7f,  0.0f}, {1.0f, 0.0f}}	// 右上
        };

        unsigned short indices[] = {
            0, 1, 2,
            1, 3, 2
        };
        GPUBuffer* vertexBuffer = GPUBuffer::Create(vertices, sizeof(vertices), _countof(vertices), 0);
        GPUBuffer* indexBuffer = GPUBuffer::Create(indices, sizeof(indices), _countof(indices), 0);

        InputAssembler* inputAssembler = InputAssembler::Create({{vertexBuffer}, indexBuffer, {
            VertexAttribute{"POSITION", 0, EFormat::FLOAT3, 0, EInputType::VERTEX},
            VertexAttribute{"TEXCOORD", 0, EFormat::FLOAT2, 0, EInputType::VERTEX},
        }});

        ShaderAttribute shaderAttribute = {};
        shaderAttribute.Stages.emplace_back(ShaderStage{EShaderStageFlag::VERTEX, "Assets/Shader/BasicVertexShader.vs.hlsl"});
        shaderAttribute.Stages.emplace_back(ShaderStage{EShaderStageFlag::PIXEL, "Assets/Shader/BasicPixelShader.ps.hlsl"});
        Shader* quadDefaultShader = Shader::Create(shaderAttribute);

        UniformBufferLayout* uniformLayout = UniformBufferLayout::Create(
            UniformBufferLayoutAttribute{
                EDescriptorRangeLayoutType::CONSTANT_BUFFER_VIEW,
                EShaderStageFlag::PIXEL,
                0, 0, 0
            }
        );
       
        mUniformBuffer = UniformBuffer::Create({uniformLayout});
        struct MeshData {
    		float color[4];
	    };
        MeshData meshData;
        meshData.color[0] = 1.0f;
        meshData.color[1] = 0.0f;
        meshData.color[2] = 0.0f;
        meshData.color[3] = 1.0f;
        mUniformBuffer->Push(&meshData, sizeof(MeshData));
        mUniformBuffer->Upload();

        RenderPipelineLayout* pipelineLayout = RenderPipelineLayout::Create(
            RenderPipelineLayoutAttribute{{uniformLayout}}
        );

        mRenderPipeline = RenderPipeline::Create(
            RenderPipelineAttribute{inputAssembler, pipelineLayout, quadDefaultShader}
        );
    }

    void GameplayLayer::OnUpdate(float deltaTime) {
        static float total = 0.0f;
        total += deltaTime;
        using namespace VIEngine;

        mRenderCommand->SetRenderTarget();
        mRenderCommand->SetBackBufferRender();
        mRenderCommand->ClearColor(Math::Sin(total), Math::Cos(total), 0.0f);
        
        static Application& app = Application::Get();
        mRenderCommand->SetViewPort(
            app.GetConfig().WindowConfig.Width,
            app.GetConfig().WindowConfig.Height,
            0.0f, 0.0f,
            0.0f, 1.0f
        );
        mRenderCommand->SetScissor(0.0f, 0.0f, 0.0f + app.GetConfig().WindowConfig.Width, 0.0f + app.GetConfig().WindowConfig.Height);

        mRenderCommand->SetRenderPipeline(mRenderPipeline);
        mRenderCommand->SetConstantsBuffer(mUniformBuffer);
        mRenderCommand->Draw();
        mRenderCommand->SetBackBufferPresent();
        mRenderCommand->Submit();
    }

    void GameplayLayer::OnDetach() {
        VI_FREE_MEMORY(mRenderCommand);
    }

    bool GameplayLayer::OnKeyPressedEvent(const VIEngine::KeyPressedEvent& keyEvent) {
        CORE_LOG_DEBUG("Key {0} is pressed", (int)keyEvent.GetKey());
        return true;
    }
    
    bool GameplayLayer::OnKeyReleasedEvent(const VIEngine::KeyReleasedEvent& keyEvent) {
        CORE_LOG_DEBUG("Key {0} is released", (int)keyEvent.GetKey());
        return false;
    }
    
    bool GameplayLayer::OnMouseButtonPressedEvent(const VIEngine::MouseButtonPressedEvent& mouseEvent) {
        CORE_LOG_DEBUG("Mouse {0} is pressed: (x: {1}, y: {2})", (int)mouseEvent.GetButton(), mouseEvent.GetPositionX(), mouseEvent.GetPositionY());
        return false;
    }
    
    bool GameplayLayer::OnMouseButtonReleasedEvent(const VIEngine::MouseButtonReleasedEvent& mouseEvent) {
        CORE_LOG_DEBUG("Mouse {0} is released: (x: {1}, y: {2})", (int)mouseEvent.GetButton(), mouseEvent.GetPositionX(), mouseEvent.GetPositionY());
        return false;
    }

    bool GameplayLayer::OnMouseMovedEvent(const VIEngine::MouseMovedEvent& mouseEvent) {
        CORE_LOG_TRACE("Mouse position: (x: {0}, y: {1}), offset: (x: {2}, y: {3})", 
            mouseEvent.GetPositionX(), 
            mouseEvent.GetPositionY(), 
            mouseEvent.GetOffsetX(), 
            mouseEvent.GetOffsetY()
        );
        return false;
    }

    bool GameplayLayer::OnMouseScrolledEvent(const VIEngine::MouseScrolledEvent& mouseEvent) {
        CORE_LOG_TRACE("Mouse scrolled: (Delta: {0})", mouseEvent.GetDelta());
        return false;
    }
}