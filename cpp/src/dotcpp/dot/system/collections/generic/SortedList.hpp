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

#include <dot/system/collections/generic/List.hpp>
#include <deque>

#include <dot/system/collections/generic/ICollection.hpp>
#include <dot/system/collections/generic/IEnumerable.hpp>
#include <dot/system/collections/generic/IEnumerator.hpp>

namespace dot
{
    template <class T> class Array1DImpl; template <class T> using Array1D = Ptr<Array1DImpl<T>>;

    ///!!! Provide .NET description Adapter class from STL deque to .NET SortedList - collection of key/value pairs that are sorted on the key
    template <class Key, class Type >
    class SortedList : public detail::std_accessor_<
        dot::IEnumerable< typename KeyValuePair<Key, Type>::type >
        , std::deque< typename KeyValuePair<Key, Type>::type > >
    {
    public:

        //!!!! Why in public section?
        typedef detail::std_accessor_<
            dot::IEnumerable< typename KeyValuePair<Key, Type>::type >
            , std::deque< typename KeyValuePair<Key, Type>::type > > base;

        /// <summary>SortedList constructor that create new empty instance of SortedList.</summary>
        SortedList() : base()
        {
        }

        //!!!! Why public?
        int capacity;

        /// <summary>Gets number of elements in SortedList.</summary>
        inline int getCount() const;

        /// <summary>Gets List of keys.</summary>
        inline List<Key> getKeys() const;

        /// <summary>Gets List of values.</summary>
        inline List<Type> getValues() const;

        /// <summary>Gets value reference associated with the specified key.</summary>
        inline Type& operator[] (Key key);

        /// <summary>Adds the specified key and value to the SortedList.</summary>
        inline void add(Key key, Type value);

        /// <summary>Removes all keys and values from the SortedList.</summary>
        inline void clear();

        /// <summary>Determines whether the SortedList contains the specified key.</summary>
        inline bool containsKey(Key key) const;

        /// <summary>Determines whether the SortedList contains the specified value.</summary>
        inline bool containsValue(Type value) const;

        /// <summary>Searches for the specified key and returns index within the entire SortedList.</summary>
        inline int indexOfKey(Key key) const;

        /// <summary>Searches for the specified value and returns index within the entire SortedList.</summary>
        inline int indexOfValue(Type value) const;

        /// <summary>Removes the value with the specified key from the SortedList.</summary>
        inline bool remove(Key key);

        /// <summary>Removes the element at the specified index from the SortedList.</summary>
        inline void removeAt(int index);

        /// <summary>Sets the capacity to the actual number of elements in the List, if that number is less than a threshold value.</summary>
        inline void trimExcess();

        /// <summary>Gets the value associated with the specified key.</summary>
        inline bool tryGetValue(Key key, Type& value);
    };
}
