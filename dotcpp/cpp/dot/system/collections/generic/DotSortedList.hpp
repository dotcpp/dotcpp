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

#ifndef __dot_system_collections_generic_SortedList_hpp__
#define __dot_system_collections_generic_SortedList_hpp__

#include <deque>
#include "DotList.hpp"
#include <hash_map>

#include <dot/system/collections/generic/IDotCollection.hpp>
#include <dot/system/collections/generic/IDotEnumerable.hpp>
#include <dot/system/collections/generic/IDotEnumerator.hpp>

namespace dot
{
	
	
	/// Adapter class from STL deque
	/// to .NET SortedList - collection of key/value pairs that are sorted on the key
	template <typename Key, typename Type >
	class SortedList : public detail::std_accessor_<
		dot::IDotEnumerable< typename KeyValuePair<Key, Type>::type >
		, std::deque< typename KeyValuePair<Key, Type>::type > >
	{
	public:

		typedef detail::std_accessor_<
			dot::IDotEnumerable< typename KeyValuePair<Key, Type>::type >
			, std::deque< typename KeyValuePair<Key, Type>::type > > base;

		
		/// SortedList constructor that create new empty instance of SortedList 
		SortedList() : base()
		{   }


		int Capacity;

		
		/// Gets number of elements in SortedList
		/// <returns>
		/// Number of elements in SortedList
		/// </returns>
		inline int get_Count() const;

		
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
		///   key of the value
		/// </param>
		/// <returns>
		///     reference associated with the specified key
		inline Type& operator[] (Key key);

		
		///     Adds the specified key and value to the SortedList
		/// <param name="key">the key of the element to add</param>
		/// </param>
		/// <param name="value">the value of the element to add</param>
		/// </param>
		inline void Add(Key key, Type value);

		
		///     Removes all keys and values from the SortedList
		inline void Clear();

		
		///     Determines whether the SortedList contains the specified key.
		/// <param name="key">the key to search in the SortedList</param>
		/// <returns>
		///     true if the SortedList contains an element with the specified key; otherwise, false.
		/// </returns>
		inline bool ContainsKey(Key key);

		
		///     Determines whether the SortedList contains the specified value.
		/// <param name="value">the value to search in the SortedList</param>
		/// <returns>
		///     true if the SortedList contains an element with the specified value; otherwise, false.
		/// </returns>
		inline bool ContainsValue(Type value);
		
		
		///     Searches for the specified key and returns index within the entire SortedList
		/// <param name="key">the key to search</param>
		/// <returns>
		///     Index of key within the entire SortedList found; otherwise, -1.
		/// </returns>
		inline int IndexOfKey(Key key);
		
		
		///     Searches for the specified value and returns index within the entire SortedList
		/// <param name="value">the value to search</param>
		/// <returns>
		///     Index of value within the entire SortedList found; otherwise, -1.
		/// </returns>
		inline int IndexOfValue(Type value);

		
		///     Removes the value with the specified key from the SortedList
		/// <param name="key">the key of the element to remove</param>
		/// <returns>
		///     true if the element is successfully found and removed; otherwise, false.
		/// </returns>
		inline bool Remove(Key key);

		
		///     Removes the element at the specified index from the SortedList
		/// <param name="index">the index of the element to remove</param>
		inline void RemoveAt(int index);
		
		
		///     Sets the capacity to the actual number of elements in the List, if that number is less than a threshold value.
		inline void TrimExcess();

		
		///     Gets the value associated with the specified key.
		/// <param name="key">the key of the value to get</param>
		/// <param name="value">when this method returns</param> contains the value associated with the specified key, if the key is found; otherwise, the default value 
		/// <returns>
		///     true if the Dictionary contains an element with the specified key; otherwise, false.
		/// </returns>
		inline bool TryGetValue(Key key, Type& value);
	};


}

#endif