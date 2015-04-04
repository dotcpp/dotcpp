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

#ifndef __dot_system_collections_generic_HashSet_hpp__
#define __dot_system_collections_generic_HashSet_hpp__

#include <deque>

#include <dot/system/collections/generic/IDotCollection.hpp>
#include <dot/system/collections/generic/IDotEnumerable.hpp>
#include <dot/system/collections/generic/IDotEnumerator.hpp>

namespace dot
{
	template <typename T>
	class HashSet : public detail::std_accessor_<dot::IDotEnumerable<T>
		, std::deque<T> >
	{
	public:
		typedef detail::std_accessor_<dot::IDotEnumerable<T>
			, std::deque<T> > base;

		typedef dot::IDotEnumerable<T> dot_enumerator_type;

		typedef std::deque<T> std_base;

		typedef T& reference_type;
	public:

		HashSet() : base()
		{   }

		inline int get_Count() const
		{
			return this->get().size();
		}

		inline bool Add(T item);

		inline void Clear();

		inline bool Contains(T item);

		template <int I>
		void CopyTo(T(&a)[I]);
		void CopyTo(T*& array, int arrayIndex);


		void CopyTo(int index, T*& array, int arrayIndex, int count);

		inline void ExceptWith(IDotEnumerable<T> &other);

		inline void IntersectWith(IDotEnumerable<T> &other);

		inline bool IsProperSubsetOf(IDotEnumerable<T> &other);
		
		inline bool IsProperSupersetOf(IDotEnumerable<T> &other);
		
		inline bool IsSubsetOf(IDotEnumerable<T> &other);
		
		inline bool IsSupersetOf(IDotEnumerable<T> &other);

		inline bool Overlaps(IDotEnumerable<T> &other);
		
		inline bool Remove(T item);
		
		template <typename Predicate>
		inline int RemoveWhere(Predicate match);
		
		inline bool SetEquals(IDotEnumerable<T> &other);
		
		inline void SymmetricExceptWith(IDotEnumerable<T> &other);
		
		inline void TrimExcess();
		
		inline void UnionWith(IDotEnumerable<T> &other);
	};


}

#endif