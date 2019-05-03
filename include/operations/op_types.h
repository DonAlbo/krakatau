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

#ifndef STUFF_OPERATIONS_OPTYPES
#define STUFF_OPERATIONS_OPTYPES

#include <stdint.h>
#include <string>
#include <limits>
#include <rtti/enum.h>
#include <optional>
#include <type_traits>
#include <operations/op_loader.h>

class ByteStream;
class Parser;

#define OPERATION_TYPE(NAME, TOKEN, STRING, NUMBER) \
  NAME = NUMBER,
#define OPERATION_TYPE_ALIAS(NAME, NUMBER) \
  NAME = NUMBER,

enum class OperationType : uint32_t {
#include <operations/op_types.def>
};

NUMERIC_LIMITS(OperationType);

#define ABSTRACT_OPERATION_SUBCLASS( SELFNAME, NEWCLASSID, BASECLASSNAME ) \
  private: \
    using self = SELFNAME; \
  public: \
    OperationType getClassId() const override { return NEWCLASSID; }; \
    static OperationType getStaticClassId() { return NEWCLASSID; }; \
     \
    bool isOfType(OperationType aID) const override { \
      return ((aID == NEWCLASSID) || BASECLASSNAME::isOfType(aID)); \
    }; \


#define OPERATION_SUBCLASS( SELFNAME, NEWCLASSID, BASECLASSNAME ) \
  private: \
    using self = SELFNAME; \
    template<typename T> \
    static constexpr bool is_dc = std::is_default_constructible<T>::value; \
  public: \
    OperationType getClassId() const override { return NEWCLASSID; }; \
    static OperationType getStaticClassId() { return NEWCLASSID; }; \
     \
    bool isOfType(OperationType aID) const override { \
      return ((aID == NEWCLASSID) || BASECLASSNAME::isOfType(aID)); \
    }; \
    template<typename T = self, typename = typename std::enable_if<is_dc<T>>::type> \
    static std::shared_ptr<Operation> fromByteStream(ByteStream*) { \
      return std::shared_ptr<Operation>(new T()); \
    } \
    template<typename T = self, typename = typename std::enable_if<is_dc<T>>::type> \
    static std::shared_ptr<Operation> fromParser(Parser*) { \
      return std::shared_ptr<Operation>(new T()); \
    } \
}; \
OP_LOADER(NEWCLASSID, SELFNAME);

std::string operationTypeToString(OperationType);
std::optional<OperationType> operationTypeFromByteStream(ByteStream*);
std::optional<OperationType> operationTypeFromString(const std::string&);

#endif