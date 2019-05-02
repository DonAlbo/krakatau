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

#ifndef STUFF_OPERATION_LOGICAL
#define STUFF_OPERATION_LOGICAL

#include <operations/op.h>
#include <value/boolean.h>
#include <memory>

class Binary_Logical_Operation : public Operation {
    public:
        virtual std::shared_ptr<Value> eval(Value_Boolean* v1, Value_Boolean* v2) = 0;
        Operation::Result execute(MachineState&) override;

        ABSTRACT_OPERATION_SUBCLASS(Binary_Logical_Operation, OperationType::BINARY_LOGICAL, Operation);
};

class Unary_Logical_Operation : public Operation {
    public:
        virtual std::shared_ptr<Value> eval(Value_Boolean* v1) = 0;
        Operation::Result execute(MachineState&) override;

        ABSTRACT_OPERATION_SUBCLASS(Unary_Logical_Operation, OperationType::UNARY_LOGICAL, Operation);
};

#define BINARY_LOGICAL_OPERATION(ClassName, OpType) \
class ClassName ## _Binary_Logical_Operation : public Binary_Logical_Operation { \
    public: \
        std::shared_ptr<Value> eval(Value_Boolean* v1, Value_Boolean* v2) override; \
        OPERATION_SUBCLASS(ClassName ## _Binary_Logical_Operation, OpType, Binary_Logical_Operation); \
}

BINARY_LOGICAL_OPERATION(And, OperationType::AND);
BINARY_LOGICAL_OPERATION(Or, OperationType::OR);
BINARY_LOGICAL_OPERATION(Xor, OperationType::XOR);

#undef BINARY_LOGICAL_OPERATION

#define UNARY_LOGICAL_OPERATION(ClassName, OpType) \
class ClassName ## _Unary_Logical_Operation : public Unary_Logical_Operation { \
    public: \
        std::shared_ptr<Value> eval(Value_Boolean* v) override; \
        OPERATION_SUBCLASS(ClassName ## _Unary_Logical_Operation, OpType, Unary_Logical_Operation); \
}

UNARY_LOGICAL_OPERATION(Not, OperationType::NOT);

#undef UNARY_LOGICAL_OPERATION

#endif
