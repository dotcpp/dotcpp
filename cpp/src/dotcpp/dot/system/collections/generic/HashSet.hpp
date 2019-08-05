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

#include <unordered_set>
#include <dot/system/Exception.hpp>
#include <dot/system/array1d.hpp>
#include <dot/system/collections/generic/list.hpp>

namespace dot
{
    template <class T> class HashSetImpl;
    template <class T> using HashSet = ptr<HashSetImpl<T>>;

    /// <summary>Represents a set of values.</summary>
    template <class T>
    class HashSetImpl : public virtual object_impl, public std::unordered_set<T>
    {
        typedef HashSetImpl<T> self;
        typedef std::unordered_set<T> base;

        template <class R> friend HashSet<R> new_HashSet();
        template <class R> friend HashSet<R> new_HashSet(list<R> collection);

    protected: // CONSTRUCTORS

        /// <summary>Initializes a new instance of the HashSet class that is empty
        /// and uses the default equality comparer for the set type.</summary>
        HashSetImpl() = default;

        /// <summary>
        /// Initializes a new instance of the HashSet class that uses the default
        /// equality comparer for the set type, contains elements copied from the specified
        /// collection, and has sufficient capacity to accommodate the number of elements copied.
        /// </summary>
        explicit HashSetImpl(list<T> collection)
        {
            for (T const & item : collection)
                this->Add(item);
        }

    public: // PROPERTIES

        /// <summary>Gets the number of elements that are contained in the set.</summary>
        int count() { return this->size(); }

    public: // METHODS

        /// <summary>Adds the specified element to a set.</summary>
        void Add(const T& item)
        {
            std::pair<typename base::iterator, bool> res = this->insert(item);
            //return res.second;
        }

        /// <summary>Removes all elements from a HashSet object.</summary>
        void Clear()
        {
            this->clear();
        }

        /// <summary>Determines whether a HashSet object contains the specified element.</summary>
        bool contains(const T& item)
        {
            auto iter = this->find(item);
            return iter != this->end();
        }

        /// <summary>Removes the specified element from a HashSet object.</summary>
        bool Remove(const T& item)
        {
            return this->erase(item) != 0;
        }

        /// <summary>Sets the capacity of a HashSet object to the actual number of elements
        /// it contains,rounded up to a nearby, implementation-specific value.</summary>
        void TrimExcess()
        {
            this->reserve(this->size());
        }

        /// <summary>Searches the set for a given value and returns the equal value it finds, if any.</summary>
        bool try_get_value(const T& equalValue, T& actualValue)
        {
            auto iter = this->find(equalValue);
            if (iter != this->end())
            {
                actualValue = *iter;
                return true;
            }
            return false;
        }

        /// <summary>Removes all elements in the specified collection from the current HashSet object.</summary>
        void ExceptWith(list<T> other)
        {
            for (T const& item : other)
            {
                this->Remove(item);
            }
        }

        /// <summary>Modifies the current HashSet object to contain only elements
        /// that are present in that object and in the specified collection.</summary>
        void IntersectWith(list<T> other)
        {
            list<T> left = make_list<T>();
            for (T const& item : other)
            {
                if (this->contains(item))
                    left->add(item);
            }

            this->Clear();
            for (T const& item : left) this->Add(item);
        }
    };

    template <class T>
    inline HashSet<T> new_HashSet() { return new HashSetImpl<T>(); }

    template <class T>
    inline HashSet<T> new_HashSet(list<T> collection) { return new HashSetImpl<T>(collection); }
}
