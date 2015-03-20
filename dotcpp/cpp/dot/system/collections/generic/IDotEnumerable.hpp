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
        virtual IDotEnumerator<T> begin() = 0;
        virtual IDotEnumerator<T> end() = 0;

        template <typename CollectionType>
        inline std_accessor<CollectionType >& cast();
    };

    template <typename Collection>
    struct std_accessor : std_accessor_base <typename detail::is_collection<Collection>::type>
    {
        typedef typename
        detail::is_collection<Collection>::type value_type;

        std_accessor(Collection const& c) : c_(c)   
        {   }

        virtual IDotEnumerator<value_type> begin()
        {
            return IDotEnumerator<value_type>(c_.begin());
        }

        virtual IDotEnumerator<value_type> end()
        {
            return IDotEnumerator<value_type>(c_.end());
        }

        Collection c_;
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
        explicit IDotEnumerable(Collection coll) 
            : accessor_(new std_accessor<Collection>(coll))
        {}

        /// <summary>(IDotEnumerable) Returns an enumerator that iterates through the collection.</summary>
        virtual IDotEnumerator<T> GetEnumerator() 
        { 
            return this->begin(); 
        }

        /// <summary> To C++ for each support we should have </summary>
        inline IDotEnumerator<T> begin() 
        {
            return accessor_->begin();
        }

        /// <summary> To C++ for each support we should have </summary>
        inline IDotEnumerator<T> end() 
        {
            return accessor_->end();
        }

    protected:
        IDotEnumerable() = default;
    protected:
        std::unique_ptr<std_accessor_base<T > > accessor_;
    };
}

#endif  // __dot_IDotEnumerable_hpp__
