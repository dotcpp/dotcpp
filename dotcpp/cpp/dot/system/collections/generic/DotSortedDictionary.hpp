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

#ifndef __dot_system_collections_generic_SortedDictionary_hpp__
#define __dot_system_collections_generic_SortedDictionary_hpp__

#include <map>

#include <dot/system/collections/generic/IDotCollection.hpp>
#include <dot/system/collections/generic/IDotEnumerable.hpp>
#include <dot/system/collections/generic/IDotEnumerator.hpp>

namespace dot
{
	
	/// Adapter class from STL map to .NET SortedDictionary - collection of key/value pairs that are sorted on the key
	template <typename Key, typename Type >
	class SortedDictionary : public detail::std_accessor_<
		dot::IDotEnumerable< typename KeyValuePair<Key, Type>::type >
		, std::map<Key, Type> >
	{
	public:
		typedef detail::std_accessor_<
			dot::IDotEnumerable< typename KeyValuePair<Key, Type>::type >
			, std::map<Key, Type> > base;

		
		/// SortedDictionary constructor that create new empty instance of SortedDictionary
		SortedDictionary() : base()
		{   }

		
		/// Gets number of elements in List
		/// <returns>
		/// Number of elements in List
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
		/// <param name="key">key of the valu</param>
		/// <returns>
		///     reference associated with the specified key
		/// </returns>
		inline Type& operator[] (Key key);

		
		///     Adds the specified key and value to the SortedDictionary
		/// <param name="key">the key of the element to ad</param>
		/// <param name="value">the value of the element to ad</param>
		inline void Add(Key key, Type value);

		
		///     Removes all keys and values from the SortedDictionary
		inline void Clear();

		
		///     Determines whether the Dictionary contains the specified key.
		/// <param name="key">the key to search in the SortedDictionar</param>
		/// <returns>
		///     true if the SortedDictionary contains an element with the specified key; otherwise, false.
		/// </returns>
		inline bool ContainsKey(Key key);

		
		///     Determines whether the SortedDictionary contains the specified value.
		/// <param name="value">the value to search in the Dictionar</param>
		/// <returns>
		///     true if the SortedDictionary contains an element with the specified value; otherwise, false.
		/// </returns>
		inline bool ContainsValue(Type value);
		
		
		/// Copies SortedDictionary elements to array starting at specified index
		/// <param name="array">target arra</param>
		/// <param name="arrayIndex">index in array at which copying begin</param>
		inline void CopyTo(typename KeyValuePair<Key, Type>::type *& array, int arrayIndex);
			
		
		///     Removes the value with the specified key from the SortedDictionary
		/// <param name="key">the key of the element to remov</param>
		/// <returns>
		///     true if the element is successfully found and removed; otherwise, false.
		/// </returns>
		inline bool Remove(Key key);

		
		///     Gets the value associated with the specified key.
		/// <param name="key">the key of the value to ge</param>.
		/// <param name="value">when this method return</param>, contains the value associated with the specified key, if the key is found; otherwise, the default value 
		/// <returns>
		///     true if the SortedDictionary contains an element with the specified key; otherwise, false.
		/// </returns>
		inline bool TryGetValue(Key key, Type& value);
	};


}

#endif