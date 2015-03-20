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

#ifndef __dot_DotList_hpp__
#define __dot_DotList_hpp__

#include <dot/system/collections/generic/IDotCollection.hpp>
#include <dot/system/collections/generic/IDotEnumerable.hpp>
#include <dot/system/collections/generic/IDotEnumerator.hpp>
#include <deque>

namespace dot
{
    template <typename Type>
    struct ReadOnlyCollection : detail::empty_type {};

    template <typename >
    struct IComparer : detail::empty_type {};

    template <typename, typename >
    struct Converter : detail::empty_type {};

    template <typename >
    struct Predicate : detail::empty_type {};

    template <typename >
    struct Action : detail::empty_type { };

    template <typename>
    struct Comparison : detail::empty_type  {};

    template <typename T>
    class List : public detail::std_accessor_<dot::IDotEnumerable<T>
                            , std::deque<T> >
    {
    public:
        typedef detail::std_accessor_<dot::IDotEnumerable<T>
                    , std::deque<T> > base;
        typedef dot::IDotEnumerable<T> dot_enumerator_type;
        typedef std::deque<T> std_base;
    private:
        inline std_base& get_()
        {
            return this->c_;
        }
    public:

        List() : base()
        {}

        int Capacity; // { get; set; }

        inline int get_Count()
        {
            return this->get_().size();
        }

        T& operator[](unsigned int) {   }

        inline void Add(T const& item)
        {
            this->get_().push_back(item);
        }

        inline void AddRange(IDotEnumerable<T> const& collection);

        inline ReadOnlyCollection<T> AsReadOnly();

        inline int BinarySearch(T item);

        inline int BinarySearch(T item, IComparer<T> comparer);
        int BinarySearch(int index, int count, T item, IComparer<T> comparer);
        void Clear();
        bool Contains(T item);

        template <typename TOutput>
        inline List<TOutput>
            ConvertAll(Converter<T, TOutput> converter);

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

        inline List<T> FindAll(Predicate<T> match)
        {
            List<T> result;
            std::for_each(begin(), end()
                , [&result, &match](T& v)
                {
                    if (match)
                        result.push_back(v);
                }
            );

            return result;
        }

        int FindIndex(int startIndex, Predicate<T> match);

        int FindIndex(int startIndex, int count, Predicate<T> match);

        T FindLast(Predicate<T> match);

        template<typename Predicate>
        inline int FindLastIndex(Predicate match)
        {
            std_base::iterator where = std::find_if(begin(), end(), comparer);
            if (where != end())
                return -1;

            return (where - begin());
        }

        int FindLastIndex(int startIndex, Predicate<T> match);

        int FindLastIndex(int startIndex, int count, Predicate<T> match);

        void ForEach(Action<T> action);

        typedef dot::IDotEnumerator<T> Enumerator;

        List<T> GetRange(int index, int count);

        int IndexOf(T item);

        int IndexOf(T item, int index);

        int IndexOf(T item, int index, int count);

        void Insert(int index, T item);

        void InsertRange(int index, IDotEnumerable<T> const& collection);

        int LastIndexOf(T item);

        int LastIndexOf(T item, int index);

        int LastIndexOf(T item, int index, int count);

        bool Remove(T item);

        int RemoveAll(Predicate<T> match);

        void RemoveAt(int index);

        void RemoveRange(int index, int count);

        void Reverse();

        //     System.Collections.Generic.List<T>.
        void Reverse(int index, int count);

        void Sort();

        void Sort(Comparison<T> comparison);

        void Sort(IComparer<T> comparer);

        template <typename Predicate>
        void Sort(int index, int count, Predicate comparer)
        {
            std::sort(begin() + index, begin() + index + count, comparer);
        }

        //!! Should be dot::Array<T>
        std::vector<T> ToArray();

        void TrimExcess();

        bool TrueForAll(Predicate<T> match);
    };

    template <typename T>
    class Array : public dot::IDotEnumerable<T>
    {
    public:
        typedef dot::IDotEnumerable<T> base;
        Array() : base(std::vector<T>())
        {}
    };
}

#endif // __dot_DotList_hpp__