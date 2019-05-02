// Copyright 2019 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <operations/dup.h>
#include <machine/state.h>

Operation::Result Dup::execute(MachineState& s) {
    if (!s.stack().hasAtLeast(1)) {
        s.stack().push(Value::error(ErrorCode::INSUFFICIENT_ARGUMENTS));
        return Operation::Result::ERROR;
    }

    s.stack().push(s.stack().peek());
    return Operation::Result::SUCCESS;
}
