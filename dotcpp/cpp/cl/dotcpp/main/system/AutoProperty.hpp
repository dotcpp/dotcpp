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

namespace cl
{
    /// <summary>Helper class to implement read/write auto property.</summary>
    template <class T>
    class AutoProperty
    {
    public: // CONSTRUCTORS

        /// <summary>Create by passing arguments to the constructor of T.</summary>
        template <typename... Args>
        explicit AutoProperty(Args... args) : value_(args...) {}

    public: // OPERATORS

        /// <summary>Provides property set behavior.</summary>
        void operator=(const T& value) { value_ = value; }

        /// <summary>Provides property get behavior.</summary>
        operator T() const { return value_; }

        /// <summary>Forwards operator* to the underlying type.</summary>
        auto& operator*() const { return *value_; }

        /// <summary>Forwards operator-> to the underlying type.</summary>
        auto operator->() const { return value_.operator->(); }

        /// <summary>Comparison operator.</summary>
        template <typename U>
        bool operator==(const U& u) const
        {
            return value_ == u;
        }

    private:
        T value_;
    };
}
