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
#include <cl/dotcpp/main/system/collections/generic/IObjectEnumerable.hpp>

namespace cl
{
    template <class T> class ListImpl; template <class T> using List = Ptr<ListImpl<T>>;

    /// <summary>
    /// Represents a strongly typed list of objects that can be accessed by index.
    /// Provides methods to search, sort, and manipulate lists.
    /// </summary>
    template <class T>
    class ListImpl : public IListImpl<T>, public virtual ObjectImpl, public std::vector<T>, public IObjectEnumerableImpl
    {
        typedef std::vector<T> base;
        typedef ListImpl<T> ThisType;

        template <class R> friend List<R> new_List();

    private: // CONSTRUCTORS

        /// <summary>
        /// Initializes a new instance of the list that is empty and has the default initial capacity.
        ///
        /// This constructor is private. Use new_List() function instead.
        /// </summary>
        ListImpl() {}

    public: // METHODS

        /// <summary>Returns an enumerator that iterates through the collection.</summary>
        virtual IEnumerator<T> GetEnumerator()
        {
            return new_Enumerator(std::vector<T>::begin(), std::vector<T>::end());
        }

        /// <summary>Returns random access begin iterator of the underlying std::vector.</summary>
        typename base::iterator begin() { return base::begin(); }

        /// <summary>Returns random access end iterator of the underlying std::vector.</summary>
        typename base::iterator end() { return base::end(); }

        /// <summary>Returns forward begin object iterator.</summary>
        virtual detail::std_object_iterator_wrapper object_begin()
        {
            return detail::make_obj_iterator(base::begin());
        }

        /// <summary>Returns forward end object iterator.</summary>
        virtual detail::std_object_iterator_wrapper object_end()
        {
            return detail::make_obj_iterator(base::end());
        }

        /// <summary>The number of items contained in the list.</summary>
        DOT_IMPL_GET(int, Count, { return this->size(); })

        /// <summary>The total number of elements the internal data structure can hold without resizing.</summary>
        DOT_PROP(int, Capacity, { return this->capacity(); }, { this->reserve(value); });

        /// <summary>Adds an object to the end of the list.</summary>
        virtual void Add(const T& item) { this->push_back(item); }

        /// <summary>Removes all elements from the list.</summary>
        virtual void Clear() { this->clear(); }

        /// <summary>Determines whether an element is in the list.</summary>
        virtual bool Contains(const T& item) { throw std::runtime_error("Not implemented.");  return false; } // TODO - implement

        /// <summary>Adds the elements of the specified collection to the end of the list.</summary>
        // TODO - implement void AddRange(const IEnumerable<T>& collection);

        /// <summary>Copies the elements of the current List(T) to a new array.</summary>
        Array1D<T> ToArray() const { return new Array1DImpl(*this); }

    public: // OPERATORS

        /// <summary>Gets or sets the element at the specified index (const version).</summary>
        virtual const T& operator[](int i) const { return base::operator[](i); }

        /// <summary>Gets or sets the element at the specified index (non-const version).</summary>
        virtual T& operator[](int i) { return base::operator[](i); }
    };

    /// <summary>
    /// Initializes a new instance of the list that is empty and has the default initial capacity.
    /// </summary>
    template <class T>
    List<T> new_List() { return new ListImpl<T>(); }
}
