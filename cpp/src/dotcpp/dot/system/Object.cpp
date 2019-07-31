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
#include <dot/system/type.hpp>
#include <dot/system/object.hpp>
#include <dot/detail/struct_wrapper.hpp>
#include <dot/system/string.hpp>
#include <dot/system/nullable.hpp>
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

    /// <summary>Construct object from local_minute by boxing.</summary>
    object::object(const local_minute & value) : base(new StructWrapperImpl<local_minute>(value)) {}

    /// <summary>Construct object from local_time by boxing.</summary>
    object::object(const local_time & value) : base(new StructWrapperImpl<local_time>(value)) {}

    /// <summary>Construct object from local_date by boxing.</summary>
    object::object(const local_date & value) : base(new StructWrapperImpl<local_date>(value)) {}

    /// <summary>Construct object from local_date_time by boxing.</summary>
    object::object(const local_date_time & value) : base(new StructWrapperImpl<local_date_time>(value)) {}

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

    /// <summary>Assign local_minute to object by boxing.</summary>
    object& object::operator=(const local_minute& value) { base::operator=(new StructWrapperImpl<local_minute>(value)); return *this; }

    /// <summary>Assign local_time to object by boxing.</summary>
    object& object::operator=(const local_time& value) { base::operator=(new StructWrapperImpl<local_time>(value)); return *this; }

    /// <summary>Assign local_date to object by boxing.</summary>
    object& object::operator=(const local_date& value) { base::operator=(new StructWrapperImpl<local_date>(value)); return *this; }

    /// <summary>Assign local_date_time to object by boxing.</summary>
    object& object::operator=(const local_date_time& value) { base::operator=(new StructWrapperImpl<local_date_time>(value)); return *this; }

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

    /// <summary>Convert object to local_minute by unboxing. Error if object does is not a boxed local_minute.</summary>
    object::operator local_minute() const { return *ptr<StructWrapperImpl<local_minute>>(*this); }

    /// <summary>Convert object to local_time by unboxing. Error if object does is not a boxed local_time.</summary>
    object::operator local_time() const { return *ptr<StructWrapperImpl<local_time>>(*this); }

    /// <summary>Convert object to local_date by unboxing. Error if object does is not a boxed local_date.</summary>
    object::operator local_date() const { return *ptr<StructWrapperImpl<local_date>>(*this); }

    /// <summary>Convert object to local_date_time by unboxing. Error if object does is not a boxed local_date_time.</summary>
    object::operator local_date_time() const { return *ptr<StructWrapperImpl<local_date_time>>(*this); }

    bool object::ReferenceEquals(object objA, object objB)
    {
        return &(*objA) == &(*objB);
    }
}
