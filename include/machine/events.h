/*
 * Copyright 2019 Google LLC
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

#ifndef STUFF_MACHINE_EVENTS
#define STUFF_MACHINE_EVENTS

#include <machine/state.h>
#include <function/block.h>
#include <operations/op.h>
#include <memory>

class MachineEventsListener : public std::enable_shared_from_this<MachineEventsListener> {
    public:

        virtual ~MachineEventsListener();

        virtual void onEnteringBlock(std::shared_ptr<Block>);
        virtual void onExecutingOperation(size_t);
        virtual void onLeavingBlock();
};

#endif
