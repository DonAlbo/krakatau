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
#include <operation/dup.h>
#include <value/value.h>
#include <gtest/gtest.h>
#include <value/boolean.h>

TEST(Dup, EmptyStack) {
    MachineState s;
    Dup dup;
    ASSERT_EQ(Operation::Result::ERROR, dup.execute(s));
}

TEST(Dup, ValidElement) {
    MachineState s;
    Dup dup;
    s.stack().push(Value::fromBoolean(true));
    ASSERT_EQ(Operation::Result::SUCCESS, dup.execute(s));
    ASSERT_TRUE(s.stack().pop()->isOfClass<Value_Boolean>());
    ASSERT_FALSE(s.stack().empty());
    ASSERT_TRUE(s.stack().pop()->isOfClass<Value_Boolean>());
}
