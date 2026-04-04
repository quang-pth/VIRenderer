#pragma once

#include<Core/Layer/Layer.h>

class GameplayLayer : public VIEngine::Layer {
public:
	GameplayLayer();
	~GameplayLayer();

	virtual void OnAttach() override;
	virtual void OnUpdate() override;
	virtual void OnDetach() override;
};