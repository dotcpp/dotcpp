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

#include <set>

#include <dot/system/ptr.hpp>

namespace dot
{
    template <class T> class Array1DImpl; template <class T> using Array1D = ptr<Array1DImpl<T>>;

    ///!!! Provide .NET description Adapter class from STL set to .NET SortedSet
    template <class T>
    class SortedSet : public virtual object_impl
    {
    public:

        typedef detail::std_accessor_<dot::IEnumerable<T>, std::set<T> > base;
        typedef dot::IEnumerable<T> cl_enumerator_type;
        typedef std::set<T> std_base;

    public:

        /// <summary>Creates new empty instance of SortedSet.</summary>
        SortedSet() : base() {  }

        /// <summary>Gets number of elements in SortedList.</summary>
        inline int count() const
        {
            return this->get().size();
        }

        /// <summary>Gets the maximum value in SortedSet.</summary>
        inline T getMax() const;

        /// <summary>Gets the minimum value in SortedSet.</summary>
        inline T getMin() const;

        /// <summary>Adds the specified key and value to the SortedSet.</summary>
        inline bool add(const T& item);

        /// <summary>Removes all keys and values from the SortedSet.</summary>
        inline void clear();

        /// <summary>Searches element in SortedSet.</summary>
        inline bool contains(const T& item);

        /// <summary>Copies SortedSet elements to array starting at then begining of array.</summary>
        void copyTo(Array1D<T>& arr);

        /// <summary>Copies SortedSet elements to array starting at specified index.</summary>
        void copyTo(Array1D<T>& arr, int index);

        /// <summary>Copies a specified number of SortedSet elements to array starting at specified index.</summary>
        void copyTo(Array1D<T>& arr, int index, int count);

        /// <summary>Removes all elements in the specified collection from the current SortedSet object.</summary>
        inline void exceptWith(const IEnumerable<T>& other);

        /// <summary>Modifies the current SortedSet to contain only elements that
        /// are present in that object and in the specified collection.</summary>
        inline void intersectWith(const IEnumerable<T>& other);

        /// <summary>Determines whether a SortedSet object is a proper subset of the specified collection.</summary>
        inline bool isProperSubsetOf(const IEnumerable<T>& other);

        /// <summary>Determines whether a SortedSet is a proper superset of the specified collection.</summary>
        inline bool isProperSupersetOf(const IEnumerable<T>& other);

        /// <summary>Determines whether a HashSet is a subset of the specified collection.</summary>
        inline bool isSubsetOf(const IEnumerable<T>& other);

        /// <summary>Determines whether a SortedSet is a superset of the specified collection.</summary>
        inline bool isSupersetOf(const IEnumerable<T>& other);

        /// <summary>Determines whether the current SortedSet and a specified collection share common elements.</summary>
        inline bool overlaps(const IEnumerable<T>& other);

        /// <summary>Removes the first occurrence of a specific object from the SortedSet.</summary>
        inline bool remove(const T& item);

        /// <summary>Removes all the elements that match the predicate conditions.</summary>
        template <class Predicate>
        inline int removeWhere(Predicate match);

        /// <summary>Returns an IEnumerable that iterates over the SortedSet in reverse order.</summary>
        inline IEnumerable<T>& reverse();

        /// <summary>Determines whether a SortedSet object and the specified collection contain the same elements.</summary>
        inline bool setEquals(const IEnumerable<T>& other) const;

        /// <summary>Modifies the current SortedSet to contain only elements that are present
        /// either in that object or in the specified collection, but not both.</summary>
        inline void symmetricExceptWith(const IEnumerable<T>& other);

        /// <summary>Modifies the current SortedSet to contain all elements
        /// that are present in itself and the specified collection.</summary>
        inline void unionWith(const IEnumerable<T>& other);
    };
}
