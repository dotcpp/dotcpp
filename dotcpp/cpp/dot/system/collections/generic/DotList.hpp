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

#ifndef __dot_system_collections_generic_List_hpp__
#define __dot_system_collections_generic_List_hpp__

#include <deque>

#include <dot/system/collections/generic/IDotCollection.hpp>
#include <dot/system/collections/generic/IDotEnumerable.hpp>
#include <dot/system/collections/generic/IDotEnumerator.hpp>

namespace dot
{
    typedef std::runtime_error Exception;

    template <typename Type>
    struct ReadOnlyCollection : detail::empty_type   {};

    template <typename >
    struct IComparer : detail::empty_type {};

    template <typename, typename >
    struct Converter : detail::empty_type {};

    //template <typename >
    //struct Predicate : detail::empty_type {};

    template <typename >
    struct Action : detail::empty_type { };

    template <typename>
    struct Comparison : detail::empty_type  {};

    
	/// Adapter class from STL deque
	/// to .NET List with access by index
	template <typename T>
    class List : public detail::std_accessor_<dot::IDotEnumerable<T>
                            , std::deque<T> >
    {
    public:
        typedef detail::std_accessor_<dot::IDotEnumerable<T>
                    , std::deque<T> > base;

        typedef dot::IDotEnumerable<T> dot_enumerator_type;

        typedef std::deque<T> std_base;

        typedef T& reference_type;
    public:

		
		/// List constructor that create new empty instance of List 
		List() : base()
        {   }

        int Capacity;// { get; set; }

		
		/// Gets number of elements in List
		/// <returns>
		/// Number of elements in List
		/// </returns>
		inline int get_Count() const
        {
            return this->get().size();
		}

		
		/// Gets element reference by index
		/// <param name="index">
		/// Index of element
		/// </param>
		/// <returns>
		/// Element reference at the index
		/// </returns>
		inline reference_type
        operator[](unsigned int index) { return *(begin() + index); }

		/// Adds the new element to the end of List
		/// <param name="item">New element</param>
		inline void Add(T const& item)    
        {
            this->get().push_back(item);
        }

		
		/// Adds the elements from other collection to the end of List
		/// <param name="collection">Other collection</param>
		inline void AddRange(IDotEnumerable<T> const& collection);

		/// Returns a read-only collection wrapper around List
		/// <returns>
		/// Read-only collection wrapper around List
		/// </returns>
		inline ReadOnlyCollection<T> AsReadOnly();

		
		/// Searches element in sorted List using default comparer
		/// and returns index of that element
		/// <param name="item">Object to search </param>
		/// <returns>
		/// Index of element in the List if the item is found
		/// </returns>
		inline int BinarySearch(T item);

		
		/// Searches element in sorted List using specified comparer
		/// and returns index of that element
		/// <param name="item">Object to search </param>
		/// <param name="comparer">IComparer implementation to compare elements</param>
		/// <returns>
		/// Index of element in the List if the item is found
		/// </returns>
		inline int BinarySearch(T item, IComparer<T> comparer);

		
		/// Searches element in sorted List in specifien range using 
		/// specified comparer and returns index of that element
		/// <param name="index">Starting range index</param>
		/// <param name="count">Lenght of range</param>
		/// <param name="item">Object to search </param>
		/// <param name="comparer">IComparer implementation to compare elements</param>
		/// <returns>
		/// Index of element in the List if the item is found
		/// </returns>
		int BinarySearch(int index, int count, T item, IComparer<T> comparer);

		
		/// Erase all elements from List
		void Clear();

		
		/// Searches element in List
		/// <param name="item">Object to search </param>
		/// <returns>
		/// true if the item is found, or false, otherwise
		/// </returns>
		bool Contains(T item);

		
		/// Converts elemetn of List from type T to type TOutput
		/// using converter
		/// <param name="TOutput">New element type</param>
		/// <param name="converter">Converter from T to TOutput</param>
		/// <returns>
		/// New List with elements of type TOutput converted from current List
		/// </returns>
		template <typename TOutput, typename Coverter>
        inline List<TOutput>
        ConvertAll(Converter<T, TOutput> converter);

		
		/// Copies List elements to array starting at then begining of arrray
		/// <param name="a">target array</param>
		template <int I>
        void CopyTo(T(&a)[I]);

		/// 
		/// Copies List elements to array starting at specified index
		/// <param name="array">Target array</param>
		/// <param name="arrayIndex">Index in array at which copying begins</param>
		void CopyTo(T*& array, int arrayIndex);

		
		/// Copies range of List elements to array starting at specified index
		/// <param name="index">Index in List at which copying begins</param>
		/// <param name="array">Target array</param>
		/// <param name="arrayIndex">Index in array at which copying begins</param>
		/// <param name="count">Number of elements to copy</param>
		void CopyTo(int index, T*& array, int arrayIndex, int count);

		
		/// Looks for elements in List that match predicate condition and returns bool
		/// <param name="match">Predicate that accepts element from List as argument and returns a value convertible to bool</param>
		/// <returns>
		/// true if there is element in List for which predicate returns true, otherwise, else
		/// </returns>
        template <typename Predicate>
        inline bool Exists(Predicate match) const 
        {
            return std::find_if(begin()
                    , end(), match) != end();
        }

		
		/// Looks for elements in List that match predicate condition and returns element
		/// <param name="match">Predicate that accepts element from List as argument and returns a value convertible to bool</param>
		/// <returns>
		/// Reference on the first occurrence an element from List for which predicate returns true
		/// </returns>
		template <typename Predicate>
		inline reference_type Find(Predicate match);

		
		/// Looks for elements in List that match predicate condition and returns it in new List
		/// <param name="match">Predicate that accepts element from List as argument and returns a value convertible to bool</param>
		/// <returns>
		/// List of all elements from List for which predicate returns true
		/// </returns>
        template <typename Predicate>
        inline List<T> FindAll(Predicate match) const
        {
            List<T> result;
            std::for_each(begin(), end()
                , [&result, &match](T& v)
                {
                    if (match(v)) 
                        result.push_back(v);
                }
            );

            return result;
        }

		
		/// Looks for element in List that match predicate condition and returns it index in List
		/// <param name="match">Predicate that accepts element from List as argument and returns a value convertible to bool</param>
		/// <returns>
		/// Index of the first occurrence an element from List for which predicate returns true
		/// </returns>
		template <typename Predicate>
		int FindIndex(Predicate match);

		 
		/// Looks for element in List starting at specified index that match predicate condition and returns it index in List
		/// <param name="startIndex">Index in List at which searching begins </param>
		/// <param name="match">Predicate that accepts element from List as argument and returns a value convertible to bool</param>
		/// <returns>
		/// Index of the first occurrence an element from List for which predicate returns true
		/// </returns>
        template <typename Predicate>
        inline int FindIndex(int startIndex, Predicate match) const  
        {
            typename std_base::const_iterator where 
                = std::find_if(begin() + startIndex, end(), match);

            return where != end() ? where - begin : -1;
        }

		 
		/// Looks for element in ranghe of elements in List that match predicate condition and returns it index in List
		/// <param name="startIndex">Index in List at which searching begins</param>
		/// <param name="count">Number of elements in range of List to search</param>
		/// <param name="match">Predicate that accepts element from List as argument and returns a value convertible to bool</param>
		/// <returns>
		/// Index of the first occurrence an element from specified range in List for which predicate returns true
		/// </returns>
		template <typename Predicate>
        inline int FindIndex(int startIndex, int count, Predicate match)
        {
            typename std_base::const_iterator start = begin() + startIndex;
            typename std_base::const_iterator end = start + count;

            assert(end <= end());

            typename std_base::const_iterator where
                = std::find_if(start, end , match);

            return where != end ? where - begin : -1;
        }

		 
		/// Looks for element in List that match predicate condition and returns it index in List
		/// <param name="match">Predicate that accepts element from List as argument and returns a value convertible to bool</param>
		/// <returns>
		/// Reference on the last occurrence an element from List for which predicate returns true
		/// </returns>
        template <typename Predicate>
        inline reference_type FindLast(Predicate match)
        {
            std_base::reverse_iterator where
                = std::find_if(get().rbegin(), get().rend(), match);

            if (where == get().rend())
            {
                return std::reference_wrapper<T>(*(T*)0);
            }

            return (*where);
        }

		 
		/// Looks for element in List that match predicate condition and returns it index in List
		/// <param name="match">Predicate that accepts element from List as argument and returns a value convertible to bool</param>
		/// <returns>
		/// Index the last occurrence an element from List for which predicate returns true
		/// </returns>
        template<typename Predicate>
        inline int FindLastIndex(Predicate match) const
        {
            std_base::const_reverse_iterator where
                = std::find_if(get().rbegin(), get().rend(), match);

            if (where == get().rend())
                return -1;

            return this->get_Count() - (get().rbegin() - where);
        }

		 
		/// Looks for element in List starting at specified index that match predicate condition and returns it index in List
		/// <param name="startIndex">Index in List at which searching begins </param>
		/// <param name="match">Predicate that accepts element from List as argument and returns a value convertible to bool</param>
		/// <returns>
		/// Index of the last occurrence an element from List for which predicate returns true
		/// </returns>
        template <typename Predicate>
        inline int FindLastIndex(int startIndex, Predicate match);

		/// 
		/// Looks for element in ranghe of elements in List that match predicate condition and returns it index in List
		/// <param name="startIndex">Index in List at which searching begins</param>
		/// <param name="count">Number of elements in range of List to search</param>
		/// <param name="match">Predicate that accepts element from List as argument and returns a value convertible to bool</param>
		/// <returns>
		/// Index of the last occurrence an element from specified range in List for which predicate returns true
		/// </returns>
		template <typename Predicate>
        inline int FindLastIndex(int startIndex, int count, Predicate match);

		 
		/// Apples action to each element in List
		/// <param name="action">Action that accepts element from List as argument</param>
		template <typename Action>
        inline void ForEach(Action action)
        {
            std::for_each(begin(), end(), action);
        }

        typedef dot::IDotEnumerator<T> Enumerator;

		 																												
		/// Returns sublist																											
		/// <param name="index">index in List at which copying begins</param>																		
		/// <param name="count">number of elements in range of List to copy</param>																	
		/// <returns>																												
		/// New List thet represent sublist of current List																			
		/// </returns>																												
		List<T> GetRange(int index, int count) {    }																				
		
		 																												
		///     Searches for the specified object and returns the index of the first entire in List									
		/// <param name="item">object to search</param>																							
		/// <returns>																												
		///     Index of the first occurrence of item in List																						
		/// </returns>																												
		int IndexOf(T item);																														
		
		 		
		///     Searches for the specified object and returns index of the first occurrence in List
		/// <param name="item">The object to search</param>
		/// <param name="index">starting index of the search</param>
		/// <returns>	
		///     Index of the first occurrence of item int the specified range of List
		/// </returns>				
		int IndexOf(T item, int index);
		
		/// 	
		///     Searches for the specified object and returns index of the first occurrence in List
		/// <param name="item">the object to search</param>
		/// <param name="index">starting index of the search</param>
		/// <param name="count">the number of elements in the range to search</param>
		/// <returns>	
		///     Index of the first occurrence of item int the specified range of List
		/// </returns>	
		int IndexOf(T item, int index, int count);
		

		 
		///     Inserts an element into List<T> at the specified index
		/// <param name="index">index at which item should be inserted</param>
        /// <param name="item">the object to insert</param>
		void Insert(int index, T item);
		
		/// 
		///     Inserts the elements of a collection into List at the specified index.
		/// <param name="index">index at which the new elements should be inserted</param>
		/// <param name="collection">the collection whose elements should be inserted into the List</param>
		void InsertRange(int index, IDotEnumerable<T> const& collection);
        
		 
        ///     Searches for the specified object and returns the index of the last occurrence in List
		/// <param name="item">the object to search</param>
		/// <returns>	
        ///     index of the last occurrence of item 
		/// </returns>
		int LastIndexOf(T item);

		 
		///     Searches for the specified object and returns the index of the last occurrence in List
		/// <param name="item">the object to search</param>
		/// <param name="index">starting index of the search</param>
		/// <returns>
		///     Index of the last occurrence of item int the specified range of List
		/// </returns>
		int LastIndexOf(T item, int index);
		 
		 
		///     Searches for the specified object and returns the index of the last occurrence in List
		/// <param name="item">the object to search</param>
		/// <param name="index">starting index of the search</param>
		/// <param name="count">the number of elements in the range to search</param>
		/// <returns>
		///     Index of the last occurrence of item int the specified range of List
		/// </returns>
		int LastIndexOf(T item, int index, int count);
		
		 
		///     Removes the first occurrence of a specific object from the List
		/// <param name="item">The object to remove </param>
		/// <returns>
		///     true if item is successfully removed; otherwise, false
		/// </returns>																													
		bool Remove(T item);

		 
		///     Removes all the elements that match the predicate conditions
		/// <param name="match">predicate that accepts element from List as argument and returns a value convertible to bool</param>
		/// <returns>
		///     The number of elements removed from the List
		/// </returns>	
		template <typename Predicate>
		inline int RemoveAll(Predicate match)
		{
			unsigned int sizeold = this->get().size();

			std::remove_if(begin(), end(), match);
			return sizeold - this->get().size();
		}

		 
		///     Removes the element at the specified index of the List
		/// <param name="index">index of the element to remove</param>
		void RemoveAt(int index)
		{
			assert(this->get().size() > index);

			this->get().erase(begin() + index);
		}
		
		 
		///     Removes a range of elements from the List
		/// <param name="index">starting index of the range of elements to remove</param>
		/// <param name="count">the number of elements to remove</param>
		void RemoveRange(int index, int count);

		/// 
		///     Reverses the order of the elements in the List
		void Reverse();
						
		 
		///     Reverses the order of the elements in the specified range.
		/// <param name="index">starting index of the range to reverse</param>
		/// <param name="count">the number of elements in the range to reverse</param>
		void Reverse(int index, int count);

		 
		///     Sorts the elements in the List the default comparer
		void Sort();

		/// 
		///     Sorts the elements in the List the specified comparsion
		/// <param name="comparison">comparer to use when comparing elements</param>
		template <typename Comparer>
        void Sort(Comparison<T> comparison);
		
		 
		///      Sorts the elements in the List the specified IComparer
		/// <param name="comparer">IComparer implementation to use when comparing elements</param>
		template <typename Comparer>
        void Sort(IComparer<T> comparer);

		///     Sorts the elements in a range of elements in List using the specified comparer.
		/// <param name="index">starting index of the range to sort</param>
		/// <param name="count">the length of the range to sort</param>
		/// <param name="comparer">use when comparing elements</param>
		template <typename Comparer>
        void Sort(int index, int count, Comparer comparer)
        {
            std::sort(begin() + index, begin() + index + count, comparer);
        }

        
		 
		///     Copies the elements of the List to a new array.
		/// <returns>
		///     An array containing copies of the elements of the List
		/// </returns>
		std::vector<T> ToArray(); // Should be dot::Array<T>

		 
		///     Sets the capacity to the actual number of elements in the List, if that number is less than a threshold value.
		void TrimExcess();

		 
		///     Determines whether every element in the List matches the conditions defined by the specified predicate.
		/// <param name="match">predicate that accepts element from List as argument and returns a value convertible to bool</param>
		/// <returns>
		///     true if every element in the List matches the predicate; otherwise, false
		/// </returns>
        template <typename Predicate>
        inline bool TrueForAll(Predicate match);
    };

    template <typename T>
    class Array : public dot::IDotEnumerable<T>
    {
    public:
        typedef dot::IDotEnumerable<T> base;
        Array() : base(std::vector<T>())
        {   }
    };
}

#endif