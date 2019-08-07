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

#include <dot/precompiled.hpp>
#include <dot/implement.hpp>
#include <dot/system/type.hpp>
#include <dot/system/object.hpp>
#include <dot/detail/struct_wrapper.hpp>
#include <dot/system/string.hpp>
#include <dot/system/nullable.hpp>
#include <dot/noda_time/local_minute.hpp>
#include <dot/noda_time/local_time.hpp>
#include <dot/noda_time/local_date.hpp>
#include <dot/noda_time/local_date_time.hpp>

namespace dot
{

    /// Construct object from nullptr.
    object::object(nullptr_t) : base(nullptr) {}

    /// Construct object from ptr(object_impl).
    object::object(const ptr<object_impl>& p) : base(p) {}

    /// Construct object from object_impl pointer.
    object::object(object_impl* value) : base(value) {}

    /// Construct object from string.
    object::object(const string& value) : base(value) {}

    /// Construct object from const string.
    object::object(const char* value) : base(string(value)) {}

    /// Construct object from bool by boxing.
    object::object(bool value) : base(new bool_impl(value)) {}

    /// Construct object from double by boxing.
    object::object(double value) : base(new double_impl(value)) {}

    /// Construct object from int by boxing.
    object::object(int value) : base(new int_impl(value)) {}

    /// Construct object from int by boxing.
    object::object(int64_t value) : base(new long_impl(value)) {}

    /// Construct object from char by boxing.
    object::object(char value) : base(new char_impl(value)) {}

    /// Construct object from local_minute by boxing.
    object::object(const local_minute & value) : base(new struct_wrapper_impl<local_minute>(value)) {}

    /// Construct object from local_time by boxing.
    object::object(const local_time & value) : base(new struct_wrapper_impl<local_time>(value)) {}

    /// Construct object from local_date by boxing.
    object::object(const local_date & value) : base(new struct_wrapper_impl<local_date>(value)) {}

    /// Construct object from local_date_time by boxing.
    object::object(const local_date_time & value) : base(new struct_wrapper_impl<local_date_time>(value)) {}

    /// Forward to operator in type ptr(T).
    bool object::operator==(nullptr_t) const { return base::operator==(nullptr); }

    /// Forward to operator in type ptr(T).
    bool object::operator!=(nullptr_t) const { return base::operator!=(nullptr); }

    /// Assign nullptr to object.
    object& object::operator=(nullptr_t) { base::operator=(nullptr); return *this; }

    /// Assign ptr(T) to object.
    object& object::operator=(const ptr<object_impl>& p) { base::operator=(p); return *this; }

    /// Assign string to object by boxing.
    object& object::operator=(const string& value) { base::operator=(value); return *this; }

    /// Assign const string to object by boxing.
    object& object::operator=(const char* value) { base::operator=(string(value)); return *this; }

    /// Assign bool to object by boxing.
    object& object::operator=(bool value) { base::operator=(new bool_impl(value)); return *this; }

    /// Assign double to object by boxing.
    object& object::operator=(double value) { base::operator=(new double_impl(value)); return *this; }

    /// Assign int to object by boxing.
    object& object::operator=(int value) { base::operator=(new int_impl(value)); return *this; }

    /// Assign int to object by boxing.
    object& object::operator=(int64_t value) { base::operator=(new long_impl(value)); return *this; }

    /// Assign int to object by boxing.
    object& object::operator=(char value) { base::operator=(new char_impl(value)); return *this; }

    /// Assign local_minute to object by boxing.
    object& object::operator=(const local_minute& value) { base::operator=(new struct_wrapper_impl<local_minute>(value)); return *this; }

    /// Assign local_time to object by boxing.
    object& object::operator=(const local_time& value) { base::operator=(new struct_wrapper_impl<local_time>(value)); return *this; }

    /// Assign local_date to object by boxing.
    object& object::operator=(const local_date& value) { base::operator=(new struct_wrapper_impl<local_date>(value)); return *this; }

    /// Assign local_date_time to object by boxing.
    object& object::operator=(const local_date_time& value) { base::operator=(new struct_wrapper_impl<local_date_time>(value)); return *this; }

    /// Convert object to bool by unboxing. Error if object does is not a boxed double.
    object::operator bool() const { return ptr<bool_impl>(*this)->value_; }

    /// Convert object to double by unboxing. Error if object does is not a boxed double.
    object::operator double() const { return ptr<double_impl>(*this)->value_; }

    /// Convert object to int by unboxing. Error if object does is not a boxed int.
    object::operator int() const { return ptr<int_impl>(*this)->value_; }

    /// Convert object to long by unboxing. Error if object does is not a boxed long.
    object::operator int64_t() const { return ptr<long_impl>(*this)->value_; }

    /// Convert object to long by unboxing. Error if object does is not a boxed long.
    object::operator char() const { return ptr<char_impl>(*this)->value_; }

    /// Convert object to local_minute by unboxing. Error if object does is not a boxed local_minute.
    object::operator local_minute() const { return *ptr<struct_wrapper_impl<local_minute>>(*this); }

    /// Convert object to local_time by unboxing. Error if object does is not a boxed local_time.
    object::operator local_time() const { return *ptr<struct_wrapper_impl<local_time>>(*this); }

    /// Convert object to local_date by unboxing. Error if object does is not a boxed local_date.
    object::operator local_date() const { return *ptr<struct_wrapper_impl<local_date>>(*this); }

    /// Convert object to local_date_time by unboxing. Error if object does is not a boxed local_date_time.
    object::operator local_date_time() const { return *ptr<struct_wrapper_impl<local_date_time>>(*this); }

    bool object::ReferenceEquals(object objA, object objB)
    {
        return &(*objA) == &(*objB);
    }
}
