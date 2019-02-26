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

#ifndef cl_dotcpp_main_Double_hpp
#define cl_dotcpp_main_Double_hpp

#include <cl/system/declare.hpp>

namespace cl
{
    /// <summary>Nullable double type with arithmetics support.
    /// In AD mode, this class contains a tape pointer.</summary>
    class tdouble
    {
        double value_ = Empty;

    public: //  CONSTANTS

        /// <summary>Empty value.</summary>
        static constexpr double Empty = -1e100;

        /// <summary>Tolerance used in comparison of doubles.</summary>
        static constexpr double Tolerance = 1e-10;

    public: //  CONSTRUCTORS

        /// <summary>Create with empty value.</summary>
        tdouble() : value_(Empty) {}

        /// <summary>Explicit constructor from double.</summary>
        tdouble(double rhs) : value_(rhs) {}

    public: //  METHODS

        /// <summary>Returns true if the field is empty.</summary>
        bool isEmpty() const { return value_ == Empty; }

        /// <summary>Convert to string.</summary>
        std::string toString() const
        {
            return value_ != Empty ? std::to_string(value_) : "";
        }

        /// <summary>Returns true if not empty.</summary>
        bool IsSet() const { return value_ != Empty; }

    public: //  OPERATORS

        /// <summary>Conversion operator.</summary>
        operator double() const { return value_; }

        /// <summary>Assignment of native double.</summary>
        tdouble& operator=(double rhs) { value_ = rhs; return *this; }
    };

}

#endif // cl_dotcpp_main_Double_hpp
