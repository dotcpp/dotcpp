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

#pragma once

#include <dot/declare.hpp>
#include <dot/system/Ptr.hpp>
#include <dot/system/ObjectImpl.hpp>
#include <dot/system/Exception.hpp>

namespace dot
{
    template <class T> class Nullable;
    class LocalTime;
    class LocalDate;
    class LocalDateTime;

    template <class T>
    class StructWrapperImpl;
    template <class T>
    using StructWrapper = Ptr<StructWrapperImpl<T>>;

    /// <summary>Adds support for boxing value types to Ptr(ObjectImpl).</summary>
    class CL_DOTCPP_MAIN Object : public Ptr<ObjectImpl>
    {
        typedef Ptr<ObjectImpl> base;

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

        /// <summary>Construct Object from Ptr(ObjectImpl).</summary>
        Object(const Ptr<ObjectImpl>& ptr);

        /// <summary>Construct Object from Ptr(T).</summary>
        template <class T>
        Object(const Ptr<T>& ptr) : base(ptr) {}

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

    public: // OPERATORS

        /// <summary>Forward to operator in type Ptr(T).</summary>
        bool operator==(nullptr_t) const;

        /// <summary>Forward to operator in type Ptr(T).</summary>
        bool operator!=(nullptr_t) const;

        /// <summary>Assign nullptr to Object.</summary>
        Object& operator=(nullptr_t);

        /// <summary>Assign Ptr(T) to Object.</summary>
        Object& operator=(const Ptr<ObjectImpl>& ptr);

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

        /// <summary>Assign Nullable to Object by boxing.</summary>
        template <class T>
        Object& operator=(const Nullable<T>& value) { if (value.HasValue) *this = value.Value; else *this = nullptr; return *this; }

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

        /// <summary>Convert Object to LocalTime by unboxing. Error if Object does is not a boxed LocalTime.</summary>
        operator LocalTime() const;

        /// <summary>Convert Object to LocalDate by unboxing. Error if Object does is not a boxed LocalDate.</summary>
        operator LocalDate() const;

        /// <summary>Convert Object to LocalDateTime by unboxing. Error if Object does is not a boxed LocalDateTime.</summary>
        operator LocalDateTime() const;

        /// <summary>Convert Object to StructWrapper by unboxing. Error if Object does is not a boxed T.</summary>
        template <class T>
        operator StructWrapper<T>() const { return this->as<StructWrapper<T>>(); }

        bool operator ==(Object rhs) const { throw new_Exception("Not implemented"); return false; }

    };

    /// <summary>Initializes a new instance of Object.</summary>
    inline Object new_Object() { return Object(new ObjectImpl); }

    /// <summary>Wraps struct into object.</summary>
    template <class T>
    class StructWrapperImpl : public virtual ObjectImpl, public T
    {
    public:
        StructWrapperImpl(const T& value) : T(value) {}

    public:
        static Type typeof()
        {
            return ::cl::typeof<T>();
        }

        virtual Type GetType() override
        {
            return typeof();
        }
    };
}

namespace std
{
    /// <summary>Implements hash struct used by STL unordered_map for Object.</summary>
    template <>
    struct hash<cl::Object> : public hash<cl::Ptr<cl::ObjectImpl>>
    {};

    /// <summary>Implements equal_to struct used by STL unordered_map for Object.</summary>
    template <>
    struct equal_to<cl::Object> : public equal_to<cl::Ptr<cl::ObjectImpl>>
    {};
}
