#pragma once

#include<Core/Layer/Layer.h>
#include<Core/Renderer/GPUBuffer.h>
#include<Core/Renderer/InputAssembler.h>
#include<Core/Renderer/Shader.h>
#include<Core/Renderer/UniformBufferLayout.h>
#include<Core/Renderer/UniformBuffer.h>
#include<Core/Renderer/RenderPipelineLayout.h>
#include<Core/Renderer/RenderPipeline.h>

namespace VIEngine {
	class RenderCommand;
}

namespace MMDApp {

	class GameplayLayer : public VIEngine::Layer {
	public:
		GameplayLayer();
		~GameplayLayer();

		virtual void OnAttach() override;
		virtual void OnUpdate(float deltaTime) override;
		virtual void OnDetach() override;
		virtual bool OnKeyPressedEvent(const VIEngine::KeyPressedEvent& keyEvent) override;
		virtual bool OnKeyReleasedEvent(const VIEngine::KeyReleasedEvent& keyEvent) override;
		virtual bool OnMouseButtonPressedEvent(const VIEngine::MouseButtonPressedEvent& mouseEvent) override;
		virtual bool OnMouseButtonReleasedEvent(const VIEngine::MouseButtonReleasedEvent& mouseEvent) override;
		virtual bool OnMouseMovedEvent(const VIEngine::MouseMovedEvent& mouseEvent) override;
		virtual bool OnMouseScrolledEvent(const VIEngine::MouseScrolledEvent& mouseEvent) override;
	private:
		VIEngine::RenderCommand* mRenderCommand;
		VIEngine::RenderPipeline* mRenderPipeline;
		VIEngine::UniformBuffer* mMeshBuffer;
		VIEngine::UniformBuffer* mLightBuffer;
	};
}