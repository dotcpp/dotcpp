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
#include <cl/dotcpp/main/system/Bool.hpp>

namespace cl
{
    /// <summary>
    /// Wrapper for bool where default constructor creates uninitialized
    /// value. Use this class to get an error message when the variable is
    /// used before being assigned to.
    ///
    /// This class uses sentinel to represent uninitialized (empty) state,
    /// ensuring no size overhead compared to the native bool type.
    /// </summary>
    class NullableBool
    {
        int value_ = Bool::Empty;

    public: //  CONSTRUCTORS

        /// <summary>Creates in uninitialized (empty) state.</summary>
        NullableBool() : value_(Bool::Empty) {}

        /// <summary>
        /// Create from native bool.
        /// </summary>
        NullableBool(bool rhs) : value_(rhs ? 1 : 0) {}

    public: //  METHODS

        /// <summary>Returns true if the object is in uninitialized (empty) state.</summary>
        bool IsBool::Empty() const { return value_ == Bool::Empty; }

        /// <summary>Returns string representation of the object.</summary>
        std::string AsString() const
        {
            switch(value_)
            {
                case 1: return "Y";
                case 0: return "N";
                case Bool::Empty: return "";
                default: throw std::exception("Unknown internal value in NullableBool.");
            }
        }

        /// <summary>Convert to native bool, error if the object is in uninitialized (empty) state.</summary>
        bool Value() const
        {
            switch(value_)
            {
                case 1: return true;
                case 0: return false;
                case Bool::Empty: throw std::exception("Bool value is empty");
                default: throw std::exception("Unknown internal value in NullableBool.");
            }
        }

        /// <summary>Clear the value and revert to uninitialized (empty) state.</summary>
        void Clear() { value_ = Bool::Empty; }

    public: //  OPERATORS

        /// <summary>Convert to native bool, error if the object is in uninitialized (empty) state.</summary>
        operator bool() const { return Value(); }

        /// <summary>
        /// Assign native bool.
        /// </summary>
        NullableBool& operator=(bool rhs) { value_ = rhs ? 1 : 0; return *this; }
    };
}
