/*
Copyright (C) 2003-2015 CompatibL

This file is part of DotCpp project, an implementation of
selected .NET class libraries in native C++ available from

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

#ifndef __dot_system_collections_generic_Dictionary_hpp__
#define __dot_system_collections_generic_Dictionary_hpp__

#include <hash_map>

#include <dot/system/collections/generic/IDotCollection.hpp>
#include <dot/system/collections/generic/IDotEnumerable.hpp>
#include <dot/system/collections/generic/IDotEnumerator.hpp>

namespace dot
{
	
	
	/// Adapter class from STL hash_map to .NET Dictionary - collection of keys and values
	template <typename Key, typename Type >
	class Dictionary : public detail::std_accessor_<
                                dot::IDotEnumerable< typename KeyValuePair<Key, Type>::type >
                                , stdext::hash_map<Key, Type> >
	{
    public:

        typedef detail::std_accessor_<
            dot::IDotEnumerable< typename KeyValuePair<Key, Type>::type >
			, stdext::hash_map<Key, Type> > base;

		
		///     Initializes a new instance of the Dictionary
		Dictionary() : base()
		{   }

		
		/// Gets number of elements in Dictionary
		/// <returns>
		/// Number of elements in Dictionary
		/// </returns>
		inline int get_Count() const
		{
			return this->get().size();
		}

		 
		/// Gets List of keys
		/// <returns>
		/// List of keys
		/// </returns>
		inline List<Key> get_Keys();

		
		/// Gets List of values
		/// <returns>
		/// List of values
		/// </returns>
		inline List<Type> get_Values();


		
		///     Gets value reference associated with the specified key
		/// <param name="key">
		///   The key of the value
		/// </param>
		/// <returns>
		///     Reference associated with the specified key
		/// </returns>
		inline Type& operator[] (Key key);

		
		///     Adds the specified key and value to the Dictionary
		/// <param name="key">
		///   The key of the element to add
		/// </param>
		/// <param name="value">
		///   The value of the element to add
		/// </param>
		inline void Add(Key key, Type value);

		/// 
		///     Removes all keys and values from the Dictionary
		
		inline void Clear();

		
		///     Determines whether the Dictionary contains the specified key.
		/// <param name="key">
		///   The key of the element to search
		/// </param>
		/// <returns>
		///     true if the Dictionary contains an element with the specified key; otherwise, false.
		/// </returns>
		inline bool ContainsKey(Key key);

		
		///     Determines whether the Dictionary contains the specified value.
		/// <param name="value">
		///   The value of the element to search
		/// </param>
		/// <returns>
		///     true if the Dictionary contains an element with the specified value; otherwise, false.
		/// </returns>
		inline bool ContainsValue(Type value);

		
		///     Removes the value with the specified key from the Dictionary
		/// <param name="key">
		///   The key of the element to remove
		/// </param>
		/// <returns>
		///     true if the element is successfully found and removed; otherwise, false.
		/// </returns>
		inline bool Remove(Key key);

		///     Gets the value associated with the specified key.
		/// <param name="key">
		///   The key of the element to get
		/// </param>
		/// <param name="value">
		///   When this method returns, contains the value associated with the specified key, if the key is found; otherwise, the default value 
		/// </param>
		/// <returns>
		///     true if the Dictionary contains an element with the specified key; otherwise, false.
		/// </returns>
		inline bool TryGetValue(Key key, Type& value);
	};


}

#endif