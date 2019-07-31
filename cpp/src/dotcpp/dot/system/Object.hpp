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
#include <dot/system/objectimpl.hpp>
#include <dot/system/Exception.hpp>
#include <dot/system/string.hpp>

namespace dot
{
    template <class T> class nullable;
    class LocalMinute;
    class LocalTime;
    class LocalDate;
    class LocalDateTime;

    template <class T>
    class StructWrapperImpl;
    template <class T>
    using StructWrapper = ptr<StructWrapperImpl<T>>;

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

        /// <summary>Construct object from LocalMinute by boxing.</summary>
        object(const LocalMinute & value);

        /// <summary>Construct object from LocalTime by boxing.</summary>
        object(const LocalTime& value);

        /// <summary>Construct object from LocalDate by boxing.</summary>
        object(const LocalDate& value);

        /// <summary>Construct object from LocalDateTime by boxing.</summary>
        object(const LocalDateTime& value);

        /// <summary>Construct object from struct wrapper, boxing the value if necessary.</summary>
        template <typename T>
        object(StructWrapper<T> value) : base(value) {}

        /// <summary>Construct object from tuple, boxing the value if necessary.</summary>
        template <typename ... T>
        object(const std::tuple<T...> & value) : object(new StructWrapperImpl<std::tuple<T...>>(value)) {}

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

        /// <summary>Assign StructWrapper to object by boxing.</summary>
        template <class T>
        object& operator=(const StructWrapper<T>& value) { base::operator=(value); return *this; }

        /// <summary>Assign tuple to object by boxing.</summary>
        template <typename ... T>
        object& operator=(const std::tuple<T...> & value) { base::operator=(new StructWrapperImpl<std::tuple<T...>>(value)); return *this; }

        /// <summary>Assign nullable to object by boxing.</summary>
        template <class T>
        object& operator=(const nullable<T>& value) { if (value.has_value()) *this = value.value(); else *this = nullptr; return *this; }

        /// <summary>Assign LocalMinute to object by boxing.</summary>
        object& operator=(const LocalMinute& value);

        /// <summary>Assign LocalTime to object by boxing.</summary>
        object& operator=(const LocalTime& value);

        /// <summary>Assign LocalDate to object by boxing.</summary>
        object& operator=(const LocalDate& value);

        /// <summary>Assign LocalDateTime to object by boxing.</summary>
        object& operator=(const LocalDateTime& value);

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

        /// <summary>Convert object to LocalMinute by unboxing. Error if object does is not a boxed LocalMinute.</summary>
        operator LocalMinute() const;

        /// <summary>Convert object to LocalTime by unboxing. Error if object does is not a boxed LocalTime.</summary>
        operator LocalTime() const;

        /// <summary>Convert object to LocalDate by unboxing. Error if object does is not a boxed LocalDate.</summary>
        operator LocalDate() const;

        /// <summary>Convert object to LocalDateTime by unboxing. Error if object does is not a boxed LocalDateTime.</summary>
        operator LocalDateTime() const;

        /// <summary>Convert object to StructWrapper by unboxing. Error if object does is not a boxed T.</summary>
        template <class T>
        operator StructWrapper<T>() const { return this->as<StructWrapper<T>>(); }

        /// <summary>Convert object to tuple by unboxing. Error if object does is not a boxed T.</summary>
        template <class ... T>
        operator std::tuple<T...>() const { return *this->as<StructWrapper<std::tuple<T...>>>(); }

        bool operator ==(object rhs) const { throw new_Exception("Not implemented"); return false; }

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
    class StructWrapperImpl
        : public virtual object_impl
        , public T
        , public detail::inherit_to_string<StructWrapperImpl<T>, T>
        , public detail::inherit_get_hashcode<StructWrapperImpl<T>, T>
        , public detail::inherit_equals<StructWrapperImpl<T>, T>
    {
    public:
        StructWrapperImpl(const T& value) : T(value) {}

    public:
        static type_t typeof()
        {
            return ::dot::typeof<T>();
        }

        virtual type_t type() override
        {
            return typeof();
        }

        virtual string to_string() override { return detail::inherit_to_string<StructWrapperImpl<T>, T>::to_string(); }

        virtual size_t hash_code() override { return detail::inherit_get_hashcode<StructWrapperImpl<T>, T>::hash_code(); }

        bool equals(object obj) override { return detail::inherit_equals<StructWrapperImpl<T>, T>::equals(obj); }
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
