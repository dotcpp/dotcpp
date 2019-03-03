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

#pragma once

#include <cl/dotcpp/main/system/Ptr.hpp>
#include <cl/dotcpp/main/system/collections/generic/ICollection.hpp>
#include <cl/dotcpp/main/system/collections/generic/IEnumerable.hpp>
#include <cl/dotcpp/main/system/collections/generic/IEnumerator.hpp>

#include <deque>

namespace cl
{
    /// <summary>
    /// Represents a strongly typed list of objects that can be accessed by index.
    /// Provides methods to search, sort, and manipulate lists.
    /// </summary>
    template <typename T>
    class List : public std::vector<T>
    {
        typedef std::vector<T> base;

    public: // CONSTRUCTORS

        /// <summary>Creates a new empty instance of List.</summary>
        List() : base() {}

    public: // METHODS

        /// <summary>The number of elements contained in the list.</summary>
        int Count() const { return size(); }

        /// <summary>Adds an object to the end of the list.</summary>
        void Add(const T& item) { push_back(item); }

        /// <summary>Adds the elements of the specified collection to the end of the list.</summary>
        // TODO void AddRange(const IEnumerable<T>& collection);

        /// <summary>Removes all elements from the list.</summary>
        void Clear() { clear(); }

        /// <summary>Determines whether an element is in the list.</summary>
        bool Contains(const T& item);

        /// <summary>Copies list elements to array starting at then begining of arrray.</summary>
        void copyTo(Array<T>& arr) const;

        /// <summary>Copies List elements to array starting at specified index.</summary>
        void copyTo(Array<T>& arr, int index) const;

        /// <summary>Copies range of List elements to array starting at specified index.</summary>
        void copyTo(int index, Array<T>& arr, int arrIndex, int count) const;

        /// <summary>Looks for element in List starting at specified index that match predicate condition and returns it index in List.</summary>
        template <typename Predicate>
        inline int findLastIndex(int startIndex, Predicate match) const;

        /// <summary>Looks for element in ranghe of elements in List that match predicate condition and returns it index in List.</summary>
        template <typename Predicate>
        inline int findLastIndex(int startIndex, int count, Predicate match) const;

        /// <summary>Apples action to each element in List.</summary>
        template <typename TAction>
        inline void forEach(TAction action)
        {
            std::for_each(begin(), end(), action);
        }

        /// <summary>Returns a sublist.</summary>
        List<T> getRange(int index, int count) const;

        /// <summary>Searches for the specified object and returns the index of the first entire in List.</summary>
        int IndexOf(const T& item) const;

        /// <summary>Searches for the specified object and returns index of the first occurrence in List.</summary>
        int indexOf(const T& item, int index) const;

        /// <summary>Searches for the specified object and returns index of the first occurrence in List.</summary>
        int indexOf(const T& item, int index, int count) const;

        /// <summary>Inserts an element into List<T> at the specified index.</summary>
        void insert(int index, T item);

        /// <summary>Inserts the elements of a collection into List at the specified index.</summary>
        void insertRange(int index, IEnumerable<T> const& collection);

        /// <summary>Searches for the specified object and returns the index of the last occurrence in List.</summary>
        int lastIndexOf(const T& item);

        /// <summary>Searches for the specified object and returns the index of the last occurrence in List.</summary>
        int lastIndexOf(const T& item, int index);

        /// <summary>Searches for the specified object and returns the index of the last occurrence in List.</summary>
        int lastIndexOf(const T& item, int index, int count);

        /// <summary>Removes the first occurrence of a specific object from the List.</summary>
        bool remove(const T& item);

        /// <summary>Removes all the elements that match the predicate conditions.</summary>
        template <typename Predicate>
        inline int removeAll(Predicate match)
        {
            unsigned int sizeold = this->get().size();
            std::remove_if(begin(), end(), match);
            return sizeold - this->get().size();
        }

        /// <summary>Removes the element at the specified index of the List.</summary>
        void removeAt(int index)
        {
            assert(this->get().size() > index);
            this->get().erase(begin() + index);
        }

        /// <summary>Removes a range of elements from the List.</summary>
        void removeRange(int index, int count);

        /// <summary>Reverses the order of the elements in the List.</summary>
        void reverse();

        /// <summary>Reverses the order of the elements in the specified range.</summary>
        void reverse(int index, int count);

        /// <summary>Sorts the elements in the list using the default comparer.</summary>
        void Sort();

        /// <summary>Sorts the elements in a range of elements in List using the specified comparer.</summary>
        template <typename Comparer>
        void sort(int index, int count, Comparer comparer)
        {
            std::sort(begin() + index, begin() + index + count, comparer);
        }

        /// <summary>Copies list elements to an array.</summary>
        Array<T> ToArray() const;
    };
}
