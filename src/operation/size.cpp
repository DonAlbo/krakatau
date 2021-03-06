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

#include <operation/size.h>
#include <rtti/rtti.h>
#include <value/tuple.h>
#include <value/string.h>
#include <value/table.h>
#include <machine/state.h>
#include <value/number.h>
#include <value/set.h>

Operation::Result Size::doExecute(MachineState& s) {
    auto value = s.stack().pop();
    auto tpl = runtime_ptr_cast<Value_Tuple>(value);
    auto str = runtime_ptr_cast<Value_String>(value);
    auto tbl = runtime_ptr_cast<Value_Table>(value);
    auto set = runtime_ptr_cast<Value_Set>(value);
    if (tpl) {
        s.stack().push(Value::fromNumber(tpl->size()));
    } else if (str) {
        s.stack().push(Value::fromNumber(str->value().size()));
    } else if (tbl) {
        s.stack().push(Value::fromNumber(tbl->size()));
    } else if (set) {
        s.stack().push(Value::fromNumber(set->size()));
    } else {
        s.stack().push(Value::fromNumber(1));
    }

    return Operation::Result::SUCCESS;
}
