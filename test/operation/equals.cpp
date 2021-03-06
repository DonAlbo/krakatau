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
#include <operation/equals.h>
#include <value/value.h>
#include <gtest/gtest.h>
#include <value/boolean.h>
#include <value/empty.h>
#include <rtti/rtti.h>
#include <value/string.h>

TEST(Equals, NotEnoughState) {
    MachineState s;
    Equals e;
    ASSERT_EQ(Operation::Result::ERROR, e.execute(s));
    s.stack().pop();
    s.stack().push(Value::empty());
    ASSERT_EQ(Operation::Result::ERROR, e.execute(s));
}

TEST(Equals, False) {
    MachineState s;
    Equals e;
    s.stack().push(Value::fromBoolean(true));
    s.stack().push(Value::empty());
    e.execute(s);
    ASSERT_EQ(1, s.stack().size());
    ASSERT_TRUE(s.stack().peek()->isOfClass<Value_Boolean>());
    ASSERT_FALSE(runtime_ptr_cast<Value_Boolean>(s.stack().pop())->value());
}

TEST(Equals, True) {
    MachineState s;
    Equals e;
    s.stack().push(Value::fromString("shark"));
    s.stack().push(Value::fromString("shark"));
    e.execute(s);
    ASSERT_EQ(1, s.stack().size());
    ASSERT_TRUE(s.stack().peek()->isOfClass<Value_Boolean>());
    ASSERT_TRUE(runtime_ptr_cast<Value_Boolean>(s.stack().pop())->value());
}
