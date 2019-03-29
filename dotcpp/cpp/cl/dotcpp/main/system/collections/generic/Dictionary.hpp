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

#include <unordered_map>
#include <cl/dotcpp/main/system/collections/generic/ICollection.hpp>
#include <cl/dotcpp/main/system/collections/generic/IEnumerable.hpp>
#include <cl/dotcpp/main/system/collections/generic/IEnumerator.hpp>
#include <cl/dotcpp/main/system/collections/generic/List.hpp>

namespace cl
{
    /// <summary>Represents a collection of keys and values.</summary>
    template <class Key, class Type >
    class Dictionary : public std::unordered_map<Key, Type>
    {
        typedef std::unordered_map<Key, Type> base;

    public: // CONSTRUCTORS

        /// <summary>Initializes a new instance of Dictionary.</summary>
        Dictionary() : base() {}

        /// <summary>Gets number of elements in dictionary.</summary>
        int Count() const { return this->size(); }

        /// <summary>Gets List of keys.</summary>
        inline List<Key> keys()
        {
            List<Key> keys;
            std::for_each(this->get().begin(), this->get().end(), [&keys](std::pair<Key, Type> const& value){ keys.add(value.first); });
            return keys;
        }

        /// <summary>Gets List of values.</summary>
        inline List<Type> values()
        {
            List<Type> values;
            std::for_each(this->get().begin(), this->get().end(), [&values](std::pair<Key, Type> const& value){ values.add(value.second); });
            return values;
        }

        /// <summary>Gets value reference associated with the specified key.</summary>
        inline Type& operator[] (Key const& key)
        {
            return this->get()[key];
        }

        /// <summary>Adds the specified key and value to the Dictionary.</summary>
        inline void add(Key const& key, Type const& value)
        {
            this->get().insert(std::pair<Key, Type>(key, value));
        }

        /// <summary>Removes all keys and values from the Dictionary.</summary>
        inline void clear()
        {
            this->get().clear();
        }

        /// <summary>Determines whether the Dictionary contains the specified key.</summary>
        inline bool containsKey(Key const& key) const
        {
            return (this->get().find(key) != this->get().end());
        }

        /// <summary>Determines whether the Dictionary contains the specified value.</summary>
        inline bool containsValue(const Type& value) const
        {
            for (typename base::iterator iter = this->get().begin(); iter != this->get().end(); iter++)
            {
                if (iter->second == value)
                {
                    return true;
                }
            }
            return false;
        }

        /// <summary>Removes the value with the specified key from the Dictionary.</summary>
        inline bool remove(Key const& key)
        {
            this->get().erase(key);
        }

        /// <summary>Gets the value associated with the specified key.</summary>
        inline bool tryGetValue(Key const& key, Type& value)
        {
            typename base::iterator iter = this->get().find(key);
            if (iter != this->get().end())
            {
                value = iter->second;
                return true;
            }
            return false;
        }
    };
}
