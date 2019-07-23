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

namespace dot
{
    namespace detail
    {
        /// <summary>
        /// This class is used as base class of Array.
        ///
        /// The objective is to make it possible to pass this class to functions
        /// accepting  std::vector. Because C# Array is non-resizable, array_base
        /// derives from std::vector and then hides all methods that resize the array.
        /// </summary>
        template <class T>
        class array_base : public std::vector<T>
        {
            typedef std::vector<T> base;

        protected: // CONSTRUCTORS

            /// <summary>
            /// Create with the specified size and default value of T.
            ///
            /// This constructor creates std::vector with capacity=size
            /// avoiding excess memory allocation.
            /// </summary>
            array_base(int size) : base(size, T()) {}

            /// <summary>Create from std::vector using copy ctor.</summary>
            explicit array_base(const std::vector<T>& obj) : base(obj) {}

            /// <summary>Create from std::vector using move ctor.</summary>
            explicit array_base(std::vector<T>&& obj) : base(obj) {}

            // TODO - delete or mark private the methods of array_base that change its size

    	protected: // METHODS

            /// <summary>Made protected to hide from derived types unless expressly enabled.</summary>
            auto begin() { return base::begin(); }

            /// <summary>Made protected to hide from derived types unless expressly enabled.</summary>
            auto end() { return base::end(); }

        protected: // OPERATORS

            /// <summary>Made protected to hide from derived types unless expressly enabled.</summary>
            const T& operator[](size_t i) const { return base::operator[](i); }

            /// <summary>Made protected to hide from derived types unless expressly enabled.</summary>
            T& operator[](size_t i) { return base::operator[](i); }
        };
    }
}
