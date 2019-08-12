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

#pragma once

#include <dot/declare.hpp>
#include <dot/system/ptr.hpp>
#include <dot/system/object_impl.hpp>
#include <dot/system/exception.hpp>
#include <dot/system/string.hpp>
#include <dot/system/enum_impl.hpp>

namespace dot
{
    template <class T> class nullable;
    class local_minute;
    class local_time;
    class local_date;
    class local_date_time;
    template <class T> class enum_impl;
    template <class T> class struct_wrapper_impl;
    template <class T> using struct_wrapper = ptr<struct_wrapper_impl<T>>;
    template <class T> type typeof();

    namespace detail
    {
        template<class W, class T> class inherit_to_string;
        template<class W, class T> class inherit_get_hashcode;
        template<class W, class T> class inherit_equals;
    }

    /// Adds support for boxing value types to ptr(object_impl).
    class DOT_CLASS object : public ptr<object_impl>
    {
        typedef ptr<object_impl> base;

    public: // CONSTRUCTORS

        /// Default constructor to create untyped object.
        ///
        /// This constructor is used, among other things,
        /// as argument to lock(...) to provide thread safety.
        object() = default;

        /// Construct object from nullptr.
        object(nullptr_t);

        /// Construct object from ptr(object_impl).
        object(const ptr<object_impl>& p);

        /// Construct object from ptr(T).
        template <class T>
        object(const ptr<T>& p) : base(p) {}

        /// Construct object from object_impl pointer.
        object(object_impl* value);

        /// Construct object from string.
        object(const string& value);

        /// Construct object from const string.
        object(const char* value);

        /// Construct object from bool by boxing.
        object(bool value);

        /// Construct object from double by boxing.
        object(double value);

        /// Construct object from int by boxing.
        object(int value);

        /// Construct object from int by boxing.
        object(int64_t value);

        /// Construct object from char by boxing.
        object(char value);

        /// Construct object from nullable by boxing.
        template <class T>
        object(const nullable<T>& value) { if (value.has_value()) *this = value.value(); }

        /// Construct object from local_minute by boxing.
        object(const local_minute & value);

        /// Construct object from local_time by boxing.
        object(const local_time& value);

        /// Construct object from local_date by boxing.
        object(const local_date& value);

        /// Construct object from local_date_time by boxing.
        object(const local_date_time& value);

        /// Construct object from enum by wrapping it in enum_impl(T).
        template <class T>
        object(T value, typename std::enable_if<std::is_enum<T>::value>::type* enableif = 0) : base(new enum_impl<T>(value)) {}

        /// Construct object from struct wrapper, boxing the value if necessary.
        template <typename T>
        object(struct_wrapper<T> value) : base(value) {}

        /// Construct object from tuple, boxing the value if necessary.
        template <typename ... T>
        object(const std::tuple<T...> & value) : object(new struct_wrapper_impl<std::tuple<T...>>(value)) {}

    public: // METHODS

        /// Convert object to enum. Error if object does is not a boxed T.
        ///
        /// This method does not have a counterpart in C#. It provides a more
        /// convenient alternative to unboxing than using cast to enum_impl(T).
        template <class T>
        T to_enum(typename std::enable_if<std::is_enum<T>::value>::type* enableif = 0) const { return ptr<enum_impl<T>>(*this)->value(); }

    public: // OPERATORS

        /// Forward to operator in type ptr(T).
        bool operator==(nullptr_t) const;

        /// Forward to operator in type ptr(T).
        bool operator!=(nullptr_t) const;

        /// Assign nullptr to object.
        object& operator=(nullptr_t);

        /// Assign ptr(T) to object.
        object& operator=(const ptr<object_impl>& p);

        /// Assign string to object by boxing.
        object& operator=(const string& value);

        /// Assign const string to object by boxing.
        object& operator=(const char* value);

        /// Assign bool to object by boxing.
        object& operator=(bool value);

        /// Assign double to object by boxing.
        object& operator=(double value);

        /// Assign int to object by boxing.
        object& operator=(int value);

        /// Assign long to object by boxing.
        object& operator=(int64_t value);

        /// Assign char to object by boxing.
        object& operator=(char value);

        /// Assign struct_wrapper to object by boxing.
        template <class T>
        object& operator=(const struct_wrapper<T>& value) { base::operator=(value); return *this; }

        /// Assign tuple to object by boxing.
        template <typename ... T>
        object& operator=(const std::tuple<T...> & value) { base::operator=(new struct_wrapper_impl<std::tuple<T...>>(value)); return *this; }

        /// Assign nullable to object by boxing.
        template <class T>
        object& operator=(const nullable<T>& value) { if (value.has_value()) *this = value.value(); else *this = nullptr; return *this; }

        /// Assign local_minute to object by boxing.
        object& operator=(const local_minute& value);

        /// Assign local_time to object by boxing.
        object& operator=(const local_time& value);

        /// Assign local_date to object by boxing.
        object& operator=(const local_date& value);

        /// Assign local_date_time to object by boxing.
        object& operator=(const local_date_time& value);

        /// Convert object to bool by unboxing. Error if object does is not a boxed double.
        operator bool() const;

        /// Convert object to double by unboxing. Error if object does is not a boxed double.
        operator double() const;

        /// Convert object to int by unboxing. Error if object does is not a boxed int.
        operator int() const;

        /// Convert object to long by unboxing. Error if object does is not a boxed long.
        operator int64_t() const;

        /// Convert object to char by unboxing. Error if object does is not a boxed long.
        operator char() const;

        /// Convert object to local_minute by unboxing. Error if object does is not a boxed local_minute.
        operator local_minute() const;

        /// Convert object to local_time by unboxing. Error if object does is not a boxed local_time.
        operator local_time() const;

        /// Convert object to local_date by unboxing. Error if object does is not a boxed local_date.
        operator local_date() const;

        /// Convert object to local_date_time by unboxing. Error if object does is not a boxed local_date_time.
        operator local_date_time() const;

        /// Convert object to struct_wrapper by unboxing. Error if object does is not a boxed T.
        template <class T>
        operator struct_wrapper<T>() const { return this->as<struct_wrapper<T>>(); } // TODO - replace as by cast_to?

        /// Convert object to tuple by unboxing. Error if object does is not a boxed T.
        template <class ... T>
        operator std::tuple<T...>() const { return *this->as<struct_wrapper<std::tuple<T...>>>(); } // TODO - replace as by cast_to?

        template <class T, class enabled = typename std::enable_if<std::is_enum<T>::value>::type* >
        operator T() const { return ptr<enum_impl<T>>(*this)->value(); }

        /// Convert object to string by unboxing. Error if object does is not a boxed string.
        operator string() const;

        bool operator ==(object rhs) const { throw exception("Not implemented"); return false; }

    public: // STATIC

        /// Determines whether the specified System.object instances are the same instance.
        static bool ReferenceEquals(object objA, object objB);
    };

    /// Initializes a new instance of object.
    inline object make_object() { return object(new object_impl); }

}

#include <dot/detail/struct_wrapper.hpp>

namespace dot
{
    /// Wraps struct into object.
    template <class T>
    class struct_wrapper_impl
        : public virtual object_impl
        , public T
        , public detail::inherit_to_string<struct_wrapper_impl<T>, T>
        , public detail::inherit_get_hashcode<struct_wrapper_impl<T>, T>
        , public detail::inherit_equals<struct_wrapper_impl<T>, T>
    {
    public:
        struct_wrapper_impl(const T& value) : T(value) {}

    public:
        static type typeof()
        {
            return ::dot::typeof<T>();
        }

        type get_type() override
        {
            return typeof();
        }

        virtual string to_string() override { return detail::inherit_to_string<struct_wrapper_impl<T>, T>::to_string(); }

        virtual size_t hash_code() override { return detail::inherit_get_hashcode<struct_wrapper_impl<T>, T>::hash_code(); }

        bool equals(object obj) override { return detail::inherit_equals<struct_wrapper_impl<T>, T>::equals(obj); }
    };
}

namespace std
{
    /// Implements hash struct used by STL unordered_map for object.
    template <>
    struct hash<dot::object> : public hash<dot::ptr<dot::object_impl>>
    {};

    /// Implements equal_to struct used by STL unordered_map for object.
    template <>
    struct equal_to<dot::object> : public equal_to<dot::ptr<dot::object_impl>>
    {};
}
