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

#include <dot/system/ptr.hpp>
#include <dot/system/collections/list_base.hpp>

namespace dot
{
    template <class T> class list_impl; template <class T> using list = ptr<list_impl<T>>;
    class type_builder_impl; using type_builder = ptr<type_builder_impl>;

    /// 
    /// Represents a strongly typed collection of objects that can be accessed by index.
    /// 
    template <class T>
    class list_impl : public virtual object_impl, public std::vector<T>, public list_base_impl
    {
        template <class R> friend list<R> make_list();
        template <class R> friend list<R> make_list(const std::vector<R> & obj);
        template <class R> friend list<R> make_list(std::vector<R>&& obj);
        template <class R> friend list<R> make_list(const std::initializer_list<R> & obj);
        template <class R> friend list<R> make_list(int size);

        typedef list_impl<T> self;
        typedef std::vector<T> base;

    private: // CONSTRUCTORS

        /// 
        /// Create empty list with default initial capacity.
        ///
        /// This constructor is private. Use make_list(...) function instead.
        /// 
        list_impl() {}

        /// 
        /// Construct from vector using deep copy semantics.
        ///
        /// This constructor is private. Use make_list(...) function instead.
        /// 
        explicit list_impl(const std::vector<T>& obj) : base(obj) {}

        /// 
        /// Construct from vector using move semantics.
        ///
        /// This constructor is private. Use make_list(...) function instead.
        /// 
        explicit list_impl(std::vector<T>&& obj) : base(obj) {}

        /// 
        /// Construct from initializer list.
        ///
        /// This constructor is private. Use make_list(...) function instead.
        /// 
        explicit list_impl(const std::initializer_list<T>& obj) : base(obj) {}

        /// 
       /// Construct from int.
       ///
       /// This constructor is private. Use make_list(...) function instead.
       /// 
       explicit list_impl(int size) : base(size) {}

    public: // METHODS

        /// The number of items contained in the list.
        int count() { return this->size(); }

        /// Set total number of elements the internal data structure can hold without resizing.
        void set_capacity(int value) { this->reserve(value); }

        /// Adds an object to the end of the list.
        void add(const T& item) { this->push_back(item); }

        /// Determines whether an element is in the list.
        virtual bool contains(const T& item)
        {
            return std::find(begin(), end(), item) != end();
        }

        /// Adds the elements of the specified collection to the end of the list.
        // TODO - implement void AddRange(const IEnumerable<T>& collection);

        /// Removes the first occurrence of a specific object from the List.
        bool remove(const T& item)
        {
            auto iter = std::find(begin(), end(), item);
            if (iter != end())
            {
                this->erase(iter);
                return true;
            }
            return false;
        }

    public: // VIRTUAL METHODS

        /// Get object from collection by index.
        virtual object get_item(int index) override
        {
            return this->operator[](index);
        }

        /// Set object from collection by index.
        virtual void set_item(int index, object value) override
        {
            this->operator[](index) = (T)value;
        }

        /// Get length of collection.
        virtual int get_length() override
        {
            return this->size();
        }

        /// Add object to end of collection.
        virtual void add_object(object item) override
        {
            add((T)item);
        }

    public: // OPERATORS

        /// Gets or sets the element at the specified index (const version).
        virtual const T& operator[](int i) const { return base::operator[](i); }

        /// Gets or sets the element at the specified index (non-const version).
        virtual T& operator[](int i) { return base::operator[](i); }

    public: // REFLECTION

        virtual type_t type() { return typeof(); }
        static type_t typeof();
    };

    /// Create empty list with default initial capacity.
    template <class T>
    list<T> make_list() { return new list_impl<T>(); }

    /// Construct from vector using deep copy semantics.
    template <class T>
    list<T> make_list(const std::vector<T> & obj) { return new list_impl<T>(obj); }

    /// Construct from vector using move semantics.
    template <class T>
    list<T> make_list(std::vector<T>&& obj) { return new list_impl<T>(std::forward<std::vector<T>>(obj)); }

    /// Construct from initializer list.
    template <class T>
    list<T> make_list(const std::initializer_list<T> & obj) { return new list_impl<T>(obj); }

    /// Construct from int.
    template <class T>
    list<T> make_list(int size) { return new list_impl<T>(size); }
}
