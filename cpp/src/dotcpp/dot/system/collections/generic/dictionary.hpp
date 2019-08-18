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

#include <unordered_map>
#include <dot/system/exception.hpp>
#include <dot/system/collections/generic/list.hpp>

namespace dot
{
    template <class key_t, class value_t> class dictionary_impl;
    template <class key_t, class value_t> using dictionary = ptr<dictionary_impl<key_t, value_t>>;

    /// Represents a collection of keys and values.
    template <class key_t, class value_t>
    class dictionary_impl
        : public virtual object_impl
        , public std::unordered_map<key_t, value_t>
    {
        typedef dictionary_impl<key_t, value_t> self;
        typedef std::unordered_map<key_t, value_t> base;

        template <class key_t_, class value_t_>
        friend dictionary<key_t_, value_t_> make_dictionary();

    private: // CONSTRUCTORS

        /// Initializes a new instance of dictionary.
        ///
        /// This constructor is private. Use make_dictionary() function instead.
        dictionary_impl() : base() {}

    public: // PROPERTIES

        /// Gets the number of key/value pairs contained in the dictionary.
        int count() { return this->size(); }

        /// Gets a collection containing the keys in the dictionary.
        list<key_t> keys()
        {
            list<key_t> list = make_list<key_t>();
            for (auto& x : *this) list->add(x.first);
            return list;
        }

        /// Gets a collection containing the values in the dictionary.
        list<value_t> values()
        {
            list<value_t> list = make_list<value_t>();
            for (auto& x : *this) list->add(x.second);
            return list;
        }

    public: // METHODS

        /// Adds the specified key and value to the dictionary.
        void add(const key_t& key, const value_t& value)
        {
            this->add(std::pair<key_t, value_t>(key, value));
        }

        /// Adds the specified value to the ICollection with the specified key.
        void add(const std::pair<key_t, value_t>& key_value_pair)
        {
            auto res = this->insert(key_value_pair);
            if (!res.second)
                throw exception("An element with the same key already exists in the dictionary");
        }

        /// Determines whether the dictionary contains the specified key.
        bool contains_key(const key_t& key)
        {
            return this->find(key) != this->end();
        }

        /// Determines whether the dictionary contains a specific value.
        virtual bool contains_value(const value_t& value)
        {
            for (auto& x : *this)
            {
                if (std::equal_to<value_t>()(x.second, value))
                    return true;
            }
            return false;
        }

        /// Removes the value with the specified key from the dictionary.
        bool remove(const key_t& key)
        {
            return this->erase(key) != 0;
        }

        /// Gets the value associated with the specified key.
        bool try_get_value(const key_t& key, value_t& value)
        {
            auto iter = this->find(key);
            if (iter != this->end())
            {
                value = iter->second;
                return true;
            }
            return false;
        }

    public: // OPERATORS

        /// Gets or sets the value associated with the specified key.
        value_t& operator[](const key_t& key)
        {
            return base::operator[](key);
        }
    };

    /// Initializes a new instance of dictionary.
    template <class key_t, class value_t>
    inline dictionary<key_t, value_t> make_dictionary() { return new dictionary_impl<key_t, value_t>(); }
}
