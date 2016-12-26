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

#ifndef __cl_system_collections_generic_CppDictionary_hpp__
#define __cl_system_collections_generic_CppDictionary_hpp__

#include <hash_map>

#include <cl/system/collections/generic/ICppCollection.hpp>
#include <cl/system/collections/generic/ICppEnumerable.hpp>
#include <cl/system/collections/generic/ICppEnumerator.hpp>
#include <cl/system/collections/generic/CppList.hpp>

namespace cl
{
    template<typename Key, typename Type>
    using map_type = stdext::hash_map<Key, Type>;

    ///!!! Provide .NET description Adapter class from STL hash_map to .NET CppDictionary - collection of keys and values
    template <typename Key, typename Type >
    class CppDictionary : public detail::std_accessor_<
        cl::ICppEnumerable<typename CppKeyValuePair<Key, Type>::type>, map_type<Key, Type> >
    {
    public:

        // Iterator type
        typedef typename
            map_type<Key, Type>::iterator iterator;

        // Const iterator
        typedef typename
            map_type<Key, Type>::const_iterator const_iterator;

        typedef detail::std_accessor_<
            cl::ICppEnumerable< 
                typename CppKeyValuePair<Key, Type>::type 
            >, map_type<Key, Type> > base;

        /// <summary>Initializes a new instance of CppDictionary.</summary>
        CppDictionary() : base()
        {
        }
        
        /// <summary>Gets number of elements in CppDictionary.</summary>
        inline int count() const
        {
            return this->get().size();
        }

        /// <summary>Gets CppList of keys.</summary>
        inline CppList<Key> keys() 
        {
            CppList<Key> keys;
            std::for_each(this->get().begin(), this->get().end(), [&keys](std::pair<Key, Type> const& value){ keys.add(value.first); });
            return keys;
        }

        /// <summary>Gets CppList of values.</summary>
        inline CppList<Type> values()
        {
            CppList<Type> values;
            std::for_each(this->get().begin(), this->get().end(), [&values](std::pair<Key, Type> const& value){ values.add(value.second); });
            return values;
        }

        /// <summary>Gets value reference associated with the specified key.</summary>
        inline Type& operator[] (Key const& key)
        {
            return this->get()[key];
        }

        /// <summary>Adds the specified key and value to the CppDictionary.</summary>
        inline void add(Key const& key, Type const& value)
        {
            this->get().insert(std::pair<Key, Type>(key, value));
        }

        /// <summary>Removes all keys and values from the CppDictionary.</summary>
        inline void clear()
        {
            this->get().clear();
        }

        /// <summary>Determines whether the CppDictionary contains the specified key.</summary>
        inline bool containsKey(Key const& key) const
        {
            return (this->get().find(key) != this->get().end());
        }

        /// <summary>Determines whether the CppDictionary contains the specified value.</summary>
        inline bool containsValue(const Type& value) const
        {
            for (map_type<Key, Type>::iterator iter = this->get().begin(); iter != this->get().end(); iter++)
            {
                if (iter->second == value)
                {
                    return true;
                }
            }
            return false;
        }

        /// <summary>Removes the value with the specified key from the CppDictionary.</summary>
        inline bool remove(Key const& key)
        {
            this->get().erase(key);
        }

        /// <summary>Gets the value associated with the specified key.</summary>
        inline bool tryGetValue(Key const& key, Type& value) 
        {
            iterator iter = this->get().find(key);
            if (iter != this->get().end())
            {
                value = iter->second;
                return true;
            }
            return false;
        }
    };
}

#endif // __cl_system_collections_generic_CppDictionary_hpp__