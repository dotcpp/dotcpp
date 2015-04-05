/*
Copyright (C) 2003-2015 CompatibL

This file is part of .C++ project, an open source implementation of
selected .NET class library APIs in native C++ with optional support
for adjoint algorithmic differentiation (AAD), available from

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

#ifndef __cl_system_collections_generic_SortedDictionary_hpp__
#define __cl_system_collections_generic_SortedDictionary_hpp__

#include <map>

#include <cl/system/collections/generic/ICppCollection.hpp>
#include <cl/system/collections/generic/ICppEnumerable.hpp>
#include <cl/system/collections/generic/ICppEnumerator.hpp>

namespace cl
{
    template <class T> class CppArray;

    ///!!! Provide .NET description Adapter class from STL map to .NET SortedDictionary - collection of key/value pairs that are sorted on the key
    template <typename Key, typename Type >
    class CppSortedDictionary : public detail::std_accessor_<
        cl::ICppEnumerable< typename KeyValuePair<Key, Type>::type >
        , std::map<Key, Type> >
    {
    public:
        typedef detail::std_accessor_<
            cl::ICppEnumerable< typename KeyValuePair<Key, Type>::type >
            , std::map<Key, Type> > base;

        /// <summary>Creates a new empty instance of SortedDictionary.</summary>
        CppSortedDictionary() : base()
        {}

        /// <summary>Gets number of elements in CppList.</summary>
        inline int getCount() const
        {
            return this->get().size();
        }

        /// <summary>Gets List of keys.</summary>
        inline List<Key> getKeys();

        /// <summary>Gets List of values.</summary>
        inline List<Type> getValues();

        /// <summary>Gets value reference associated with the specified key.</summary>
        inline Type& operator[] (Key key);

        /// <summary>Adds the specified key and value to the SortedDictionary.</summary>
        inline void add(Key key, Type value);

        /// <summary>Removes all keys and values from the SortedDictionary
        inline void clear();

        /// <summary>Determines whether the Dictionary contains the specified key.</summary>
        inline bool containsKey(Key key);

        /// <summary>Determines whether the SortedDictionary contains the specified value.</summary>
        inline bool containsValue(Type value);

        /// <summary>Copies SortedDictionary elements to array starting at specified index.</summary>
        inline void copyTo(Array<typename KeyValuePair<Key, Type>::type>& arr, int arrIndex) const;

        /// <summary>Removes the value with the specified key from the SortedDictionary.</summary>
        inline bool remove(Key key);

        /// <summary>Gets the value associated with the specified key.</summary>
        inline bool tryGetValue(Key key, Type& value) const;
    };
}

#endif