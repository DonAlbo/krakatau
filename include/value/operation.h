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

#ifndef STUFF_VALUE_OPERATION
#define STUFF_VALUE_OPERATION

#include <value/value.h>
#include <operations/op.h>

class MachineState;

class Value_Operation : public Value {
    public:
        static constexpr uint8_t MARKER = '!';

        static std::shared_ptr<Value> fromByteStream(ByteStream* bs);
        static std::shared_ptr<Value> fromParser(Parser*);

        Value_Operation(std::shared_ptr<Operation>);
        std::shared_ptr<Operation> value() const;
        virtual std::string describe() const override;
        bool equals(std::shared_ptr<Value>) const override;
        size_t serialize(Serializer*) override;

        size_t hash() const override;
        std::shared_ptr<Value> clone() const override;

        Operation::Result execute(MachineState&);

        VALUE_SUBCLASS(ValueType::OPERATION, Value);
    private:
        std::shared_ptr<Operation> mValue;
};

#endif
