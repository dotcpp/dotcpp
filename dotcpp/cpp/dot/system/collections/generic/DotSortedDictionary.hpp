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
	template <typename Key, typename Type >
	class SortedDictionary : public detail::std_accessor_<
		dot::IDotEnumerable< typename KeyValuePair<Key, Type>::type >
		, std::map<Key, Type> >
	{
	public:

		typedef detail::std_accessor_<
			dot::IDotEnumerable< typename KeyValuePair<Key, Type>::type >
			, std::map<Key, Type> > base;

		SortedDictionary() : base()
		{   }

		inline int get_Count() const
		{
			return this->get().size();
		}

		inline List<Key> get_Keys();
		inline List<Type> get_Values();



		inline Type& operator[] (Key key);

		inline void Add(Key key, Type value);

		inline void Clear();

		inline bool ContainsKey(Key key);

		inline bool ContainsValue(Type value);
		
		inline void CopyTo(typename KeyValuePair<Key, Type>::type *& array, int arrayIndex);
			
		inline bool Remove(Key key);

		inline bool TryGetValue(Key key, Type& value);
	};


}

#endif