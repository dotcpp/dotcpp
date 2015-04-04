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

#ifndef __cl_system_collections_generic_SortedSet_hpp__
#define __cl_system_collections_generic_SortedSet_hpp__

#include <set>

#include <cl/system/collections/generic/ICppCollection.hpp>
#include <cl/system/collections/generic/ICppEnumerable.hpp>
#include <cl/system/collections/generic/ICppEnumerator.hpp>

namespace cl
{
	
	/// Adapter class from STL set to .NET SortedSet
	template <typename T>
	class SortedSet : public detail::std_accessor_<cl::ICppEnumerable<T>
		, std::set<T> >
	{
	public:
		typedef detail::std_accessor_<cl::ICppEnumerable<T>
			, std::set<T> > base;
		typedef cl::ICppEnumerable<T> cl_enumerator_type;
		typedef std::set<T> std_base;

	public:
		
		/// SortedSet constructor that create new empty instance of SortedSet
		SortedSet() : base() {	}

		
		/// Gets number of elements in SortedList
		/// <returns>
		/// Number of elements in SortedList
		/// </returns>
		inline int get_Count()
		{
			return this->get().size();
		}

		
		///     Gets the maximum value in SortedSet
		/// <returns>
		///     The maximum value in the set.
		/// </returns>
		inline T get_Max();

		
		///     Gets the minimum value in SortedSet
		/// <returns>
		///     The minimum value in the set.
		/// </returns>
		inline T get_Min();

		
		///     Adds the specified key and value to the SortedSet
		/// <param name="key">the key of the element to add</param>
		/// <param name="value">the value of the element to add</param>
		inline bool Add(T item);

		
		///     Removes all keys and values from the SortedSet
		inline void Clear();

		
		/// Searches element in SortedSet
		/// <param name="item">object to search</param>
		/// <returns>
		/// true if the item is found, or false, otherwise
		/// </returns>
		inline bool Contains(T item);

		
		/// Copies SortedSet elements to array starting at then begining of arrray
		/// <param name="array">target array</param>
		void CopyTo(T*& array);

		/// Copies SortedSet elements to array starting at specified index
		/// <param name="array">target array</param>
		/// <param name="arrayIndex">index in array at which copying begins</param>
		void CopyTo(T*& array, int arrayIndex);


		/// Copies a specified number of SortedSet elements to array starting at specified index
		/// <param name="array">target array</param>
		/// <param name="arrayIndex">index in array at which copying begins</param>
		/// <param name="count">number of elements to copy</param>
		void CopyTo(T*& array, int arrayIndex, int count);

		
		///     Removes all elements in the specified collection from the current SortedSet object.
		/// <param name="other">the collection of items to remove from the SortedSet object</param>
		inline void ExceptWith(ICppEnumerable<T> &other);

		
		///     Modifies the current SortedSet to contain only elements that are present in that object and in the specified collection
		/// <param name="other">the collection to compare to the current SortedSet</param>
		inline void IntersectWith(ICppEnumerable<T> &other);

		
		///     Determines whether a SortedSet object is a proper subset of the specified collection.
		/// <param name="other">the collection to compare to the current SortedSet</param>
		/// <returns>
		///     true if the SortedSet object is a proper subset of other; otherwise, false.
		/// </returns>
		inline bool IsProperSubsetOf(ICppEnumerable<T> &other);

		
		///     Determines whether a SortedSet is a proper superset of the specified collection.
		/// <param name="other">the collection to compare to the current SortedSet</param>
		/// <returns>
		///     true if the SortedSet is a proper superset other; otherwise, false.
		/// </returns>
		inline bool IsProperSupersetOf(ICppEnumerable<T> &other);

		
		///     Determines whether a HashSet is a subset of the specified collection
		/// <param name="other">the collection to compare to the current SortedSet</param>
		/// <returns>
		///     true if the SortedSet is a subset of other; otherwise, false
		/// </returns>
		inline bool IsSubsetOf(ICppEnumerable<T> &other);

		
		///     Determines whether a SortedSet is a superset of the specified collection.
		/// <param name="other">the collection to compare to the current SortedSet</param>
		/// <returns>
		///     true if the SortedSet is a superset of other; otherwise, false.
		/// </returns>
		inline bool IsSupersetOf(ICppEnumerable<T> &other);

		
		///     Determines whether the current SortedSet and a specified collection share common elements.
		/// <param name="other">other collection to compare to the current SortedSet</param>
		/// <returns>
		///     true if the SortedSet object and other share at least one common element; otherwise, false.
		/// </returns>
		inline bool Overlaps(ICppEnumerable<T> &other);

		
		///     Removes the first occurrence of a specific object from the SortedSet
		/// <param name="item">The object to remove </param>
		/// <returns>
		///     true if item is successfully removed; otherwise, false
		/// </returns>	
		inline bool Remove(T item);

		
		///     Removes all the elements that match the predicate conditions
		/// <param name="match">predicate that accepts element from SortedSet as argument and returns a value convertible to bool</param>
		/// <returns>
		///     The number of elements removed from the SortedSet
		/// </returns>	
		template <typename Predicate>
		inline int RemoveWhere(Predicate match);

		
		///     Returns an ICppEnumerable that iterates over the SortedSet in reverse order.
		/// <returns>
		///     An enumerator that iterates over the SortedSet in reverse order.
		/// </returns>	
		inline ICppEnumerable<T>& Reverse();

		
		///     Determines whether a SortedSet object and the specified collection contain the same elements.
		/// <param name="other">the collection to compare to the current SortedSet</param>
		/// <returns>
		///     true if the SortedSet object is equal to other; otherwise, false.
		/// </returns>	
		inline bool SetEquals(ICppEnumerable<T> &other);

		
		///     Modifies the current SortedSet to contain only elements that are present either in that object or in the specified collection, but not both.
		/// <param name="other">the collection to compare to the current SortedSet</param>
		inline void SymmetricExceptWith(ICppEnumerable<T> &other);

		
		///     Modifies the current SortedSet to contain all elements that are present in itself and the specified collection
		/// <param name="other">the collection to compare to the current SortedSet</param>
		inline void UnionWith(ICppEnumerable<T> &other);


	};


}

#endif