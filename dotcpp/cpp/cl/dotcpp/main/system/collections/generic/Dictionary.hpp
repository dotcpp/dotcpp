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
#include <cl/dotcpp/main/system/collections/generic/IDictionary.hpp>
#include <cl/dotcpp/main/system/collections/generic/List.hpp>

namespace cl
{
    template <class TKey, class TValue> class DictionaryImpl;
    template <class TKey, class TValue> using Dictionary = Ptr<DictionaryImpl<TKey, TValue>>;

    /// <summary>Represents a collection of keys and values.</summary>
    template <class TKey, class TValue>
    class DictionaryImpl
        : public IDictionary<TKey, TValue>
        , public virtual ObjectImpl
        , public std::unordered_map<TKey, TValue>
    {
        typedef std::unordered_map<TKey, TValue> base;

        template <class TKey, class TValue>
        friend Dictionary<TKey, TValue> new_Dictionary();

    private: // CONSTRUCTORS

        /// <summary>
        /// Initializes a new instance of Dictionary.
        ///
        /// This constructor is private. Use new_Dictionary() function instead.
        /// </summary>
        DictionaryImpl() : base() {}

    public: // METHODS

        /// <summary>Gets number of elements in dictionary.</summary>
        int Count() const { return this->size(); }

        /// <summary>Gets List of keys.</summary>
        inline List<TKey> keys()
        {
            List<TKey> keys;
            std::for_each(this->get().begin(), this->get().end(), [&keys](std::pair<TKey, TValue> const& value){ keys.add(value.first); });
            return keys;
        }

        /// <summary>Gets List of values.</summary>
        inline List<TValue> values()
        {
            List<TValue> values;
            std::for_each(this->get().begin(), this->get().end(), [&values](std::pair<TKey, TValue> const& value){ values.add(value.second); });
            return values;
        }

        /// <summary>Gets value reference associated with the specified key.</summary>
        inline TValue& operator[] (TKey const& key)
        {
            return this->get()[key];
        }

        /// <summary>Adds the specified key and value to the Dictionary.</summary>
        inline void add(TKey const& key, TValue const& value)
        {
            this->get().insert(std::pair<TKey, TValue>(key, value));
        }

        /// <summary>Removes all keys and values from the Dictionary.</summary>
        inline void clear()
        {
            this->get().clear();
        }

        /// <summary>Determines whether the Dictionary contains the specified key.</summary>
        inline bool containsKey(TKey const& key) const
        {
            return (this->get().find(key) != this->get().end());
        }

        /// <summary>Determines whether the Dictionary contains the specified value.</summary>
        inline bool containsValue(const TValue& value) const
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
        inline bool remove(TKey const& key)
        {
            this->get().erase(key);
        }

        /// <summary>Gets the value associated with the specified key.</summary>
        inline bool tryGetValue(TKey const& key, TValue& value)
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

    /// <summary>Initializes a new instance of Dictionary.</summary>
    template <class TKey, class TValue>
    Dictionary<TKey, TValue> new_Dictionary() { return new DictionaryImpl<TKey, TValue>(); }
}
