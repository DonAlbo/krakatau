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

#ifndef STUFF_OPERATION_LOADSLOT
#define STUFF_OPERATION_LOADSLOT

#include <operation/base_op.h>
#include <string>

class Loadslot : public BaseOperation<Loadslot, OperationType::LOADSLOT> {
    public:
        static std::shared_ptr<Operation> fromByteStream(ByteStream*);
        static std::shared_ptr<Operation> fromParser(Parser*);

        Loadslot(const std::string&);
        virtual Operation::Result doExecute(MachineState&) override;
        virtual std::string describe() const override;
        size_t serialize(Serializer*) const override;
        bool equals(std::shared_ptr<Operation>) const override;

        std::shared_ptr<Operation> clone() const override;

        std::string key() const;
    private:
        std::string mKey;
};

#endif
