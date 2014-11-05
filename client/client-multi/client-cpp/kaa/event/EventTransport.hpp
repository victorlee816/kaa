/*
 * Copyright 2014 CyberVision, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef EVENTTRANSPORT_HPP_
#define EVENTTRANSPORT_HPP_

#include "kaa/KaaDefaults.hpp"

#ifdef KAA_USE_EVENTS

#include "kaa/channel/transport/IEventTransport.hpp"
#include "kaa/channel/transport/AbstractKaaTransport.hpp"
#include "kaa/channel/IKaaChannelManager.hpp"
#include "kaa/gen/EndpointGen.hpp"
#include "kaa/KaaThread.hpp"

namespace kaa {

class EventManager;

class EventTransport : public AbstractKaaTransport<TransportType::EVENT>, public IEventTransport {
public:
    EventTransport(EventManager& eventManager, IKaaChannelManager& channelManager);

    std::shared_ptr<EventSyncRequest>    createEventRequest(std::int32_t requestId);
    void                onEventResponse(const EventSyncResponse& response);
    void                onSyncResponseId(std::int32_t requestId);

    void sync();
private:
    KAA_MUTEX_DECLARE(eventsGuard_);

    EventManager & eventManager_;
    std::map<std::uint32_t, std::list<Event> >    events_;
};

}  // namespace kaa

#endif

#endif /* EVENTTRANSPORT_HPP_ */