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
#include <cl/dotcpp/main/system/Int.hpp>
#include <cl/dotcpp/main/system/ObjectImpl.hpp>

namespace cl
{
    class NullableInt;

    /// <summary>Wrapper around int to make it convertible to Object (boxing).</summary>
    class IntImpl : public virtual ObjectImpl
    {
        friend Object;
        friend NullableInt;
        int value_;

    public: // CONSTRUCTORS

        /// <summary>Create from value (box).</summary>
        IntImpl(int value) : value_(value) {}

    public: // METHODS

        /// <summary>A string representing the name of the current type.</summary>
        virtual String ToString() const;
    };

    /// <summary>
    /// Wrapper for int where default constructor creates uninitialized
    /// value. Use this class to get an error message when the variable is
    /// used before being assigned to.
    ///
    /// This class uses sentinel to represent uninitialized (empty) state,
    /// ensuring no size overhead compared to the native int type.
    /// </summary>
    class NullableInt
    {
        int value_ = Int::Empty;

    public: //  CONSTRUCTORS

        /// <summary>Creates in uninitialized (empty) state.</summary>
        NullableInt() : value_(Int::Empty) {}

        /// <summary>
        /// Create from native int.
        ///
        /// If sentinel value for uninitialized state is passed to this constructor,
        /// no error occurs and the object is constructed in uninitialized state.
        /// </summary>
        NullableInt(int rhs) : value_(rhs) {}

        /// <summary>
        /// Create from Object.
        ///
        /// Error if Object does is not a boxed double.
        /// Null Object becomes empty NullableDouble.
        /// </summary>
        // NullableInt(const Ptr<ObjectImpl>& rhs);

    public: //  METHODS

        /// <summary>Returns true if the object is in uninitialized (empty) state.</summary>
        bool IsEmpty() const { return value_ == Int::Empty; }

        /// <summary>Returns string representation of the object.</summary>
        std::string AsString() const;

        /// <summary>Convert to native double, error if the object is in uninitialized (empty) state.</summary>
        int Value() const { if (value_ == Int::Empty) throw std::runtime_error("Int value is empty"); return value_; }

        /// <summary>Clear the value and revert to uninitialized (empty) state.</summary>
        void Clear() { value_ = Int::Empty; }

    public: //  OPERATORS

        /// <summary>Convert to native int, error if the object is in uninitialized (empty) state.</summary>
        operator int() const { return Value(); }

        /// <summary>
        /// Assign native int.
        ///
        /// If sentinel value for uninitialized state is passed to this operator,
        /// no error occurs and the object reverts to uninitialized (empty) state.
        /// </summary>
        NullableInt& operator=(int rhs) { value_ = rhs; return *this; }
    };
}
