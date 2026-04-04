#pragma once

#include"Core/pch.h"

namespace VIEngine {
	class VI_API Layer {
	public:
		Layer() = default; 
        virtual ~Layer() = default;
		virtual void OnAttach() {}
		virtual void OnUpdate() {}
		virtual void OnDetach() {}
	};

}