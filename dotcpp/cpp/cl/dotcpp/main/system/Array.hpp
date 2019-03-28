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
#include <cl/dotcpp/main/system/ObjectImpl.hpp>

namespace cl
{
    class ArrayImpl;

    template <class> class Array1DImpl; template <class T> using Array1D = Ptr<Array1DImpl<T>>;

    /// <summary>
    /// Common base to List(T) and Array1D(T)
    /// </summary>
    class ArrayImpl : public virtual ObjectImpl
    {
        template <class T> friend class Array1DImpl;
        template <class T> friend class Array2DImpl;
        template <class T> friend class Array3DImpl;

    public: // METHODS

        /// <summary>The number of items contained in all dimensions of the list.</summary>
        DOT_DECL_GET(ArrayImpl, int, Count)
    };

    class Array : public Ptr<ArrayImpl>
    {
        typedef Ptr<ArrayImpl> base;

    public: // CONSTRUCTORS

        /// <summary>
        /// Default constructor.
        /// </summary>
        Array() : base() {}

        /// <summary>Construct Array from pointer to derived types.</summary>
        Array(const Ptr<ArrayImpl>& ptr) : base(ptr) {}

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
        static void Sort(const Array1D<T> obj);
    };
}
