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

    /// <summary>Represents a collection of keys and values.</summary>
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

        /// <summary>
        /// Initializes a new instance of dictionary.
        ///
        /// This constructor is private. Use make_dictionary() function instead.
        /// </summary>
        dictionary_impl() : base() {}

    public: // PROPERTIES

        /// <summary>Gets the number of key/value pairs contained in the dictionary.</summary>
        int count() { return this->size(); }

        /// <summary>Gets a collection containing the keys in the dictionary.</summary>
        list<key_t> keys()
        {
            list<key_t> list = make_list<key_t>();
            for (auto& x : *this) list->add(x.first);
            return list;
        }

        /// <summary>Gets a collection containing the values in the dictionary.</summary>
        list<value_t> values()
        {
            list<value_t> list = make_list<value_t>();
            for (auto& x : *this) list->add(x.second);
            return list;
        }

    public: // METHODS

        /// <summary>Adds the specified key and value to the dictionary.</summary>
        void add(const key_t& key, const value_t& value)
        {
            this->add(std::pair<key_t, value_t>(key, value));
        }

        /// <summary>Adds the specified value to the ICollection with the specified key.</summary>
        void add(const std::pair<key_t, value_t>& key_value_pair)
        {
            auto res = this->insert(key_value_pair);
            if (!res.second)
                throw exception("An element with the same key already exists in the dictionary");
        }

        /// <summary>Determines whether the dictionary contains the specified key.</summary>
        bool contains_key(const key_t& key)
        {
            return this->find(key) != end();
        }

        /// <summary>Determines whether the dictionary contains a specific value.</summary>
        virtual bool contains_value(const value_t& value)
        {
            for (auto& x : *this)
            {
                if (std::equal_to<value_t>()(x.second, value))
                    return true;
            }
            return false;
        }

        /// <summary>Removes the value with the specified key from the dictionary.</summary>
        bool remove(const key_t& key)
        {
            return this->erase(key) != 0;
        }

        /// <summary>Gets the value associated with the specified key.</summary>
        bool try_get_value(const key_t& key, value_t& value)
        {
            auto iter = this->find(key);
            if (iter != end())
            {
                value = iter->second;
                return true;
            }
            return false;
        }

    public: // OPERATORS

        /// <summary>Gets or sets the value associated with the specified key.</summary>
        value_t& operator[](const key_t& key)
        {
            return base::operator[](key);
        }
    };

    /// <summary>Initializes a new instance of dictionary.</summary>
    template <class key_t, class value_t>
    inline dictionary<key_t, value_t> make_dictionary() { return new dictionary_impl<key_t, value_t>(); }
}
