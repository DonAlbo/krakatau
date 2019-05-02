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

#include <machine/state.h>
#include <operations/nop.h>
#include <value/value.h>
#include <gtest/gtest.h>
#include <value/empty.h>

TEST(Nop, Test) {
    MachineState s;
    s.stack().push(Value::empty());
    Nop nop;
    nop.execute(s);
    ASSERT_FALSE(s.stack().empty());
    ASSERT_TRUE(s.stack().peek()->isOfClass<Value_Empty>());
}
