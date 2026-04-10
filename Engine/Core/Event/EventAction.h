#pragma once

#include"Core/Event/EventContext.h"
#include"Core/Event/EventParam.h"

namespace VIEngine {
	template<typename T>
	using EventAction = std::function<bool(const T&)>;

    using EventActionHandle = uint16_t;
	
	template<typename T>
	using EventActionPair = std::pair<EventActionHandle, EventAction<T>>;
	
	template<typename T>
	using EventActionList = std::vector<EventActionPair<T>>;
}