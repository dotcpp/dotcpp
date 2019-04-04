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

#include <cl/dotcpp/main/declare.hpp>
#include <cl/dotcpp/main/system/Ptr.hpp>
#include <cl/dotcpp/main/system/ObjectImpl.hpp>
#include <cl/dotcpp/main/system/Exception.hpp>

namespace cl
{
    class NullableBool;
    class NullableDouble;
    class NullableInt;
    class NullableLong;

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
        Object() : base() {}

        /// <summary>Construct Object from Ptr(ObjectImpl).</summary>
        Object(const Ptr<ObjectImpl>& ptr) : base(ptr) {}

        /// <summary>Construct Object from Ptr(T).</summary>
        template <class T>
        Object(const Ptr<T>& ptr) : base(ptr) {}

        /// <summary>Construct Object from String.</summary>
        Object(const String& value);

        /// <summary>Construct Object from bool by boxing.</summary>
        Object(bool value);

        /// <summary>Construct Object from NullableBool by boxing.</summary>
        Object(const NullableBool& value);

        /// <summary>Construct Object from double by boxing.</summary>
        Object(double value);

        /// <summary>Construct Object from NullableDouble by boxing.</summary>
        Object(const NullableDouble& value);

        /// <summary>Construct Object from int by boxing.</summary>
        Object(int value);

        /// <summary>Construct Object from NullableInt by boxing.</summary>
        Object(const NullableInt& value);

        /// <summary>Construct Object from int by boxing.</summary>
        Object(int64_t value);

        /// <summary>Construct Object from NullableInt by boxing.</summary>
        Object(const NullableLong& value);

        /// <summary>Construct Object from auto property, boxing the value if necessary.</summary>
        template <typename T>
        Object(detail::auto_prop<T> & value) : Object(value.operator T()) {}

    public: // OPERATORS

        /// <summary>Forward to operator in type Pt(T).</summary>
        bool operator==(nullptr_t) const { return base::operator==(nullptr); }

        /// <summary>Forward to operator in type Pt(T).</summary>
        template <class T>
        bool operator!=(nullptr_t) const { return !operator==(nullptr); }

        /// <summary>Assign Ptr(T) to Object.</summary>
        Object& operator=(const Ptr<ObjectImpl>& ptr) { base::operator=(ptr); return *this; }

        /// <summary>Assign String to Object by boxing.</summary>
        Object& operator=(const String& value);

        /// <summary>Assign bool to Object by boxing.</summary>
        Object& operator=(bool value);

        /// <summary>Assign NullableDouble to Object by boxing.</summary>
        Object& operator=(const NullableBool& value);

        /// <summary>Assign double to Object by boxing.</summary>
        Object& operator=(double value);

        /// <summary>Assign NullableDouble to Object by boxing.</summary>
        Object& operator=(const NullableDouble& value);

        /// <summary>Assign int to Object by boxing.</summary>
        Object& operator=(int value);

        /// <summary>Assign NullableInt to Object by boxing.</summary>
        Object& operator=(const NullableInt& value);

        /// <summary>Assign long to Object by boxing.</summary>
        Object& operator=(int64_t value);

        /// <summary>Assign NullableLong to Object by boxing.</summary>
        Object& operator=(const NullableLong& value);

        /// <summary>Convert Object to bool by unboxing. Error if Object does is not a boxed double.</summary>
        operator bool() const;

        /// <summary>Convert Object to double by unboxing. Error if Object does is not a boxed double.</summary>
        operator double() const;

        /// <summary>Convert Object to int by unboxing. Error if Object does is not a boxed int.</summary>
        operator int() const;

        /// <summary>Convert Object to long by unboxing. Error if Object does is not a boxed long.</summary>
        operator int64_t() const;
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

