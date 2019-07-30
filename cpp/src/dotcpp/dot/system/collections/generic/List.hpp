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

#include <dot/system/collections/generic/IList.hpp>

namespace dot
{
    template <class T> class ListImpl; template <class T> using List = ptr<ListImpl<T>>;
    class TypeBuilderImpl; using TypeBuilder = ptr<TypeBuilderImpl>;

    /// <summary>
    /// Represents a strongly typed list of objects that can be accessed by index.
    /// Provides methods to search, sort, and manipulate lists.
    /// </summary>
    template <class T>
    class ListImpl : public IListImpl<T>, public virtual object_impl, public std::vector<T>
    {
        template <class R> friend List<R> new_List();
        template <class R> friend List<R> new_List(const std::vector<R> & obj);
        template <class R> friend List<R> new_List(std::vector<R>&& obj);
        template <class R> friend List<R> new_List(const std::initializer_list<R> & obj);

        typedef ListImpl<T> self;
        typedef std::vector<T> base;

    private: // CONSTRUCTORS

        /// <summary>
        /// Initializes a new instance of the list that is empty and has the default initial capacity.
        ///
        /// This constructor is private. Use new_List() function instead.
        /// </summary>
        ListImpl() {}

        explicit ListImpl(const std::vector<T>& obj) : base(obj) {}

        explicit ListImpl(std::vector<T>&& obj) : base(obj) {}

        explicit ListImpl(const std::initializer_list<T>& obj) : base(obj) {}

    public: // METHODS

        /// <summary>Returns random access begin iterator of the underlying std::vector.</summary>
        typename base::iterator begin() { return base::begin(); }

        /// <summary>Returns random access end iterator of the underlying std::vector.</summary>
        typename base::iterator end() { return base::end(); }

        /// <summary>The number of items contained in the list.</summary>
        int count() override { return this->size(); }

        /// <summary>The total number of elements the internal data structure can hold without resizing.</summary>
        DOT_PROP(int, Capacity, { return this->capacity(); }, { this->reserve(value); });

        /// <summary>Adds an object to the end of the list.</summary>
        virtual void Add(const T& item) { this->push_back(item); }

        /// <summary>
        /// Adds an item to the end of the collection.
        ///
        /// In C\#, the non-generic method is implemented for the interface
        /// but not for the class to avoid ambiguous conversions. Because
        /// in C++ this cannot be done, here this method has object prefix.
        /// </summary>
        virtual void objectAdd(object item) { this->push_back((T)item); }

        /// <summary>Removes all elements from the list.</summary>
        virtual void Clear() { this->clear(); }

        /// <summary>Determines whether an element is in the list.</summary>
        virtual bool Contains(const T& item)
        {
            return std::find(begin(), end(), item) != end();
        }

        /// <summary>Adds the elements of the specified collection to the end of the list.</summary>
        // TODO - implement void AddRange(const IEnumerable<T>& collection);

        /// <summary>Removes the first occurrence of a specific object from the List.</summary>
        virtual bool Remove(const T& item)
        {
            auto iter = std::find(begin(), end(), item);
            if (iter != end())
            {
                this->erase(iter);
                return true;
            }
            return false;
        }

        /// <summary>Copies the elements of the current List(T) to a new array.</summary>
        Array1D<T> ToArray() const { return new_Array1D(*this); }

    public: // OPERATORS

        /// <summary>Gets or sets the element at the specified index (const version).</summary>
        virtual const T& operator[](int i) const { return base::operator[](i); }

        /// <summary>Gets or sets the element at the specified index (non-const version).</summary>
        virtual T& operator[](int i) { return base::operator[](i); }

    public: // REFLECTION

        virtual type_t type() { return typeof(); }
        static type_t typeof();
    };

    /// <summary>
    /// Initializes a new instance of the list that is empty and has the default initial capacity.
    /// </summary>
    template <class T>
    List<T> new_List() { return new ListImpl<T>(); }

    template <class T>
    List<T> new_List(const std::vector<T> & obj) { return new ListImpl<T>(obj); }

    template <class T>
    List<T> new_List(std::vector<T>&& obj) { return new ListImpl<T>(std::forward<std::vector<T>>(obj)); }

    template <class T>
    List<T> new_List(const std::initializer_list<T> & obj) { return new ListImpl<T>(obj); }

}
