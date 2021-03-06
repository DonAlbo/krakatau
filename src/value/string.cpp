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

#include <value/string.h>
#include <rtti/rtti.h>
#include <stream/serializer.h>
#include <stream/byte_stream.h>
#include <parser/parser.h>
#include <string>
#include <functional>
#include <locale>
#include <codecvt>
#include <value/empty.h>
#include <value/character.h>
#include <rtti/visitor.h>

Value_String::Value_String(const std::u32string& s) : mValue(s) {}

std::u32string Value_String::value() const {
    return mValue;
}

std::string Value_String::utf8() const {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
    return convert.to_bytes(value());
}

std::string Value_String::describe() const {
    return utf8();
}

bool Value_String::equals(std::shared_ptr<Value> v) const {
    auto str = runtime_ptr_cast<Value_String>(v);
    if (str == nullptr) return false;

    return str->value() == value();
}

size_t Value_String::serialize(Serializer* s) {
    const auto& val(utf8());
    const auto sz = val.size();

    size_t wr = s->writeNumber(MARKER, 1);
    wr += s->writeData(sz, (uint8_t*)val.data());
    return wr;
}

std::shared_ptr<Value> Value_String::fromByteStream(ByteStream* bs) {
    if (auto sv = bs->readData()) {
        return Value::fromString(sv.value());
    }
    
    return nullptr;
}

std::shared_ptr<Value> Value_String::fromParser(Parser* p) {
    auto valstr = p->expectedError(TokenKind::STRING);
    if (!valstr) return nullptr;
    auto value = valstr->value();
    return Value::fromString(value);
}

size_t Value_String::hash() const {
    return std::hash<std::u32string>()(value());
}

std::shared_ptr<Value> Value_String::clone() const {
    return Value::fromString(value());
}

size_t Value_String::size() const {
    return value().size();
}

std::shared_ptr<Value> Value_String::at(size_t i) const {
    if (i >= size()) return Value::empty();
    return Value::fromCharacter(value().at(i));
}

Value_String* Value_String::append(char32_t n) {
    mValue += n;
    return this;
}

Value_String* Value_String::append(const std::u32string& s) {
    mValue += s;
    return this;
}

AppendableValue<Value_String*, std::shared_ptr<Value>>::RetType Value_String::tryAppend(std::shared_ptr<Value> val) {
    if (auto chr = val->asClass<Value_Character>()) return append(chr->value());
    else if (auto str = val->asClass<Value_String>()) return append(str->value());
    else return ErrorCode::TYPE_MISMATCH;
}

Appendable::RetType Value_String::appendValue(std::shared_ptr<Value> val) {
    return std::visit(overloaded {
        [](Value_String* in) -> Appendable::RetType { return in; },
        [](ErrorCode in) -> Appendable::RetType { return in; },
    }, tryAppend(val));
}

std::shared_ptr<Value> Value_String::newEmptyOfSameType() {
    return Value::fromString("");
}
