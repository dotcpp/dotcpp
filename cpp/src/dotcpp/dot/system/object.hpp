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

namespace dot
{
    template <class T> class nullable;
    class local_minute;
    class local_time;
    class local_date;
    class local_date_time;

    template <class T>
    class struct_wrapper_impl;
    template <class T>
    using struct_wrapper = ptr<struct_wrapper_impl<T>>;

    template <class T>
    type_t typeof();


    namespace detail
    {
        template<class W, class T>
        class inherit_to_string;
        template<class W, class T>
        class inherit_get_hashcode;
        template<class W, class T>
        class inherit_equals;
    }

    /// <summary>Adds support for boxing value types to ptr(object_impl).</summary>
    class DOT_CLASS object : public ptr<object_impl>
    {
        typedef ptr<object_impl> base;

    public: // CONSTRUCTORS

        /// <summary>
        /// Default constructor to create untyped object.
        ///
        /// This constructor is used, among other things,
        /// as argument to lock(...) to provide thread safety.
        /// </summary>
        object() = default;

        /// <summary>Construct object from nullptr.</summary>
        object(nullptr_t);

        /// <summary>Construct object from ptr(object_impl).</summary>
        object(const ptr<object_impl>& p);

        /// <summary>Construct object from ptr(T).</summary>
        template <class T>
        object(const ptr<T>& p) : base(p) {}

        /// <summary>Construct object from object_impl pointer.</summary>
        object(object_impl* value);

        /// <summary>Construct object from string.</summary>
        object(const string& value);

        /// <summary>Construct object from const string.</summary>
        object(const char* value);

        /// <summary>Construct object from bool by boxing.</summary>
        object(bool value);

        /// <summary>Construct object from double by boxing.</summary>
        object(double value);

        /// <summary>Construct object from int by boxing.</summary>
        object(int value);

        /// <summary>Construct object from int by boxing.</summary>
        object(int64_t value);

        /// <summary>Construct object from char by boxing.</summary>
        object(char value);

        /// <summary>Construct object from nullable by boxing.</summary>
        template <class T>
        object(const nullable<T>& value) { if (value.has_value()) *this = value.value(); }

        /// <summary>Construct object from local_minute by boxing.</summary>
        object(const local_minute & value);

        /// <summary>Construct object from local_time by boxing.</summary>
        object(const local_time& value);

        /// <summary>Construct object from local_date by boxing.</summary>
        object(const local_date& value);

        /// <summary>Construct object from local_date_time by boxing.</summary>
        object(const local_date_time& value);

        /// <summary>Construct object from struct wrapper, boxing the value if necessary.</summary>
        template <typename T>
        object(struct_wrapper<T> value) : base(value) {}

        /// <summary>Construct object from tuple, boxing the value if necessary.</summary>
        template <typename ... T>
        object(const std::tuple<T...> & value) : object(new struct_wrapper_impl<std::tuple<T...>>(value)) {}

    public: // OPERATORS

        /// <summary>Forward to operator in type ptr(T).</summary>
        bool operator==(nullptr_t) const;

        /// <summary>Forward to operator in type ptr(T).</summary>
        bool operator!=(nullptr_t) const;

        /// <summary>Assign nullptr to object.</summary>
        object& operator=(nullptr_t);

        /// <summary>Assign ptr(T) to object.</summary>
        object& operator=(const ptr<object_impl>& p);

        /// <summary>Assign string to object by boxing.</summary>
        object& operator=(const string& value);

        /// <summary>Assign const string to object by boxing.</summary>
        object& operator=(const char* value);

        /// <summary>Assign bool to object by boxing.</summary>
        object& operator=(bool value);

        /// <summary>Assign double to object by boxing.</summary>
        object& operator=(double value);

        /// <summary>Assign int to object by boxing.</summary>
        object& operator=(int value);

        /// <summary>Assign long to object by boxing.</summary>
        object& operator=(int64_t value);

        /// <summary>Assign char to object by boxing.</summary>
        object& operator=(char value);

        /// <summary>Assign struct_wrapper to object by boxing.</summary>
        template <class T>
        object& operator=(const struct_wrapper<T>& value) { base::operator=(value); return *this; }

        /// <summary>Assign tuple to object by boxing.</summary>
        template <typename ... T>
        object& operator=(const std::tuple<T...> & value) { base::operator=(new struct_wrapper_impl<std::tuple<T...>>(value)); return *this; }

        /// <summary>Assign nullable to object by boxing.</summary>
        template <class T>
        object& operator=(const nullable<T>& value) { if (value.has_value()) *this = value.value(); else *this = nullptr; return *this; }

        /// <summary>Assign local_minute to object by boxing.</summary>
        object& operator=(const local_minute& value);

        /// <summary>Assign local_time to object by boxing.</summary>
        object& operator=(const local_time& value);

        /// <summary>Assign local_date to object by boxing.</summary>
        object& operator=(const local_date& value);

        /// <summary>Assign local_date_time to object by boxing.</summary>
        object& operator=(const local_date_time& value);

        /// <summary>Convert object to bool by unboxing. Error if object does is not a boxed double.</summary>
        operator bool() const;

        /// <summary>Convert object to double by unboxing. Error if object does is not a boxed double.</summary>
        operator double() const;

        /// <summary>Convert object to int by unboxing. Error if object does is not a boxed int.</summary>
        operator int() const;

        /// <summary>Convert object to long by unboxing. Error if object does is not a boxed long.</summary>
        operator int64_t() const;

        /// <summary>Convert object to char by unboxing. Error if object does is not a boxed long.</summary>
        operator char() const;

        /// <summary>Convert object to local_minute by unboxing. Error if object does is not a boxed local_minute.</summary>
        operator local_minute() const;

        /// <summary>Convert object to local_time by unboxing. Error if object does is not a boxed local_time.</summary>
        operator local_time() const;

        /// <summary>Convert object to local_date by unboxing. Error if object does is not a boxed local_date.</summary>
        operator local_date() const;

        /// <summary>Convert object to local_date_time by unboxing. Error if object does is not a boxed local_date_time.</summary>
        operator local_date_time() const;

        /// <summary>Convert object to struct_wrapper by unboxing. Error if object does is not a boxed T.</summary>
        template <class T>
        operator struct_wrapper<T>() const { return this->as<struct_wrapper<T>>(); }

        /// <summary>Convert object to tuple by unboxing. Error if object does is not a boxed T.</summary>
        template <class ... T>
        operator std::tuple<T...>() const { return *this->as<struct_wrapper<std::tuple<T...>>>(); }

        bool operator ==(object rhs) const { throw exception("Not implemented"); return false; }

    public: // STATIC

        /// <summary>Determines whether the specified System.object instances are the same instance.</summary>
        static bool ReferenceEquals(object objA, object objB);
    };

    /// <summary>Initializes a new instance of object.</summary>
    inline object new_object() { return object(new object_impl); }

}

#include <dot/detail/struct_wrapper.hpp>

namespace dot
{
    /// <summary>Wraps struct into object.</summary>
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
        static type_t typeof()
        {
            return ::dot::typeof<T>();
        }

        virtual type_t type() override
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
    /// <summary>Implements hash struct used by STL unordered_map for object.</summary>
    template <>
    struct hash<dot::object> : public hash<dot::ptr<dot::object_impl>>
    {};

    /// <summary>Implements equal_to struct used by STL unordered_map for object.</summary>
    template <>
    struct equal_to<dot::object> : public equal_to<dot::ptr<dot::object_impl>>
    {};
}
