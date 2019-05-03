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

#include <value/value.h>
#include <gtest/gtest.h>
#include <function/block.h>
#include <value/number.h>
#include <value/boolean.h>
#include <value/empty.h>
#include <value/string.h>
#include <value/block.h>
#include <value/operation.h>
#include <value/error.h>
#include <value/tuple.h>
#include <value/type.h>
#include <rtti/rtti.h>
#include <value/table.h>
#include <operations/at.h>
#include <error/error_codes.h>

TEST(Value, Number) {
    auto v(Value::fromNumber(123));
    ASSERT_TRUE(v->isOfClass<Value_Number>());
    ASSERT_EQ(123, runtime_ptr_cast<Value_Number>(v)->value());

    ASSERT_FALSE(v->equals(Value::fromNumber(4)));
    ASSERT_FALSE(v->equals(Value::empty()));
    ASSERT_TRUE(v->equals(Value::fromNumber(123)));
}

TEST(Value, Empty) {
    auto v(Value::empty());
    ASSERT_TRUE(v->isOfClass<Value_Empty>());

    ASSERT_FALSE(v->equals(Value::fromNumber(4)));
    ASSERT_TRUE(v->equals(Value::empty()));
}

TEST(Value, Boolean) {
    auto v(Value::fromBoolean(false));
    ASSERT_TRUE(v->isOfClass<Value_Boolean>());
    ASSERT_EQ(false, runtime_ptr_cast<Value_Boolean>(v)->value());

    ASSERT_FALSE(v->equals(Value::fromBoolean(true)));
    ASSERT_FALSE(v->equals(Value::fromNumber(1221)));
    ASSERT_TRUE(v->equals(Value::fromBoolean(false)));
}

TEST(Value, Block) {
    auto v(Value::fromBlock(std::make_shared<Block>()));
    ASSERT_TRUE(v->isOfClass<Value_Block>());
    ASSERT_NE(nullptr, runtime_ptr_cast<Value_Block>(v));
    ASSERT_EQ(0, runtime_ptr_cast<Value_Block>(v)->value()->size());

    ASSERT_FALSE(v->equals(Value::fromBoolean(true)));
    ASSERT_TRUE(v->equals(Value::fromBlock(std::make_shared<Block>())));
    ASSERT_TRUE(v->equals(v));
}

TEST(Value, TypeMismatch) {
    auto v(Value::fromNumber(123));
    ASSERT_FALSE(v->isOfClass<Value_Boolean>());
    ASSERT_FALSE(v->isOfClass<Value_Empty>());
    ASSERT_EQ(nullptr, runtime_ptr_cast<Value_Boolean>(v));
    ASSERT_FALSE(v->isOfClass<Value_Block>());
    ASSERT_NE(nullptr, v->asClass<Value_Number>());
    ASSERT_EQ(nullptr, v->asClass<Value_Empty>());
    ASSERT_EQ(nullptr, v->asClass<Value_Boolean>());
}

TEST(Value, Operation) {
    auto v(Value::fromOperation(std::shared_ptr<Operation>(new At())));
    ASSERT_TRUE(v->isOfClass<Value_Operation>());
    ASSERT_NE(nullptr, runtime_ptr_cast<Value_Operation>(v));
    ASSERT_EQ("at", v->describe());

    ASSERT_FALSE(v->equals(Value::fromBoolean(true)));
    ASSERT_FALSE(v->equals(Value::fromNumber(1221)));
    ASSERT_TRUE(Value::fromOperation(std::shared_ptr<Operation>(new At())));
}

TEST(Value, Print) {
    ASSERT_EQ("4556", Value::fromNumber(4556)->describe());
    ASSERT_EQ("empty", Value::empty()->describe());
    ASSERT_EQ("true", Value::fromBoolean(true)->describe());
    ASSERT_EQ("false", Value::fromBoolean(false)->describe());
    ASSERT_EQ(" hello ", Value::fromString(" hello ")->describe());
    auto tpl_val = Value::tuple();
    auto tpl = runtime_ptr_cast<Value_Tuple>(tpl_val);
    ASSERT_EQ("(empty, hello, 12)", tpl->append(Value::empty())->append(Value::fromString("hello"))->append(Value::fromNumber(12))->describe());
    ASSERT_EQ("string", Value::type(ValueType::STRING)->describe());
    auto tbl_val = Value::table();
    auto tbl = tbl_val->asClass<Value_Table>();
    tbl->append(Value::fromNumber(123), Value::fromNumber(42));
    ASSERT_EQ("[123 -> 42]", tbl_val->describe());
}

TEST(Value, String) {
    auto v(Value::fromString("hello world"));
    ASSERT_TRUE(v->isOfClass<Value_String>());
    ASSERT_EQ("hello world", runtime_ptr_cast<Value_String>(v)->value());

    ASSERT_FALSE(v->equals(Value::fromBoolean(true)));
    ASSERT_FALSE(v->equals(Value::fromString("   abc   ")));
    ASSERT_TRUE(v->equals(Value::fromString("hello world")));
}

TEST(Value, Error) {
    auto v(Value::error(ErrorCode::DIV_BY_ZERO));
    ASSERT_TRUE(v->isOfClass<Value_Error>());
    ASSERT_EQ(ErrorCode::DIV_BY_ZERO, v->asClass<Value_Error>()->value());

    ASSERT_FALSE(v->equals(Value::fromBoolean(true)));
    ASSERT_FALSE(v->equals(Value::error(ErrorCode::TYPE_MISMATCH)));
    ASSERT_TRUE(v->equals(Value::error(ErrorCode::DIV_BY_ZERO)));
}

TEST(Value, Tuple) {
    Value_Tuple vp;
    ASSERT_EQ(0, vp.size());
    ASSERT_TRUE(vp.at(12)->isOfClass<Value_Empty>());
    vp.append(Value::empty());
    ASSERT_EQ(1, vp.size());
    ASSERT_TRUE(vp.at(0)->isOfClass<Value_Empty>());
    vp.append(Value::fromNumber(12));
    ASSERT_EQ(2, vp.size());
    ASSERT_TRUE(vp.at(0)->isOfClass<Value_Empty>());
    ASSERT_TRUE(vp.at(1)->isOfClass<Value_Number>());
    vp.append(Value::fromBoolean(false));
    ASSERT_EQ(3, vp.size());
    ASSERT_TRUE(vp.at(0)->isOfClass<Value_Empty>());
    ASSERT_TRUE(vp.at(1)->isOfClass<Value_Number>());
    ASSERT_TRUE(vp.at(2)->isOfClass<Value_Boolean>());
    ASSERT_TRUE(vp.at(3)->isOfClass<Value_Empty>());
}

TEST(Value, Type) {
    auto v(Value::type(ValueType::NUMBER));
    ASSERT_TRUE(v->isOfClass<Value_Type>());
    ASSERT_EQ(ValueType::NUMBER, runtime_ptr_cast<Value_Type>(v)->value());

    ASSERT_TRUE(v->equals(Value::type(ValueType::NUMBER)));
    ASSERT_FALSE(v->equals(Value::empty()));
    ASSERT_FALSE(v->equals(Value::type(ValueType::STRING)));
}

TEST(Value, Table) {
    auto tbl_val = Value::table();
    auto tbl = runtime_ptr_cast<Value_Table>(tbl_val);
    ASSERT_EQ(0, tbl->size());
    tbl->append(Value::fromNumber(123), Value::fromNumber(42));
    ASSERT_EQ(1, tbl->size());
    ASSERT_TRUE(tbl->keyAt(0)->isOfClass<Value_Number>());
    ASSERT_TRUE(tbl->valueAt(0)->isOfClass<Value_Number>());
    ASSERT_TRUE(tbl->find(Value::fromNumber(123))->isOfClass<Value_Number>());
    tbl->append(Value::fromNumber(456), Value::fromBoolean(false));
    ASSERT_EQ(2, tbl->size());
    ASSERT_TRUE(tbl->find(Value::fromNumber(123))->isOfClass<Value_Number>());
    ASSERT_TRUE(tbl->find(Value::fromNumber(456))->isOfClass<Value_Boolean>());
}