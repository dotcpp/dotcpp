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

#include <cl/dotcpp/main/system/collections/generic/ListBase.hpp>
#include <cl/dotcpp/main/system/Exception.hpp>

namespace cl
{
    template <class T> class Array1DImpl; template <class T> using Array1D = Ptr<Array1DImpl<T>>;

    /// <summary>
    /// Represents a strongly typed list of objects that can be accessed by index.
    /// Provides methods to search, sort, and manipulate lists.
    /// </summary>
    template <typename T>
    class Array1DImpl : public ListBaseImpl<T>
    {
        typedef std::vector<T> base;

        template <typename T>
        friend Array1D<T> new_Array1D(int size);

    private: // CONSTRUCTORS

        /// <summary>
        /// Initializes a new instance of the array with the specified size.
        ///
        /// This constructor is private. Use new_Array1D(size) function instead.
        /// </summary>
        Array1DImpl(int size) { base::resize(size); }

    public: // METHODS

        /// <summary>Adds an object to the end of the list.</summary>
        virtual void Add(const T& item) { throw Exception("Method Add(item) is not available for a fixed size collection."); }

        /// <summary>Removes all elements from the list.</summary>
        virtual void Clear() { throw Exception("Method Clear() is not available for a fixed size collection."); }
    };

    /// <summary>
    /// Initializes a new instance of the array with the specified size.
    /// </summary>
    template <typename T>
    Array1D<T> new_Array1D(int size) { return new Array1DImpl<T>(size); }
}
