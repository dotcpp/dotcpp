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
#include <dot/system/collections/generic/ISet.hpp>
#include <dot/system/collections/generic/List.hpp>

namespace dot
{
    template <class T> class Array1DImpl; template <class T> using Array1D = ptr<Array1DImpl<T>>;

    template <class T> class HashSetImpl;
    template <class T> using HashSet = ptr<HashSetImpl<T>>;

    /// <summary>Represents a set of values.</summary>
    template <class T>
    class HashSetImpl
        : public virtual object_impl
        , public ISetImpl<T>
        , public std::unordered_set<T>
    {
        typedef HashSetImpl<T> self;
        typedef std::unordered_set<T> base;

        template <class T_> friend HashSet<T_> new_HashSet();
        template <class T_> friend HashSet<T_> new_HashSet(IEnumerable<T_> collection);

    protected: // CONSTRUCTORS

        /// <summary>Initializes a new instance of the HashSet class that is empty
        /// and uses the default equality comparer for the set type.</summary>
        HashSetImpl() = default;

        /// <summary>
        /// Initializes a new instance of the HashSet class that uses the default
        /// equality comparer for the set type, contains elements copied from the specified
        /// collection, and has sufficient capacity to accommodate the number of elements copied.
        /// </summary>
        explicit HashSetImpl(IEnumerable<T> collection)
        {
            for (T const & item : collection)
                this->Add(item);
        }

    public: // PROPERTIES

        /// <summary>Gets the number of elements that are contained in the set.</summary>
        int count() override { return this->size(); }

    public: // METHODS

        /// <summary>Adds the specified element to a set.</summary>
        virtual void Add(const T& item) override
        {
            std::pair<typename base::iterator, bool> res = this->insert(item);
            //return res.second;
        }

        /// <summary>Removes all elements from a HashSet object.</summary>
        virtual void Clear() override
        {
            this->clear();
        }

        /// <summary>Determines whether a HashSet object contains the specified element.</summary>
        virtual bool Contains(const T& item) override
        {
            auto iter = this->find(item);
            return iter != this->end();
        }

        /// <summary>Removes the specified element from a HashSet object.</summary>
        virtual bool Remove(const T& item) override
        {
            return this->erase(item) != 0;
        }

        /// <summary>Returns random access begin iterator of the underlying std::unordered_set.</summary>
        typename base::iterator begin() { return base::begin(); }

        /// <summary>Returns random access end iterator of the underlying std::unordered_set.</summary>
        typename base::iterator end() { return base::end(); }

        /// <summary>Sets the capacity of a HashSet object to the actual number of elements
        /// it contains,rounded up to a nearby, implementation-specific value.</summary>
        void TrimExcess()
        {
            this->reserve(this->size());
        }

        /// <summary>Searches the set for a given value and returns the equal value it finds, if any.</summary>
        bool TryGetValue(const T& equalValue, T& actualValue)
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
        virtual void ExceptWith(IEnumerable<T> other) override
        {
            for (T const& item : other)
            {
                this->Remove(item);
            }
        }

        /// <summary>Modifies the current HashSet object to contain only elements
        /// that are present in that object and in the specified collection.</summary>
        virtual void IntersectWith(IEnumerable<T> other) override
        {
            List<T> left = new_List<T>();
            for (T const& item : other)
            {
                if (this->Contains(item))
                    left->Add(item);
            }

            this->Clear();
            for (T const& item : left) this->Add(item);
        }
    };

    template <class T>
    inline HashSet<T> new_HashSet() { return new HashSetImpl<T>(); }

    template <class T>
    inline HashSet<T> new_HashSet(IEnumerable<T> collection) { return new HashSetImpl<T>(collection); }
}
