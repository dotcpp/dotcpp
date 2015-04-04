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

#include <hash_set>

#include <dot/system/collections/generic/IDotCollection.hpp>
#include <dot/system/collections/generic/IDotEnumerable.hpp>
#include <dot/system/collections/generic/IDotEnumerator.hpp>

namespace dot
{
	
	/// Adapter class from STL has_set to .NET HashSet
	template <typename T>
	class HashSet : public detail::std_accessor_<dot::IDotEnumerable<T>
		, stdext::hash_set<T> >
	{
	public:
		typedef detail::std_accessor_<dot::IDotEnumerable<T>
			, std::hash_set<T> > base;

		typedef dot::IDotEnumerable<T> dot_enumerator_type;

		typedef std::hash_set<T> std_base;

		typedef T& reference_type;
	public:
		
		
		///     Initializes a new instance of the HashSet
		HashSet() : base()
		{   }

		
		/// Gets number of elements in HashSet
		/// <returns>
		/// Number of elements in HashSet
		/// </returns>
		inline int get_Count() const
		{
			return this->get().size();
		}

		
		///   Adds the specified element to the HashSet
		/// <param name="item">
		///   The element to add to the set.
		/// </param>
		inline bool Add(T item);

		
		///     Removes all keys and values from the HashSet
		inline void Clear();

		
		/// Searches element in HashSet
		/// <param name="item">
		///   The element to search.
		/// </param>
		/// <returns>
		/// true if the item is found, or false, otherwise
		/// </returns>
		inline bool Contains(T item);

		
		/// Copies HashSet elements to array starting at then begining of arrray
		/// <param name="array">
		/// Target array
		/// </param>
		void CopyTo(T*& array);

		
		/// Copies HashSet elements to array starting at specified index
		/// <param name="array">
		/// Target array
		/// </param>
		/// <param name="arrayIndex">
		/// Index in array at which copying begins
		/// </param>
		void CopyTo(T*& array, int arrayIndex);

		
		/// Copies range of HashSet elements to array starting at specified index
		/// <param name="array">
		/// Target array
		/// </param>
		/// <param name="arrayIndex">
		/// Index in array at which copying begins
		/// </param>
		/// <param name="count">
		/// Number of elements to copy
		/// </param>
		void CopyTo(T*& array, int arrayIndex, int count);

		
		///     Removes all elements in the specified collection from the current HashSet object.
		/// <param name="other">
		///   The collection of items to remove from the HashSet object.
		/// </param>
		inline void ExceptWith(IDotEnumerable<T> &other);

		
		///     Modifies the current HashSet to contain only elements that are present in that object and in the specified collection
		/// <param name="other">
		///   The collection to compare to the current HashSet
		/// </param>
		inline void IntersectWith(IDotEnumerable<T> &other);

		
		///     Determines whether a HashSet object is a proper subset of the specified collection.
		/// <param name="other">
		///   The collection to compare to the current HashSet
		/// </param>
		/// <returns>
		///     true if the HashSet object is a proper subset of other; otherwise, false.
		/// </returns>
		inline bool IsProperSubsetOf(IDotEnumerable<T> &other);
		
		
		///     Determines whether a HashSet is a proper superset of the specified collection.
		/// <param name="other">
		///   The collection to compare to the current HashSet
		/// </param>
		/// <returns>
		///     true if the HashSet is a proper superset other; otherwise, false.
		/// </returns>
		inline bool IsProperSupersetOf(IDotEnumerable<T> &other);
		
		
		///     Determines whether a HashSet is a subset of the specified collection
		/// <param name="other">
		///   The collection to compare to the current HashSet
		/// </param>
		/// <returns>
		///     true if the HashSet is a subset of other; otherwise, false
		/// </returns>
		inline bool IsSubsetOf(IDotEnumerable<T> &other);
		
		
		///     Determines whether a HashSet is a superset of the specified collection.
		/// <param name="other">
		///   The collection to compare to the current HashSet
		/// </param>
		/// <returns>
		///     true if the HashSet is a superset of other; otherwise, false.
		/// </returns>
		inline bool IsSupersetOf(IDotEnumerable<T> &other);

		
		///     Determines whether the current HashSet and a specified collection share common elements.
		/// <param name="other">
		///   The collection to compare to the current HashSet
		/// </param>
		/// <returns>
		///     true if the HashSet object and other share at least one common element; otherwise, false.
		/// </returns>
		inline bool Overlaps(IDotEnumerable<T> &other);

		
		///     Removes the first occurrence of a specific object from the HashSet
		/// <param name="item">
		///   The element to remove
		/// </param>																										
		/// <returns>
		///     true if item is successfully removed; otherwise, false
		/// </returns>													
		inline bool Remove(T item);

		
		///     Removes all the elements that match the predicate conditions
		/// <param name="match">
		///		Predicate that accepts element from HashSet as argument and returns a value convertible to bool.
		/// </param>																										
		/// <returns>
		///     The number of elements removed from the HashSet
		/// </returns>	
		template <typename Predicate>
		inline int RemoveWhere(Predicate match);

		
		///     Determines whether a HashSet object and the specified collection contain the same elements.
		/// <param name="other">
		///   The collection to compare to the current HashSet
		/// </param>																										
		/// <returns>
		///     true if the HashSet object is equal to other; otherwise, false.
		/// </returns>	
		inline bool SetEquals(IDotEnumerable<T> &other);
		
		
		///     Modifies the current HashSet to contain only elements that are present either in that object or in the specified collection, but not both.
		/// <param name="other">
		///   The collection to compare to the current HashSet
		/// </param>
		inline void SymmetricExceptWith(IDotEnumerable<T> &other);
		
		
		///     Sets the capacity to the actual number of elements in the List, if that number is less than a threshold value.
		inline void TrimExcess();
		
		
		///     Modifies the current HashSet to contain all elements that are present in itself and the specified collection
		/// <param name="other">
		///   The collection to compare to the current HashSet
		/// </param>
		inline void UnionWith(IDotEnumerable<T> &other);
	};


}

#endif