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

#ifndef cl_dotcpp_main_HashSet_hpp
#define cl_dotcpp_main_HashSet_hpp

#include <unordered_set>

#include <cl/dotcpp/main/system/collections/generic/ICollection.hpp>
#include <cl/dotcpp/main/system/collections/generic/IEnumerable.hpp>
#include <cl/dotcpp/main/system/collections/generic/IEnumerator.hpp>

namespace cl
{
    template <typename T> class TArray;

    /// Adapter class from STL has_set to .NET HashSet
    template <typename T>
    class THashSet : public detail::std_accessor_<cl::ITEnumerable<T>, std::unordered_set<Type> >
    {
    public:

        typedef detail::std_accessor_<cl::ITEnumerable<T>, std::unordered_set<Type> > base;
        typedef cl::ITEnumerable<T> cl_enumerator_type;
        typedef std::unordered_set<Type> std_base;
        typedef T& reference_type;

    public:

        /// <summary>Initializes a new instance of the HashSet.</summary>
        THashSet() : base()
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
        void copyTo(TArray<T>& arr) const;

        /// <summary>Copies HashSet elements to array starting at specified index.</summary>
        void copyTo(TArray<T>& arr, int arrIndex) const;

        /// <summary>Copies range of HashSet elements to array starting at specified index.</summary>
        void copyTo(TArray<T>& arr, int arrIndex, int count) const;

        /// <summary>Removes all elements in the specified collection from the current HashSet object.</summary>
        inline void exceptWith(const ITEnumerable<T>& other);

        /// <summary>Modifies the current HashSet to contain only elements that are present in that object and in the specified collection.</summary>
        inline void intersectWith(const ITEnumerable<T>& other);

        /// <summary>Determines whether a HashSet object is a proper subset of the specified collection.</summary>
        inline bool isProperSubsetOf(const ITEnumerable<T>& other) const;

        /// <summary>Determines whether a HashSet is a proper superset of the specified collection.</summary>
        inline bool isProperSupersetOf(const ITEnumerable<T>& other) const;

        /// <summary>Determines whether a HashSet is a subset of the specified collection.</summary>
        inline bool isSubsetOf(const ITEnumerable<T>& other) const;

        /// <summary>Determines whether a HashSet is a superset of the specified collection.</summary>
        inline bool isSupersetOf(const ITEnumerable<T>& other) const;

        /// <summary>Determines whether the current HashSet and a specified collection share common elements.</summary>
        inline bool overlaps(const ITEnumerable<T>& other) const;

        /// <summary>Removes the first occurrence of a specific object from the HashSet.</summary>
        inline bool remove(const T& item);

        /// <summary>Removes all the elements that match the predicate conditions.</summary>
        template <typename Predicate>
        inline int removeWhere(Predicate match);

        /// <summary>Determines whether a HashSet object and the specified collection contain the same elements.</summary>
        inline bool setEquals(const ITEnumerable<T>& other) const;

        /// <summary>Modifies the current HashSet to contain only elements that are present either in that object or in the specified collection, but not both.</summary>
        inline void symmetricExceptWith(const ITEnumerable<T>& other);

        /// <summary>Sets the capacity to the actual number of elements in the List, if that number is less than a threshold value.</summary>
        inline void trimExcess();

        /// <summary>Modifies the current HashSet to contain all elements that are present in itself and the specified collection.</summary>
        inline void unionWith(const ITEnumerable<T>& other);
    };
}

#endif // cl_dotcpp_main_HashSet_hpp