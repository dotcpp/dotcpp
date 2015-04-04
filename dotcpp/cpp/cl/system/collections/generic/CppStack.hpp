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

#ifndef __cl_system_collections_generic_Stack_hpp__
#define __cl_system_collections_generic_Stack_hpp__

#include <deque>

#include <cl/system/collections/generic/ICppCollection.hpp>
#include <cl/system/collections/generic/ICppEnumerable.hpp>
#include <cl/system/collections/generic/ICppEnumerator.hpp>

namespace cl
{
	/// Adapter class from STL deque to .NET Stack. srd::deque used as container to make possible Conataints(T item) and GetEnumerator() implementation
	template <typename T>
	class Stack : public detail::std_accessor_<cl::ICppEnumerable<T>
		, std::deque<T> >
	{
	public:
		typedef detail::std_accessor_<cl::ICppEnumerable<T>
			, std::deque<T> > base;
		typedef cl::ICppEnumerable<T> cl_enumerator_type;
		typedef std::deque<T> std_base;

	public:
		
		/// Stack constructor that create new empty instance of Stack
		Stack() : base() {	}
		
		
		/// Gets number of elements in Stack
		/// <returns>
		/// Number of elements in Stack
		/// </returns>
		inline int get_Count()
		{
			return this->get().size();
		}

		
		/// Erase all elements from Stack
		inline void Clear()
		{
			get().clear();
		}

		
		/// Searches element in Stack
		/// <param name="item">object to search</param>
		/// <returns>
		/// true if the item is found, or false, otherwise
		/// </returns>
		inline bool Contains(T item);
		
		
		/// Copies Stack elements to array starting at specified index
		/// <param name="array">target arra</param>
		/// <param name="arrayIndex">index in array at which copying begin</param>
		inline void CopyTo(T*& array, int arrayIndex);

		typedef cl::ICppEnumerator<T> Enumerator;

		//inline cl_enumerator_type GetEnumerator();

		///     Returns the object at the top of the Stack without removing it.
		/// <returns>
		///     The object at the top of the Stack
		/// </returns>
		inline T Peek()
		{
			return get().back();
		}
		

		///     Removes and returns the object at the top of the Stack
		/// <returns>
		///     The object that is removed from the beginning of the Stack
		/// </returns>
		inline T Pop()
		{
			T returnItem = get().top();
			get().pop_back();
			return returnItem;
		}

		
		///     Adds an object to the top of the Stack
		/// <param name="item">the object to add to the Stac</param>
		inline void Push(T item)
		{
			get().push_back(item);
		}

		
		///     Copies the elements of the Stack to a new array.
		/// <returns>
		///     An array containing copies of the elements of the Stack
		/// </returns>
		inline cl::Array<T> ToArray();

		
		
		///     Sets the capacity to the actual number of elements in the Stack, if that number is less than a threshold value.
		inline void TrimExcess();

		

	};


}

#endif