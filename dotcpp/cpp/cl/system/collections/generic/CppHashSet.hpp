/*
Copyright (C) 2003-2015 CompatibL

This file is part of .C++ project, an open source implementation of
selected .NET class library APIs in native C++ with optional support
for adjoint algorithmic differentiation (AAD), available from

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

#ifndef __cl_system_collections_generic_HashSet_hpp__
#define __cl_system_collections_generic_HashSet_hpp__

#include <hash_set>

#include <cl/system/collections/generic/ICppCollection.hpp>
#include <cl/system/collections/generic/ICppEnumerable.hpp>
#include <cl/system/collections/generic/ICppEnumerator.hpp>

namespace cl
{
    template <typename T> class CppArray;

    /// Adapter class from STL has_set to .NET HashSet
    template <typename T>
    class CppHashSet : public detail::std_accessor_<cl::ICppEnumerable<T>, stdext::hash_set<T> >
    {
    public:

        typedef detail::std_accessor_<cl::ICppEnumerable<T>, std::hash_set<T> > base;
        typedef cl::ICppEnumerable<T> cl_enumerator_type;
        typedef std::hash_set<T> std_base;
        typedef T& reference_type;

    public:

        /// <summary>Initializes a new instance of the HashSet.</summary>
        CppHashSet() : base()
        {
        }

        /// <summary>Gets number of elements in HashSet.</summary>
        inline int getCount() const
        {
            return this->get().size();
        }

        /// <summary>Adds the specified element to the HashSet.</summary>
        inline bool add(T item);

        /// <summary>Removes all keys and values from the HashSet.</summary>
        inline void clear();

        /// <summary>Searches element in HashSet.</summary>
        inline bool contains(const T& item) const;

        /// <summary>Copies HashSet elements to array starting at then begining of arrray.</summary>
        void copyTo(CppArray<T>& arr) const;

        /// <summary>Copies HashSet elements to array starting at specified index.</summary>
        void copyTo(CppArray<T>& arr, int arrIndex) const;

        /// <summary>Copies range of HashSet elements to array starting at specified index.</summary>
        void copyTo(CppArray<T>& arr, int arrIndex, int count) const;

        /// <summary>Removes all elements in the specified collection from the current HashSet object.</summary>
        inline void exceptWith(const ICppEnumerable<T>& other);

        /// <summary>Modifies the current HashSet to contain only elements that are present in that object and in the specified collection.</summary>
        inline void intersectWith(const ICppEnumerable<T>& other);

        /// <summary>Determines whether a HashSet object is a proper subset of the specified collection.</summary>
        inline bool isProperSubsetOf(const ICppEnumerable<T>& other) const;

        /// <summary>Determines whether a HashSet is a proper superset of the specified collection.</summary>
        inline bool isProperSupersetOf(const ICppEnumerable<T>& other) const;

        /// <summary>Determines whether a HashSet is a subset of the specified collection.</summary>
        inline bool isSubsetOf(const ICppEnumerable<T>& other) const;

        /// <summary>Determines whether a HashSet is a superset of the specified collection.</summary>
        inline bool isSupersetOf(const ICppEnumerable<T>& other) const;

        /// <summary>Determines whether the current HashSet and a specified collection share common elements.</summary>
        inline bool overlaps(const ICppEnumerable<T>& other) const;

        /// <summary>Removes the first occurrence of a specific object from the HashSet.</summary>
        inline bool remove(const T& item);

        /// <summary>Removes all the elements that match the predicate conditions.</summary>
        template <typename Predicate>
        inline int removeWhere(Predicate match);

        /// <summary>Determines whether a HashSet object and the specified collection contain the same elements.</summary>
        inline bool setEquals(const ICppEnumerable<T>& other) const;

        /// <summary>Modifies the current HashSet to contain only elements that are present either in that object or in the specified collection, but not both.</summary>
        inline void symmetricExceptWith(const ICppEnumerable<T>& other);

        /// <summary>Sets the capacity to the actual number of elements in the List, if that number is less than a threshold value.</summary>
        inline void trimExcess();

        /// <summary>Modifies the current HashSet to contain all elements that are present in itself and the specified collection.</summary>
        inline void unionWith(const ICppEnumerable<T>& other);
    };
}

#endif