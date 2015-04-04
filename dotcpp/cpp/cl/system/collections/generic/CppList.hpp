/*
Copyright (C) 2003-2015 CompatibL

This file is part of DotCpp (.C++), an open source implementation of
selected .NET class library APIs in native C++ with optional support
for algorithmic differentiation (AD), available from

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

#ifndef __cl_system_collections_generic_List_hpp__
#define __cl_system_collections_generic_List_hpp__

#include <cl/system/collections/generic/ICollection.hpp>
#include <cl/system/collections/generic/IEnumerable.hpp>
#include <cl/system/collections/generic/IEnumerator.hpp>
#include <deque>

namespace cl
{
    //!! Should be Exception? Also it is already defined.
    typedef std::runtime_error CppException;

    template <typename Type>
    struct CppReadOnlyCollection : detail::empty_type {};

    template <typename >
    struct ICppComparer : detail::empty_type {};

    template <typename, typename >
    struct CppConverter : detail::empty_type {};

    template <typename >
    struct CppAction : detail::empty_type { };

    template <typename>
    struct CppComparison : detail::empty_type  {};

    template <typename T>
    class CppList : public detail::std_accessor_<cl::ICppEnumerable<T>
                            , std::deque<T> >
    {
    public:
        typedef detail::std_accessor_<cl::ICppEnumerable<T>
                    , std::deque<T> > base;

        typedef cl::ICppEnumerable<T> cl_enumerator_type;

        typedef std::deque<T> std_base;

        typedef T& reference_type;
    public:

        CppList() : base()
        {}

        int Capacity; // { get; set; }

        inline int get_Count() const
        {
            return this->get().size();
        }

        inline reference_type
        operator[](unsigned int index) { return *(begin() + index); }

        inline void Add(T const& item)
        {
            this->get().push_back(item);
        }

        inline void AddRange(ICppEnumerable<T> const& collection);

        inline CppReadOnlyCollection<T> AsReadOnly();

        inline int BinarySearch(T item);

        inline int BinarySearch(T item, ICppComparer<T> comparer);
        int BinarySearch(int index, int count, T item, ICppComparer<T> comparer);
        void Clear();
        bool Contains(T item);

        template <typename TOutput, typename Coverter>
        inline CppList<TOutput>
        ConvertAll(CppConverter<T, TOutput> converter);

        template <int I>
        void CopyTo(T(&a)[I]);
        void CopyTo(T*& array, int arrayIndex);

        void CopyTo(int index, T*& array, int arrayIndex, int count);

        template <typename Predicate>
        inline bool Exists(Predicate match) const
        {
            return std::find_if(begin()
                    , end(), match) != end();
        }

        template <typename Predicate>
        inline CppList<T> FindAll(Predicate match) const
        {
            CppList<T> result;
            std::for_each(begin(), end()
                , [&result, &match](T& v)
                {
                    if (match)
                        result.push_back(v);
                }
            );

            return result;
        }

        template <typename Predicate>
        inline int FindIndex(int startIndex, Predicate match) const
        {
            typename std_base::const_iterator where
                = std::find_if(begin() + startIndex, end(), match);

            return where != end() ? where - begin : -1;
        }

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

        template<typename Predicate>
        inline int FindLastIndex(Predicate match) const
        {
            std_base::const_reverse_iterator where
                = std::find_if(get().rbegin(), get().rend(), match);

            if (where == get().rend())
                return -1;

            return this->get_Count() - (get().rbegin() - where);
        }

        template <typename Predicate>
        inline int FindLastIndex(int startIndex, Predicate match);

        template <typename Predicate>
        inline int FindLastIndex(int startIndex, int count, Predicate match);

        template <typename CppAction>
        inline void ForEach(CppAction action)
        {
            std::for_each(begin(), end(), action);
        }

        typedef cl::ICppEnumerator<T> Enumerator;

        //!! Implement
        CppList<T> GetRange(int index, int count) {}

        int IndexOf(T item);

        int IndexOf(T item, int index);

        int IndexOf(T item, int index, int count);

        void Insert(int index, T item);

        void InsertRange(int index, ICppEnumerable<T> const& collection);

        int LastIndexOf(T item);

        int LastIndexOf(T item, int index);

        int LastIndexOf(T item, int index, int count);

        bool Remove(T item);

        template <typename Predicate>
        inline int RemoveAll(Predicate match)
        {
            unsigned int sizeold = this->get().size();

            std::remove_if(begin(), end(), match);
            return sizeold - this->get().size();
        }

        void RemoveAt(int index)
        {
            assert(this->get().size() > index);

            this->get().erase(begin() + index);
        }

        void RemoveRange(int index, int count);

        void Reverse();

        void Reverse(int index, int count);

        void Sort();

        template <typename Comparer>
        void Sort(CppComparison<T> comparison);

        template <typename Comparer>
        void Sort(ICppComparer<T> comparer);

        template <typename Comparer>
        void Sort(int index, int count, Comparer comparer)
        {
            std::sort(begin() + index, begin() + index + count, comparer);
        }

        //!! Should be cl::Array<T>
        std::vector<T> ToArray();

        void TrimExcess();

        template <typename Predicate>
        inline bool TrueForAll(Predicate match);
    };

    //!! Move to a separate file
    template <typename T>
    class CppArray : public cl::ICppEnumerable<T>
    {
    public:
        typedef cl::ICppEnumerable<T> base;
        CppArray() : base(std::vector<T>())
        {}
    };
}

#endif // __cl_system_collections_generic_List_hpp__