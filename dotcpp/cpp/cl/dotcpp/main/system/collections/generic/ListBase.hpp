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

#include <cl/dotcpp/main/system/collections/generic/IList.hpp>

namespace cl
{
    /// <summary>
    /// Common base to List(T) and Array1D(T)
    /// </summary>
    template <typename T>
    class ListBaseImpl : public IListImpl<T>, public virtual ObjectImpl, public std::vector<T>
    {
        typedef std::vector<T> base;

    protected: // CONSTRUCTORS

        /// <summary>
        /// Initializes a new instance of the list that is empty and has the default initial capacity.
        /// </summary>
        ListBaseImpl() {}

    public: // METHODS

        /// <summary>Returns an enumerator that iterates through the collection.</summary>
        virtual IEnumerator<T> GetEnumerator()
        {
            return new_Enumerator(std::vector<T>::begin(), std::vector<T>::end());
        }

        /// <summary>Implements begin() used by STL and similar algorithms.</summary>
        virtual detail::std_iterator_wrapper<T> begin()
        {
            return detail::std_iterator_wrapper<T>(detail::make_iterator(std::vector<T>::begin()));
        }

        /// <summary>Implements end() used by STL and similar algorithms.</summary>
        virtual detail::std_iterator_wrapper<T> end()
        {
            return detail::std_iterator_wrapper<T>(detail::make_iterator(std::vector<T>::end()));
        }

        /// <summary>The number of items contained in the list.</summary>
        DOT_IMPL_GET(ListBaseImpl, int, Count, { return this->size(); })

        /// <summary>The total number of elements the internal data structure can hold without resizing.</summary>
        DOT_PROP(ListBaseImpl, int, Capacity, { return this->capacity(); }, { this->reserve(value); });

        /// <summary>Adds an object to the end of the list.</summary>
        virtual void Add(const T& item) { this->push_back(item); }

        /// <summary>Removes all elements from the list.</summary>
        virtual void Clear() { this->clear(); }

        /// <summary>Determines whether an element is in the list.</summary>
        virtual bool Contains(const T& item) { return false; } // TODO - implement

    public: // OPERATORS

        /// <summary>Gets or sets the element at the specified index (const version).</summary>
        virtual const T& operator[](int i) const { return base::operator[](i); }

        /// <summary>Gets or sets the element at the specified index (non-const version).</summary>
        virtual T& operator[](int i) { return base::operator[](i); }

        /*

        /// <summary>Copies list elements to array starting at then begining of arrray.</summary>
        void copyTo(Array1D<T>& arr) const;

        /// <summary>Copies ListBase elements to array starting at specified index.</summary>
        void copyTo(Array1D<T>& arr, int index) const;

        /// <summary>Copies range of ListBase elements to array starting at specified index.</summary>
        void copyTo(int index, Array1D<T>& arr, int arrIndex, int count) const;

        /// <summary>Looks for element in ListBase that matches predicate condition and returns its index.</summary>
        template <typename Predicate>
        inline int findLastIndex(Predicate match) const
        {
            return std::distance(this->begin(), std::find_if(this->rbegin(), this->rend(), match).base() - 1);
        }

        /// <summary>Looks for element in ListBase starting at specified index that match predicate condition and returns it index in ListBase.</summary>
        template <typename Predicate>
        inline int findLastIndex(int startIndex, Predicate match) const;

        /// <summary>Looks for element in ranghe of elements in ListBase that match predicate condition and returns it index in ListBase.</summary>
        template <typename Predicate>
        inline int findLastIndex(int startIndex, int count, Predicate match) const;

        /// <summary>Returns element in ListBase that matches predicate condition.</summary>
        template <typename Predicate>
        inline T const & findLast(Predicate match) const
        {
            return *std::find_if(this->rbegin(), this->rend(), match);
        }

        /// <summary>Returns element in ListBase that matches predicate condition.</summary>
        template <typename Predicate>
        inline T& findLast(Predicate match)
        {
            return *std::find_if(this->rbegin(), this->rend(), match);
        }

        /// <summary>Apples action to each element in ListBase.</summary>
        template <typename TAction>
        inline void forEach(TAction action)
        {
            std::for_each(this->begin(), this->end(), action);
        }

        /// <summary>Returns a sublist.</summary>
        ListBase<T> getRange(int index, int count) const;

        /// <summary>Searches for the specified object and returns the index of the first entire in ListBase.</summary>
        int IndexOf(const T& item) const;

        /// <summary>Searches for the specified object and returns index of the first occurrence in ListBase.</summary>
        int indexOf(const T& item, int index) const;

        /// <summary>Searches for the specified object and returns index of the first occurrence in ListBase.</summary>
        int indexOf(const T& item, int index, int count) const;

        /// <summary>Inserts an element into ListBase<T> at the specified index.</summary>
        void insert(int index, T item);

        /// <summary>Inserts the elements of a collection into ListBase at the specified index.</summary>
        void insertRange(int index, IEnumerable<T> const& collection);

        /// <summary>Searches for the specified object and returns the index of the last occurrence in ListBase.</summary>
        int lastIndexOf(const T& item);

        /// <summary>Searches for the specified object and returns the index of the last occurrence in ListBase.</summary>
        int lastIndexOf(const T& item, int index);

        /// <summary>Searches for the specified object and returns the index of the last occurrence in ListBase.</summary>
        int lastIndexOf(const T& item, int index, int count);

        /// <summary>Removes the first occurrence of a specific object from the ListBase.</summary>
        bool remove(const T& item);

        /// <summary>Removes all the elements that match the predicate conditions.</summary>
        template <typename Predicate>
        inline int removeAll(Predicate match)
        {
            unsigned int sizeold = this->get().size();
            std::remove_if(this->begin(), this->end(), match);
            return sizeold - this->get().size();
        }

        /// <summary>Removes the element at the specified index of the ListBase.</summary>
        void removeAt(int index)
        {
            assert(this->get().size() > index);
            this->get().erase(this->begin() + index);
        }

        /// <summary>Removes a range of elements from the ListBase.</summary>
        void removeRange(int index, int count);

        /// <summary>Reverses the order of the elements in the ListBase.</summary>
        void reverse();

        /// <summary>Reverses the order of the elements in the specified range.</summary>
        void reverse(int index, int count);

        /// <summary>Sorts the elements in the list using the default comparer.</summary>
        void Sort();

        /// <summary>Sorts the elements in a range of elements in ListBase using the specified comparer.</summary>
        template <typename Comparer>
        void sort(int index, int count, Comparer comparer)
        {
            std::sort(this->begin() + index, this->begin() + index + count, comparer);
        }

        /// <summary>Copies list elements to an array.</summary>
        Array1D<T> ToArray() const;

        */
    };
}
