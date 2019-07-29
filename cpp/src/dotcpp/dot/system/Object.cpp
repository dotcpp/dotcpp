/*
Copyright (C) 2015-present The DotCpp Authors.

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
#include <dot/system/object.hpp>
#include <dot/detail/struct_wrapper.hpp>
#include <dot/system/string.hpp>
#include <dot/system/Nullable.hpp>
#include <dot/noda_time/LocalMinute.hpp>
#include <dot/noda_time/LocalTime.hpp>
#include <dot/noda_time/LocalDate.hpp>
#include <dot/noda_time/LocalDateTime.hpp>

namespace dot
{

    /// <summary>Construct object from nullptr.</summary>
    object::object(nullptr_t) : base(nullptr) {}

    /// <summary>Construct object from ptr(object_impl).</summary>
    object::object(const ptr<object_impl>& p) : base(p) {}

    /// <summary>Construct object from object_impl pointer.</summary>
    object::object(object_impl* value) : base(value) {}

    /// <summary>Construct object from string.</summary>
    object::object(const string& value) : base(value) {}

    /// <summary>Construct object from const string.</summary>
    object::object(const char* value) : base(string(value)) {}

    /// <summary>Construct object from bool by boxing.</summary>
    object::object(bool value) : base(new BoolImpl(value)) {}

    /// <summary>Construct object from double by boxing.</summary>
    object::object(double value) : base(new DoubleImpl(value)) {}

    /// <summary>Construct object from int by boxing.</summary>
    object::object(int value) : base(new IntImpl(value)) {}

    /// <summary>Construct object from int by boxing.</summary>
    object::object(int64_t value) : base(new LongImpl(value)) {}

    /// <summary>Construct object from char by boxing.</summary>
    object::object(char value) : base(new CharImpl(value)) {}

    /// <summary>Construct object from LocalMinute by boxing.</summary>
    object::object(const LocalMinute & value) : base(new StructWrapperImpl<LocalMinute>(value)) {}

    /// <summary>Construct object from LocalTime by boxing.</summary>
    object::object(const LocalTime & value) : base(new StructWrapperImpl<LocalTime>(value)) {}

    /// <summary>Construct object from LocalDate by boxing.</summary>
    object::object(const LocalDate & value) : base(new StructWrapperImpl<LocalDate>(value)) {}

    /// <summary>Construct object from LocalDateTime by boxing.</summary>
    object::object(const LocalDateTime & value) : base(new StructWrapperImpl<LocalDateTime>(value)) {}

    /// <summary>Forward to operator in type ptr(T).</summary>
    bool object::operator==(nullptr_t) const { return base::operator==(nullptr); }

    /// <summary>Forward to operator in type ptr(T).</summary>
    bool object::operator!=(nullptr_t) const { return base::operator!=(nullptr); }

    /// <summary>Assign nullptr to object.</summary>
    object& object::operator=(nullptr_t) { base::operator=(nullptr); return *this; }

    /// <summary>Assign ptr(T) to object.</summary>
    object& object::operator=(const ptr<object_impl>& p) { base::operator=(p); return *this; }

    /// <summary>Assign string to object by boxing.</summary>
    object& object::operator=(const string& value) { base::operator=(value); return *this; }

    /// <summary>Assign const string to object by boxing.</summary>
    object& object::operator=(const char* value) { base::operator=(string(value)); return *this; }

    /// <summary>Assign bool to object by boxing.</summary>
    object& object::operator=(bool value) { base::operator=(new BoolImpl(value)); return *this; }

    /// <summary>Assign double to object by boxing.</summary>
    object& object::operator=(double value) { base::operator=(new DoubleImpl(value)); return *this; }

    /// <summary>Assign int to object by boxing.</summary>
    object& object::operator=(int value) { base::operator=(new IntImpl(value)); return *this; }

    /// <summary>Assign int to object by boxing.</summary>
    object& object::operator=(int64_t value) { base::operator=(new LongImpl(value)); return *this; }

    /// <summary>Assign int to object by boxing.</summary>
    object& object::operator=(char value) { base::operator=(new CharImpl(value)); return *this; }

    /// <summary>Assign LocalMinute to object by boxing.</summary>
    object& object::operator=(const LocalMinute& value) { base::operator=(new StructWrapperImpl<LocalMinute>(value)); return *this; }

    /// <summary>Assign LocalTime to object by boxing.</summary>
    object& object::operator=(const LocalTime& value) { base::operator=(new StructWrapperImpl<LocalTime>(value)); return *this; }

    /// <summary>Assign LocalDate to object by boxing.</summary>
    object& object::operator=(const LocalDate& value) { base::operator=(new StructWrapperImpl<LocalDate>(value)); return *this; }

    /// <summary>Assign LocalDateTime to object by boxing.</summary>
    object& object::operator=(const LocalDateTime& value) { base::operator=(new StructWrapperImpl<LocalDateTime>(value)); return *this; }

    /// <summary>Convert object to bool by unboxing. Error if object does is not a boxed double.</summary>
    object::operator bool() const { return ptr<BoolImpl>(*this)->value_; }

    /// <summary>Convert object to double by unboxing. Error if object does is not a boxed double.</summary>
    object::operator double() const { return ptr<DoubleImpl>(*this)->value_; }

    /// <summary>Convert object to int by unboxing. Error if object does is not a boxed int.</summary>
    object::operator int() const { return ptr<IntImpl>(*this)->value_; }

    /// <summary>Convert object to long by unboxing. Error if object does is not a boxed long.</summary>
    object::operator int64_t() const { return ptr<LongImpl>(*this)->value_; }

    /// <summary>Convert object to long by unboxing. Error if object does is not a boxed long.</summary>
    object::operator char() const { return ptr<CharImpl>(*this)->value_; }

    /// <summary>Convert object to LocalMinute by unboxing. Error if object does is not a boxed LocalMinute.</summary>
    object::operator LocalMinute() const { return *ptr<StructWrapperImpl<LocalMinute>>(*this); }

    /// <summary>Convert object to LocalTime by unboxing. Error if object does is not a boxed LocalTime.</summary>
    object::operator LocalTime() const { return *ptr<StructWrapperImpl<LocalTime>>(*this); }

    /// <summary>Convert object to LocalDate by unboxing. Error if object does is not a boxed LocalDate.</summary>
    object::operator LocalDate() const { return *ptr<StructWrapperImpl<LocalDate>>(*this); }

    /// <summary>Convert object to LocalDateTime by unboxing. Error if object does is not a boxed LocalDateTime.</summary>
    object::operator LocalDateTime() const { return *ptr<StructWrapperImpl<LocalDateTime>>(*this); }

    bool object::ReferenceEquals(object objA, object objB)
    {
        return &(*objA) == &(*objB);
    }
}
