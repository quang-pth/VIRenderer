#include"Layer/GameplayLayer.h"
#include<Core/Input/InputEvent.h>
#include<Core/Logger/Logger.h>
#include<Core/Application.h>
#include<Core/Math/Math.h>
#include<Core/Renderer/RenderCommand.h>
#include<Core/Renderer/GPUBuffer.h>
#include<Core/Renderer/InputAssembler.h>

namespace MMDApp {
    GameplayLayer::GameplayLayer() {
    }

    GameplayLayer::~GameplayLayer() {
    }

    void GameplayLayer::OnAttach() {
        using namespace VIEngine;

        mRenderCommand = RenderCommand::Create(VIEngine::ERenderCommandType::MAIN);

        GPUBuffer* vertexBuffer = GPUBuffer::Create(nullptr, 0, 0, 0);
        GPUBuffer* indexBuffer = GPUBuffer::Create(nullptr, 0, 0, 0);
        InputAssembler* inputAssembler = InputAssembler::Create({{vertexBuffer}, indexBuffer, {
            VertexAttribute{"POSITION", 0, EFormat::FLOAT3, 0, EInputType::VERTEX},
            VertexAttribute{"TEXCOORD", 0, EFormat::FLOAT2, 0, EInputType::VERTEX},
        }});
        // shader = CreateShader()
        // pipelineState = CreatePipelineState(shader, {attribute})
    }

    void GameplayLayer::OnUpdate(float deltaTime) {
        static float total = 0.0f;
        total += deltaTime;
        using namespace VIEngine;
        mRenderCommand->BeginRecord();
        mRenderCommand->SetRenderTarget();
        mRenderCommand->SetBackBufferRender();
        mRenderCommand->ClearColor(Math::Sin(total), Math::Cos(total), 0.0f);
        mRenderCommand->SetBackBufferPresent();
        mRenderCommand->EndRecord();
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