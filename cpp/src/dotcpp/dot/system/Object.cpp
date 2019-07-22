/*
Copyright (C) 2003-present CompatibL

This file is part of .C++, a native C++ implementation of
popular .NET class library APIs developed to facilitate
code reuse between C# and C++.

    http://github.com/dotcpp/dotcpp (source)
    http://dotcpp.org (documentation)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <dot/implement.hpp>
#include <dot/system/Type.hpp>
#include <dot/system/Object.hpp>
#include <dot/system/String.hpp>
#include <dot/system/Nullable.hpp>
#include <dot/nodatime/LocalTime.hpp>
#include <dot/nodatime/LocalDate.hpp>
#include <dot/nodatime/LocalDateTime.hpp>

namespace dot
{

    /// <summary>Construct Object from nullptr.</summary>
    Object::Object(nullptr_t) : base(nullptr) {}

    /// <summary>Construct Object from Ptr(ObjectImpl).</summary>
    Object::Object(const Ptr<ObjectImpl>& ptr) : base(ptr) {}

    /// <summary>Construct Object from ObjectImpl pointer.</summary>
    inline Object::Object(ObjectImpl* value) : base(value) {}

    /// <summary>Construct Object from String.</summary>
    Object::Object(const String& value) : base(value) {}

    /// <summary>Construct Object from const string.</summary>
    Object::Object(const char* value) : base(String(value)) {}

    /// <summary>Construct Object from bool by boxing.</summary>
    Object::Object(bool value) : base(new BoolImpl(value)) {}

    /// <summary>Construct Object from double by boxing.</summary>
    Object::Object(double value) : base(new DoubleImpl(value)) {}

    /// <summary>Construct Object from int by boxing.</summary>
    Object::Object(int value) : base(new IntImpl(value)) {}

    /// <summary>Construct Object from int by boxing.</summary>
    Object::Object(int64_t value) : base(new LongImpl(value)) {}

    /// <summary>Construct Object from char by boxing.</summary>
    Object::Object(char value) : base(new CharImpl(value)) {}

    /// <summary>Construct Object from LocalTime by boxing.</summary>
    Object::Object(const LocalTime & value) : base(new StructWrapperImpl<LocalTime>(value)) {}

    /// <summary>Construct Object from LocalDate by boxing.</summary>
    Object::Object(const LocalDate & value) : base(new StructWrapperImpl<LocalDate>(value)) {}

    /// <summary>Construct Object from LocalDateTime by boxing.</summary>
    Object::Object(const LocalDateTime & value) : base(new StructWrapperImpl<LocalDateTime>(value)) {}

    /// <summary>Forward to operator in type Ptr(T).</summary>
    bool Object::operator==(nullptr_t) const { return base::operator==(nullptr); }

    /// <summary>Forward to operator in type Ptr(T).</summary>
    bool Object::operator!=(nullptr_t) const { return base::operator!=(nullptr); }

    /// <summary>Assign nullptr to Object.</summary>
    Object& Object::operator=(nullptr_t) { base::operator=(nullptr); return *this; }

    /// <summary>Assign Ptr(T) to Object.</summary>
    Object& Object::operator=(const Ptr<ObjectImpl>& ptr) { base::operator=(ptr); return *this; }

    /// <summary>Assign String to Object by boxing.</summary>
    Object& Object::operator=(const String& value) { base::operator=(value); return *this; }

    /// <summary>Assign const string to Object by boxing.</summary>
    Object& Object::operator=(const char* value) { base::operator=(String(value)); return *this; }

    /// <summary>Assign bool to Object by boxing.</summary>
    Object& Object::operator=(bool value) { base::operator=(new BoolImpl(value)); return *this; }

    /// <summary>Assign double to Object by boxing.</summary>
    Object& Object::operator=(double value) { base::operator=(new DoubleImpl(value)); return *this; }

    /// <summary>Assign int to Object by boxing.</summary>
    Object& Object::operator=(int value) { base::operator=(new IntImpl(value)); return *this; }

    /// <summary>Assign int to Object by boxing.</summary>
    Object& Object::operator=(int64_t value) { base::operator=(new LongImpl(value)); return *this; }

    /// <summary>Assign int to Object by boxing.</summary>
    Object& Object::operator=(char value) { base::operator=(new CharImpl(value)); return *this; }

    /// <summary>Assign LocalTime to Object by boxing.</summary>
    Object& Object::operator=(const LocalTime& value) { base::operator=(new StructWrapperImpl<LocalTime>(value)); return *this; }

    /// <summary>Assign LocalDate to Object by boxing.</summary>
    Object& Object::operator=(const LocalDate& value) { base::operator=(new StructWrapperImpl<LocalDate>(value)); return *this; }

    /// <summary>Assign LocalDateTime to Object by boxing.</summary>
    Object& Object::operator=(const LocalDateTime& value) { base::operator=(new StructWrapperImpl<LocalDateTime>(value)); return *this; }

    /// <summary>Convert Object to bool by unboxing. Error if Object does is not a boxed double.</summary>
    Object::operator bool() const { return Ptr<BoolImpl>(*this)->value_; }

    /// <summary>Convert Object to double by unboxing. Error if Object does is not a boxed double.</summary>
    Object::operator double() const { return Ptr<DoubleImpl>(*this)->value_; }

    /// <summary>Convert Object to int by unboxing. Error if Object does is not a boxed int.</summary>
    Object::operator int() const { return Ptr<IntImpl>(*this)->value_; }

    /// <summary>Convert Object to long by unboxing. Error if Object does is not a boxed long.</summary>
    Object::operator int64_t() const { return Ptr<LongImpl>(*this)->value_; }

    /// <summary>Convert Object to long by unboxing. Error if Object does is not a boxed long.</summary>
    Object::operator char() const { return Ptr<CharImpl>(*this)->value_; }

    /// <summary>Convert Object to LocalTime by unboxing. Error if Object does is not a boxed LocalTime.</summary>
    Object::operator LocalTime() const { return *Ptr<StructWrapperImpl<LocalTime>>(*this); }

    /// <summary>Convert Object to LocalDate by unboxing. Error if Object does is not a boxed LocalDate.</summary>
    Object::operator LocalDate() const { return *Ptr<StructWrapperImpl<LocalDate>>(*this); }

    /// <summary>Convert Object to LocalDateTime by unboxing. Error if Object does is not a boxed LocalDateTime.</summary>
    Object::operator LocalDateTime() const { return *Ptr<StructWrapperImpl<LocalDateTime>>(*this); }
}
