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
#include <dot/system/Long.hpp>
#include <dot/system/ObjectImpl.hpp>

namespace dot
{
    /// <summary>
    /// Wrapper for int64_t where default constructor creates uninitialized
    /// value. Use this class to get an error message when the variable is
    /// used before being assigned to.
    ///
    /// This class uses sentinel to represent uninitialized (empty) state,
    /// ensuring no size overhead compared to the native long type.
    /// </summary>
    class NullableLong
    {
        int64_t value_ = Long::Empty;

    public: //  CONSTRUCTORS

        /// <summary>Creates in uninitialized (empty) state.</summary>
        NullableLong() : value_(Long::Empty) {}

        /// <summary>
        /// Create from native long.
        ///
        /// If sentinel value for uninitialized state is passed to this constructor,
        /// no error occurs and the object is constructed in uninitialized state.
        /// </summary>
        NullableLong(int64_t rhs) : value_(rhs) {}

        /// <summary>
        /// Supports cast (explicit constructor) from Object.
        ///
        /// Error if Object does is not a boxed long.
        /// Null Object becomes empty NullableLong.
        /// </summary>
        explicit NullableLong(const Ptr<ObjectImpl>& rhs) : value_(rhs == nullptr ? Long::Empty : Ptr<LongImpl>(rhs)->value_) {}

    public: //  METHODS

        /// <summary>Returns true if the object is in uninitialized (empty) state.</summary>
        bool IsEmpty() const { return value_ == Long::Empty; }

        /// <summary>Returns string representation of the object.</summary>
        std::string AsString() const;

        /// <summary>Convert to native long, error if the object is in uninitialized (empty) state.</summary>
        int64_t Value() const { if (value_ == Long::Empty) throw std::runtime_error("Long value is empty"); return value_; }

        /// <summary>Clear the value and revert to uninitialized (empty) state.</summary>
        void Clear() { value_ = Long::Empty; }

    public: //  OPERATORS

        /// <summary>Convert to native long, error if the object is in uninitialized (empty) state.</summary>
        operator int64_t() const { return Value(); }

        /// <summary>
        /// Assign native long.
        ///
        /// If sentinel value for uninitialized state is passed to this operator,
        /// no error occurs and the object reverts to uninitialized (empty) state.
        /// </summary>
        NullableLong& operator=(int64_t rhs) { value_ = rhs; return *this; }
    };
}
