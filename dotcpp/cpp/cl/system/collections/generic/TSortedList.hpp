/*
Copyright (C) 2003-2015 CompatibL

This file is part of .C++, a native C++ implementation of
selected .NET class library APIs with built-in support for
algorithmic differentiation (AD), available from

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

#ifndef __cl_system_collections_generic_TSortedList_hpp__
#define __cl_system_collections_generic_TSortedList_hpp__

#include <cl/system/collections/generic/TList.hpp>
#include <deque>
#include <hash_map>

#include <cl/system/collections/generic/ITCollection.hpp>
#include <cl/system/collections/generic/ITEnumerable.hpp>
#include <cl/system/collections/generic/ITEnumerator.hpp>

namespace cl
{
    template <class T> class Array;

    ///!!! Provide .NET description Adapter class from STL deque to .NET SortedList - collection of key/value pairs that are sorted on the key
    template <typename Key, typename Type >
    class TSortedList : public detail::std_accessor_<
        cl::ITEnumerable< typename TKeyValuePair<Key, Type>::type >
        , std::deque< typename TKeyValuePair<Key, Type>::type > >
    {
    public:

        //!!!! Why in public section?
        typedef detail::std_accessor_<
            cl::ITEnumerable< typename TKeyValuePair<Key, Type>::type >
            , std::deque< typename TKeyValuePair<Key, Type>::type > > base;

        /// <summary>SortedList constructor that create new empty instance of SortedList.</summary>
        TSortedList() : base()
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

#endif // __cl_system_collections_generic_TSortedList_hpp__