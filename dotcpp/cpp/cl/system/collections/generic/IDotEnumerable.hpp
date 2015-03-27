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

#ifndef __dot_IDotEnumerable_hpp__
#define __dot_IDotEnumerable_hpp__

#include <vector>
#include <list>

#include <dot/system/declare.hpp>
#include <dot/system/collections/generic/IDotEnumerator.hpp>

namespace dot
{
    namespace detail
    {
        struct empty_type {};
        struct null_type;

        /// To get value type from collection type
        template <typename Collection>
        struct is_collection {
            typedef null_type type;
            typedef null_type allocator_type;
        };

        template <typename ValueType, typename Allocator>
        struct is_collection <std::vector<ValueType, Allocator> >
        {
            typedef ValueType type;
            typedef Allocator allocator_type;
        };

        template <typename ValueType, typename Allocator>
        struct is_collection <std::deque<ValueType, Allocator> >
        {
            typedef ValueType type;
            typedef Allocator allocator_type;
        };

        template <typename ValueType, typename Allocator>
        struct is_collection <std::list<ValueType, typename Allocator> >
        {
            typedef ValueType type;
            typedef Allocator allocator_type;
        };
    }

    template <class T> class IDotEnumerator;

    template <typename Collection>
    struct std_accessor;

    template <typename T>
    struct std_accessor_base
    {
        template <typename CollectionType>
        inline std_accessor<CollectionType >& cast();
    };

    template <typename Collection>
    struct std_accessor : std_accessor_base <typename detail::is_collection<Collection>::type>
    {
        typedef typename
        detail::is_collection<Collection>::type value_type;

        std_accessor(std::reference_wrapper<Collection > const& c)
                : c_(c)
        {   }

        std::reference_wrapper<Collection > c_;
    };

    template <typename T>
    template <typename CollectionType>
    inline std_accessor<CollectionType >& std_accessor_base<T>::cast()
    {
        typedef typename
            detail::is_collection<CollectionType>::type request_value_type;

        static_assert(std::is_same<request_value_type, T>::value, "This is not converted collections type");
    }

    /// <summary>Exposes the enumerator, which supports a simple
    /// iteration over a collection of a specified type.</summary>
    template <class T>
    class IDotEnumerable
    {
    public: // METHODS
        template <typename Collection>
        explicit IDotEnumerable(std::reference_wrapper<Collection > coll)
            : accessor_(new std_accessor<Collection>(coll))
        {}

        /// <summary>(IDotEnumerable) Returns an enumerator that iterates through the collection.</summary>
        virtual dot::IDotEnumerator<T> GetEnumerator() = 0;

    protected:
        IDotEnumerable() = default;
    protected:
        std::unique_ptr<std_accessor_base<T > > accessor_;
    };

    namespace detail
    {
        template <typename Enumerable, typename Iterable >
        class std_accessor_ : public Enumerable
        {
        public:
            typedef typename
                detail::is_collection<Iterable>::type value_type;

            typedef Iterable std_base;

            std_accessor_() : Enumerable(std::ref(c_))
            {

            }

            //! Beginning position of non-constant iterator
            inline typename Iterable::iterator
            begin()
            {
                return c_.begin();
            }

            //! Ending position of non-constant iterator
            inline typename Iterable::iterator
            end()
            {
                return c_.end();
            }

            //! Beginning position of constant iterator
            inline typename Iterable::const_iterator
            begin() const
            {
                return c_.begin();
            }

            //! Ending position of constant iterator
            inline typename Iterable::const_iterator
            end() const
            {
                return c_.end();
            }


            //! Returns DotEnumerator for the beginning position
            inline dot::IDotEnumerator<value_type >
            GetEnumerator()
            {
                return dot::IDotEnumerator<value_type>(c_.begin());
            }

            //! Returns the enclosed STL container as constant reference
            inline std_base const& get() const
            {
                return this->c_;
            }

            //! Returns the enclosed STL container as non-constant reference
            inline std_base& get()
            {
                return this->c_;
            }

            Iterable c_;
        };
    }
}

#endif  // __dot_IDotEnumerable_hpp__
