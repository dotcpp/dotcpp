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
#include <cl/dotcpp/main/system/Double.hpp>
#include <cl/dotcpp/main/system/ObjectImpl.hpp>

namespace cl
{
    class NullableDouble;

    /// <summary>Wrapper around double to make it convertible to Object (boxing).</summary>
    class DoubleImpl : public virtual ObjectImpl
    {
        friend Object;
        friend NullableDouble;
        double value_;

    public: // CONSTRUCTORS

        /// <summary>Create from value (box).</summary>
        DoubleImpl(double value) : value_(value) {}

    public: // METHODS

        /// <summary>A string representing the name of the current type.</summary>
        virtual String ToString() const;
    };

    /// <summary>
    /// Nullable double is initialized to null (empty) by default ctor.
    /// Conversion to double when in null state results in an error.
    ///
    /// This class uses a sentinel to represent null (empty) state,
    /// ensuring no size overhead compared to the native double type.
    /// </summary>
    class NullableDouble
    {
        double value_ = Double::Empty;

    public: //  CONSTRUCTORS

        /// <summary>Creates in null (empty) state.</summary>
        NullableDouble() : value_(Double::Empty) {}

        /// <summary>
        /// Create from native double.
        ///
        /// If sentinel value for null state is passed to this constructor,
        /// no error occurs and the object is constructed in null state.
        /// </summary>
        NullableDouble(double rhs) : value_(rhs) {}

        /// <summary>
        /// Supports cast (explicit constructor) from Object.
        ///
        /// Error if Object does is not a boxed double.
        /// Null Object becomes empty NullableDouble.
        /// </summary>
        explicit NullableDouble(const Ptr<ObjectImpl>& rhs) : value_(rhs == nullptr ? Double::Empty : Ptr<DoubleImpl>(rhs)->value_) {}

    public: //  METHODS

        /// <summary>Returns true if the object is in null (empty) state.</summary>
        bool IsEmpty() const { return value_ == Double::Empty; }

        /// <summary>Returns string representation of the object.</summary>
        std::string AsString() const;

        /// <summary>Convert to native double, error if the object is in null (empty) state.</summary>
        double Value() const { if (value_ == Double::Empty) throw std::runtime_error("Double value is empty"); return value_; }

        /// <summary>Clear the value and revert to null (empty) state.</summary>
        void Clear() { value_ = Double::Empty; }

    public: //  OPERATORS

        /// <summary>Convert to native double, error if the object is in null (empty) state.</summary>
        operator double() const { return Value(); }

        /// <summary>
        /// Assign native double.
        ///
        /// If sentinel value for null state is passed to this operator,
        /// no error occurs and the object reverts to null (empty) state.
        /// </summary>
        NullableDouble& operator=(double rhs) { value_ = rhs; return *this; }
    };
}
