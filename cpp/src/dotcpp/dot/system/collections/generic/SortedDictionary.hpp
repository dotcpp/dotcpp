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

#include <map>

#include <dot/system/collections/generic/ICollection.hpp>
#include <dot/system/collections/generic/List.hpp>

namespace dot
{
    template <class T> class Array1DImpl; template <class T> using Array1D = ptr<Array1DImpl<T>>;

    ///!!! Provide .NET description Adapter class from STL map to .NET SortedDictionary - collection of key/value pairs that are sorted on the key
    template <class Key, class type_t >
    class SortedDictionary : public detail::std_accessor_<
        dot::IEnumerable< typename KeyValuePair<Key, type_t>::type >
        , std::map<Key, type_t> >
    {
    public:
        typedef detail::std_accessor_<
            dot::IEnumerable< typename KeyValuePair<Key, type_t>::type >
            , std::map<Key, type_t> > base;

        /// <summary>Creates a new empty instance of SortedDictionary.</summary>
        SortedDictionary() : base()
        {}

        /// <summary>Gets number of elements in List.</summary>
        inline int count() const
        {
            return this->get().size();
        }

        /// <summary>Gets List of keys.</summary>
        inline List<Key> keys()
        {
            List<Key> keys;
            std::for_each(this->get().begin(), this->get().end(), [&keys] (std::pair<Key, type_t> const& pair) { keys.add(pair.first); });
            return keys;
        }

        /// <summary>Gets List of values.</summary>
        inline List<type_t> values()
        {
            List<type_t> values;
            std::for_each(this->get().begin(), this->get().end(), [&values] (std::pair<Key, type_t> const& pair) { values.add(pair.second); });
            return values;
        }

        /// <summary>Gets value reference associated with the specified key.</summary>
        inline Type& operator[] (Key key)
        {
            return this->get()[key];
        }

        /// <summary>Gets value reference associated with the specified key.</summary>
        inline type_t const& operator[] (Key key) const
        {
            return this->get()[key];
        }

        /// <summary>Adds the specified key and value to the SortedDictionary.</summary>
        inline void add(Key key, type_t value)
        {
            this->get().insert(std::pair<Key, type_t>(key, value));
        }

        /// <summary>Removes all keys and values from the SortedDictionary
        inline void clear()
        {
            this->get().clear();
        }

        /// <summary>Determines whether the Dictionary contains the specified key.</summary>
        inline bool containsKey(Key key) const
        {
            return this->get().find(key) != this->get().end();
        }

        /// <summary>Determines whether the SortedDictionary contains the specified value.</summary>
        inline bool containsValue(type_t value) const
        {
            for (auto it = this->get().begin(); it < this->get().end(); it++)
            {
                if ((*it).second == value) return true;
            }
            return false;
        }

        /// <summary>Copies SortedDictionary elements to array starting at specified index.</summary>
        inline void copyTo(Array1D<typename KeyValuePair<Key, type_t>::type>& arr, int arrIndex) const
        {
            /*if (arrIndex +  this->get().count() > arr.length())
                throw Exeption();*/
            for (auto it = this->get().begin(), int i = arrIndex; it < this->get().end(); it++, i++)
            {
                arr[i] = *it;
            }
        }

        /// <summary>Removes the value with the specified key from the SortedDictionary.</summary>
        inline bool remove(Key key)
        {
            auto it = this->get().find(key);
            if (it != this->get().end())
            {
                this->get().erase(it);
                return true;
            }
            return false;
        }

        /// <summary>Gets the value associated with the specified key.</summary>
        inline bool tryGetValue(Key key, Type& value)
        {
            auto it = this->get().find(key);
            if (it != this->get().end())
            {
                value = (*it).second;
                return true;
            }
            else
            {
                value = Type();
                return false;
            }
        }
    };
}
