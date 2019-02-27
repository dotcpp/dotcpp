/*
Copyright (C) 2003-2015 CompatibL

This file is part of .C++, a native C++ implementation of
selected .NET class library APIs with built-in support for
algorithmic differentiation (AD), available from

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

namespace cl
{
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

    public: //  METHODS

        /// <summary>Returns true if the object is in null (empty) state.</summary>
        bool IsEmpty() const { return value_ == Double::Empty; }

        /// <summary>Returns string representation of the object.</summary>
        std::string AsString() const { return value_ != Double::Empty ? std::to_string(value_) : ""; }

        /// <summary>Convert to native double, error if the object is in null (empty) state.</summary>
        double Value() const { if (value_ == Double::Empty) throw std::exception("Double value is empty"); return value_; }

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
