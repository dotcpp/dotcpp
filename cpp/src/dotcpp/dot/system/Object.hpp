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
#include <dot/system/ObjectImpl.hpp>
#include <dot/system/Exception.hpp>
#include <dot/system/String.hpp>

namespace dot
{
    template <class T> class Nullable;
    class LocalMinute;
    class LocalTime;
    class LocalDate;
    class LocalDateTime;

    template <class T>
    class StructWrapperImpl;
    template <class T>
    using StructWrapper = ptr<StructWrapperImpl<T>>;

    template <class T>
    Type typeof();


    namespace detail
    {
        template<class W, class T>
        class inherit_to_string;
        template<class W, class T>
        class inherit_get_hashcode;
        template<class W, class T>
        class inherit_equals;
    }

    /// <summary>Adds support for boxing value types to ptr(ObjectImpl).</summary>
    class DOT_CLASS Object : public ptr<ObjectImpl>
    {
        typedef ptr<ObjectImpl> base;

    public: // CONSTRUCTORS

        /// <summary>
        /// Default constructor to create untyped Object.
        ///
        /// This constructor is used, among other things,
        /// as argument to lock(...) to provide thread safety.
        /// </summary>
        Object() = default;

        /// <summary>Construct Object from nullptr.</summary>
        Object(nullptr_t);

        /// <summary>Construct Object from ptr(ObjectImpl).</summary>
        Object(const ptr<ObjectImpl>& p);

        /// <summary>Construct Object from ptr(T).</summary>
        template <class T>
        Object(const ptr<T>& p) : base(p) {}

        /// <summary>Construct Object from ObjectImpl pointer.</summary>
        Object(ObjectImpl* value);

        /// <summary>Construct Object from String.</summary>
        Object(const String& value);

        /// <summary>Construct Object from const string.</summary>
        Object(const char* value);

        /// <summary>Construct Object from bool by boxing.</summary>
        Object(bool value);

        /// <summary>Construct Object from double by boxing.</summary>
        Object(double value);

        /// <summary>Construct Object from int by boxing.</summary>
        Object(int value);

        /// <summary>Construct Object from int by boxing.</summary>
        Object(int64_t value);

        /// <summary>Construct Object from char by boxing.</summary>
        Object(char value);

        /// <summary>Construct Object from Nullable by boxing.</summary>
        template <class T>
        Object(const Nullable<T>& value) { if (value.HasValue) *this = value.Value; }

        /// <summary>Construct Object from LocalMinute by boxing.</summary>
        Object(const LocalMinute & value);

        /// <summary>Construct Object from LocalTime by boxing.</summary>
        Object(const LocalTime& value);

        /// <summary>Construct Object from LocalDate by boxing.</summary>
        Object(const LocalDate& value);

        /// <summary>Construct Object from LocalDateTime by boxing.</summary>
        Object(const LocalDateTime& value);

        /// <summary>Construct Object from auto property, boxing the value if necessary.</summary>
        template <typename T>
        Object(detail::auto_prop<T> & value) : Object(value.operator T()) {}

        /// <summary>Construct Object from struct wrapper, boxing the value if necessary.</summary>
        template <typename T>
        Object(StructWrapper<T> value) : base(value) {}

        /// <summary>Construct Object from tuple, boxing the value if necessary.</summary>
        template <typename ... T>
        Object(const std::tuple<T...> & value) : Object(new StructWrapperImpl<std::tuple<T...>>(value)) {}

    public: // OPERATORS

        /// <summary>Forward to operator in type ptr(T).</summary>
        bool operator==(nullptr_t) const;

        /// <summary>Forward to operator in type ptr(T).</summary>
        bool operator!=(nullptr_t) const;

        /// <summary>Assign nullptr to Object.</summary>
        Object& operator=(nullptr_t);

        /// <summary>Assign ptr(T) to Object.</summary>
        Object& operator=(const ptr<ObjectImpl>& p);

        /// <summary>Assign String to Object by boxing.</summary>
        Object& operator=(const String& value);

        /// <summary>Assign const string to Object by boxing.</summary>
        Object& operator=(const char* value);

        /// <summary>Assign bool to Object by boxing.</summary>
        Object& operator=(bool value);

        /// <summary>Assign double to Object by boxing.</summary>
        Object& operator=(double value);

        /// <summary>Assign int to Object by boxing.</summary>
        Object& operator=(int value);

        /// <summary>Assign long to Object by boxing.</summary>
        Object& operator=(int64_t value);

        /// <summary>Assign char to Object by boxing.</summary>
        Object& operator=(char value);

        /// <summary>Assign StructWrapper to Object by boxing.</summary>
        template <class T>
        Object& operator=(const StructWrapper<T>& value) { base::operator=(value); return *this; }

        /// <summary>Assign tuple to Object by boxing.</summary>
        template <typename ... T>
        Object& operator=(const std::tuple<T...> & value) { base::operator=(new StructWrapperImpl<std::tuple<T...>>(value)); return *this; }

        /// <summary>Assign Nullable to Object by boxing.</summary>
        template <class T>
        Object& operator=(const Nullable<T>& value) { if (value.HasValue) *this = value.Value; else *this = nullptr; return *this; }

        /// <summary>Assign LocalMinute to Object by boxing.</summary>
        Object& operator=(const LocalMinute& value);

        /// <summary>Assign LocalTime to Object by boxing.</summary>
        Object& operator=(const LocalTime& value);

        /// <summary>Assign LocalDate to Object by boxing.</summary>
        Object& operator=(const LocalDate& value);

        /// <summary>Assign LocalDateTime to Object by boxing.</summary>
        Object& operator=(const LocalDateTime& value);

        /// <summary>Convert Object to bool by unboxing. Error if Object does is not a boxed double.</summary>
        operator bool() const;

        /// <summary>Convert Object to double by unboxing. Error if Object does is not a boxed double.</summary>
        operator double() const;

        /// <summary>Convert Object to int by unboxing. Error if Object does is not a boxed int.</summary>
        operator int() const;

        /// <summary>Convert Object to long by unboxing. Error if Object does is not a boxed long.</summary>
        operator int64_t() const;

        /// <summary>Convert Object to char by unboxing. Error if Object does is not a boxed long.</summary>
        operator char() const;

        /// <summary>Convert Object to LocalMinute by unboxing. Error if Object does is not a boxed LocalMinute.</summary>
        operator LocalMinute() const;

        /// <summary>Convert Object to LocalTime by unboxing. Error if Object does is not a boxed LocalTime.</summary>
        operator LocalTime() const;

        /// <summary>Convert Object to LocalDate by unboxing. Error if Object does is not a boxed LocalDate.</summary>
        operator LocalDate() const;

        /// <summary>Convert Object to LocalDateTime by unboxing. Error if Object does is not a boxed LocalDateTime.</summary>
        operator LocalDateTime() const;

        /// <summary>Convert Object to StructWrapper by unboxing. Error if Object does is not a boxed T.</summary>
        template <class T>
        operator StructWrapper<T>() const { return this->as<StructWrapper<T>>(); }

        /// <summary>Convert Object to tuple by unboxing. Error if Object does is not a boxed T.</summary>
        template <class ... T>
        operator std::tuple<T...>() const { return *this->as<StructWrapper<std::tuple<T...>>>(); }

        bool operator ==(Object rhs) const { throw new_Exception("Not implemented"); return false; }

    public: // STATIC

        /// <summary>Determines whether the specified System.Object instances are the same instance.</summary>
        static bool ReferenceEquals(Object objA, Object objB);
    };

    /// <summary>Initializes a new instance of Object.</summary>
    inline Object new_Object() { return Object(new ObjectImpl); }

}

#include <dot/detail/struct_wrapper.hpp>

namespace dot
{
    /// <summary>Wraps struct into object.</summary>
    template <class T>
    class StructWrapperImpl
        : public virtual ObjectImpl
        , public T
        , public detail::inherit_to_string<StructWrapperImpl<T>, T>
        , public detail::inherit_get_hashcode<StructWrapperImpl<T>, T>
        , public detail::inherit_equals<StructWrapperImpl<T>, T>
    {
    public:
        StructWrapperImpl(const T& value) : T(value) {}

    public:
        static Type typeof()
        {
            return ::dot::typeof<T>();
        }

        virtual Type GetType() override
        {
            return typeof();
        }

        virtual String ToString() override { return detail::inherit_to_string<StructWrapperImpl<T>, T>::ToString(); }

        virtual size_t GetHashCode() override { return detail::inherit_get_hashcode<StructWrapperImpl<T>, T>::GetHashCode(); }

        virtual bool Equals(Object obj) override { return detail::inherit_equals<StructWrapperImpl<T>, T>::Equals(obj); }
    };
}

namespace std
{
    /// <summary>Implements hash struct used by STL unordered_map for Object.</summary>
    template <>
    struct hash<dot::Object> : public hash<dot::ptr<dot::ObjectImpl>>
    {};

    /// <summary>Implements equal_to struct used by STL unordered_map for Object.</summary>
    template <>
    struct equal_to<dot::Object> : public equal_to<dot::ptr<dot::ObjectImpl>>
    {};
}
