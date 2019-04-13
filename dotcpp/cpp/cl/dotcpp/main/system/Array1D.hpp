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
#include <cl/dotcpp/main/system/Array.hpp>
#include <cl/dotcpp/main/detail/array_base.hpp>

namespace cl
{
    template <class T> class Array1DImpl; template <class T> using Array1D = Ptr<Array1DImpl<T>>;

    /// <summary>
    /// Represents a strongly typed list of objects that can be accessed by index.
    /// Provides methods to search, sort, and manipulate lists.
    /// </summary>
    template <class T>
    class Array1DImpl : public ArrayImpl, public detail::array_base<T>
    {
        typedef Array1DImpl<T> self;
        typedef detail::array_base<T> base;

        template <class R> friend Array1D<R> new_Array1D(int size);
        template <class R> friend Array1D<R> new_Array1D(const std::vector<R>& obj);
        template <class R> friend Array1D<R> new_Array1D(std::vector<R>&& obj);

    private: // CONSTRUCTORS

        /// <summary>
        /// Initializes a new instance of the array with the specified size.
        ///
        /// This constructor is private. Use new_Array1D(size) function instead.
        /// </summary>
        explicit Array1DImpl(int size) : base(size) {}

        /// <summary>
        /// Create from std::vector using copy ctor.
        ///
        /// This constructor is private. Use new_Array1D(size) function instead.
        /// </summary>
        explicit Array1DImpl(const std::vector<T>& obj) : base(obj) {}

        /// <summary>
        /// Create from std::vector using move ctor.
        ///
        /// This constructor is private. Use new_Array1D(size) function instead.
        /// </summary>
        explicit Array1DImpl(std::vector<T>&& obj) : base(obj) {}

    public: // PROPERTIES

        /// <summary>The number of items contained in the list.</summary>
        DOT_IMPL_GET(int, Count, { return this->size(); })

    public: // METHODS

        /// <summary>Returns random access begin iterator of the underlying std::vector.</summary>
        auto begin() { return base::begin(); }

        /// <summary>Returns random access end iterator of the underlying std::vector.</summary>
        auto end() { return base::end(); }

    public: // OPERATORS

        /// <summary>Gets or sets the element at the specified index (const version).</summary>
        const T& operator[](int i) const { return base::operator[](size_t(i)); }

        /// <summary>Gets or sets the element at the specified index (non-const version).</summary>
        T& operator[](int i) { return base::operator[](size_t(i)); }

    public: // REFLECTION

        DOT_REFLECTION
        (
            "System", "T[]" // TODO provide custom logic to resolve T[] into specific name
        )
    };

    /// <summary>
    /// Initializes a new instance of the array with the specified size.
    /// </summary>
    template <class T>
    Array1D<T> new_Array1D(int size) { return new Array1DImpl<T>(size); }

    /// <summary>
    /// Create from std::vector using copy ctor.
    /// </summary>
    template <class T>
    Array1D<T> new_Array1D(const std::vector<T>& obj) { return new Array1DImpl<T>(obj); }

    /// <summary>
    /// Create from std::vector using move ctor.
    /// </summary>
    template <class T>
    Array1D<T> new_Array1D(std::vector<T>&& obj) { return new Array1DImpl<T>(obj); }

    /// <summary>
    /// Sorts the elements in a one-dimensional Array
    /// using default comparer of array elements.
    ///
    /// In C#, this method takes Array base and there is
    /// an error message if the array is multidimensional.
    /// In C+, we will detect this error at compile time.
    /// </summary>
    template <class T>
    void Array::Sort(const Array1D<T> obj)
    {
        std::sort(obj->begin(), obj->end());
    }
}

namespace std
{
    /// <summary>Implements begin() used by STL and similar algorithms.</summary>
    template <class T>
    auto begin(cl::Array1D<T>& obj)
    {
        return obj->begin();
    }

    /// <summary>Implements end() used by STL and similar algorithms.</summary>
    template <class T>
    auto end(cl::Array1D<T>& obj)
    {
        return obj->end();
    }
}