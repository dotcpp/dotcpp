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
#include <dot/system/ptr.hpp>
#include <vector>

namespace dot
{
    template <class T> class array_impl; template <class T> using array = ptr<array_impl<T>>;

    /// <summary>
    /// Represents a strongly typed list of objects that can be accessed by index.
    /// Provides methods to search, sort, and manipulate lists.
    /// </summary>
    template <class T>
    class array_impl : public virtual object_impl, public std::vector<T>
    {
        typedef array_impl<T> self;
        typedef std::vector<T> base;

        template <class R> friend array<R> make_array(int size);
        template <class R> friend array<R> make_array(const std::vector<R>& obj);
        template <class R> friend array<R> make_array(std::vector<R>&& obj);

    private: // CONSTRUCTORS

        /// <summary>
        /// Initializes a new instance of the array with the specified size.
        ///
        /// This constructor is private. Use make_array(...) function instead.
        /// </summary>
        explicit array_impl(int size) : base(size) {}

        /// <summary>
        /// Create from std::vector using copy ctor.
        ///
        /// This constructor is private. Use make_array(...) function instead.
        /// </summary>
        explicit array_impl(const std::vector<T>& obj) : base(obj) {}

        /// <summary>
        /// Create from std::vector using move ctor.
        ///
        /// This constructor is private. Use make_array(...) function instead.
        /// </summary>
        explicit array_impl(std::vector<T>&& obj) : base(obj) {}

    public: // METHODS

        /// <summary>The number of items contained in the array.</summary>
        int count() { return size(); }

        /// <summary>Delete methods from the base class std::vector that modify array size.</summary>
        void push_back(const T& obj) = delete;

        /// <summary>Delete methods from the base class std::vector that modify array size.</summary>
        T pop_back(const T& obj) = delete;

        /// <summary>Delete methods from the base class std::vector that modify array size.</summary>
        void resize(size_t size) = delete;

    public: // OPERATORS

        /// <summary>Gets or sets the element at the specified index (const version).</summary>
        const T& operator[](int i) const { return base::operator[](size_t(i)); }

        /// <summary>Gets or sets the element at the specified index (non-const version).</summary>
        T& operator[](int i) { return base::operator[](size_t(i)); }

    public: // STATIC

        /// <summary>
        /// Sorts the elements in a one-dimensional Array
        /// using default comparer of array elements.
        ///
        /// In C#, this method takes Array base and there is
        /// an error message if the array is multidimensional.
        /// In C+, we will detect this error at compile time.
        /// </summary>
        template <class T>
        static void sort(const array<T> obj)
        {
            std::sort(obj->begin(), obj->end());
        }

    public: // REFLECTION

        virtual type_t type() { return typeof(); }
        static type_t typeof();
    };

    /// <summary>
    /// Initializes a new instance of the array with the specified size.
    /// </summary>
    template <class T>
    array<T> make_array(int size) { return new array_impl<T>(size); }

    /// <summary>
    /// Create from std::vector using copy ctor.
    /// </summary>
    template <class T>
    array<T> make_array(const std::vector<T>& obj) { return new array_impl<T>(obj); }

    /// <summary>
    /// Create from std::vector using move ctor.
    /// </summary>
    template <class T>
    array<T> make_array(std::vector<T>&& obj) { return new array_impl<T>(obj); }
}

namespace std
{
    /// <summary>Implements begin() used by STL and similar algorithms.</summary>
    template <class T>
    auto begin(dot::array<T>& obj)
    {
        return obj->begin();
    }

    /// <summary>Implements end() used by STL and similar algorithms.</summary>
    template <class T>
    auto end(dot::array<T>& obj)
    {
        return obj->end();
    }
}