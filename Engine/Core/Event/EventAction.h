#pragma once

#include"Core/Event/EventContext.h"
#include"Core/Event/EventParam.h"

namespace VIEngine {
	using EventAction = std::function<bool(const EventContext&)>;
    using EventActionHandle = uint16_t;
	using EventActionPair = std::pair<EventActionHandle, EventAction>;
	using EventActionList = std::vector<EventActionPair>;
}