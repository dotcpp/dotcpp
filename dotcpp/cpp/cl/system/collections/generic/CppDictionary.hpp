/*
Copyright (C) 2003-2015 CompatibL

This file is part of .C++, an open source implementation of TapeScript
in native C++ using .NET class library conventions, available from

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

#ifndef __cl_system_collections_generic_CppDictionary_hpp__
#define __cl_system_collections_generic_CppDictionary_hpp__

#include <hash_map>

#include <cl/system/collections/generic/ICppCollection.hpp>
#include <cl/system/collections/generic/ICppEnumerable.hpp>
#include <cl/system/collections/generic/ICppEnumerator.hpp>

namespace cl
{
    ///!!! Provide .NET description Adapter class from STL hash_map to .NET Dictionary - collection of keys and values
    template <typename Key, typename Type >
    class Dictionary : public detail::std_accessor_<
        cl::ICppEnumerable<typename KeyValuePair<Key, Type>::type>, stdext::hash_map<Key, Type> >
    {
    public:

        typedef detail::std_accessor_<
            cl::ICppEnumerable< typename KeyValuePair<Key, Type>::type >, stdext::hash_map<Key, Type> >
            base;

        /// <summary>Initializes a new instance of CppDictionary.</summary>
        Dictionary() : base()
        {
        }

        /// <summary>Gets number of elements in Dictionary.</summary>
        inline int getCount() const
        {
            return this->get().size();
        }

        /// <summary>Gets List of keys.</summary>
        inline List<Key> getKeys() const;

        /// <summary>Gets List of values.</summary>
        inline List<Type> getValues() const;

        /// <summary>Gets value reference associated with the specified key.</summary>
        inline Type& operator[] (Key key);

        /// <summary>Adds the specified key and value to the Dictionary.</summary>
        inline void add(Key key, Type value);

        /// <summary>Removes all keys and values from the Dictionary.</summary>
        inline void clear();

        /// <summary>Determines whether the Dictionary contains the specified key.</summary>
        inline bool containsKey(Key key) const;

        /// <summary>Determines whether the Dictionary contains the specified value.</summary>
        inline bool containsValue(const Type& value) const;

        /// <summary>Removes the value with the specified key from the Dictionary.</summary>
        inline bool remove(Key key);

        /// <summary>Gets the value associated with the specified key.</summary>
        inline bool TryGetValue(Key key, Type& value);
    };
}

#endif // __cl_system_collections_generic_CppDictionary_hpp__