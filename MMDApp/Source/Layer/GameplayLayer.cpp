#include"Layer/GameplayLayer.h"
#include<Core/Input/InputEvent.h>
#include<Core/Logger/Logger.h>
#include<Core/Application.h>
#include<Core/Math/Math.h>
#include<Core/Renderer/RenderCommand.h>

namespace MMDApp {
    GameplayLayer::GameplayLayer() {
    }

    GameplayLayer::~GameplayLayer() {

    }

    void GameplayLayer::OnAttach() {
        mRenderCommand = VIEngine::RenderCommand::Create(VIEngine::ERenderCommandType::MAIN);
        // mQuad = CreateQuad()

        // CreateQuad() {
        // Shader shader = CreateShader("quad.fs", "quad.ps")
        // VertexFormat vertexFormat;
        // vertexFormat.AddAttribute("POSITION", EAttributeFormat::FLOAT3)
        // vertexFormat.AddAttribute("COLOR", EAttributeFormat::FLOAT3)
        // vertexFormat.AddAttribute("TEXCOORD", EAttributeFormat::FLOAT2)
        // float vertices[] = {...}; 
        // VertexBuffer vertexBuffer = CreateVertexBuffer(vertexFormat, vertices, sizeof(vertices));
        // float indices[] = {...};
        // IndexBuffer indexBuffer = CreateIndexBuffer(indices, sizeof(indices));
        // return CreateVisual(vertexBuffer, indexBuffer, shader);
        // }
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