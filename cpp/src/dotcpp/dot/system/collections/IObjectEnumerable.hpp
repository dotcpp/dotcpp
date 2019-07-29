/*
Copyright (C) 2015-present The DotCpp Authors.

This file is part of .C++, a native C++ implementation of
popular .NET class library APIs developed to facilitate
code reuse between C# and C++.

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

#pragma once

#include <dot/declare.hpp>
#include <dot/system/ptr.hpp>
#include <dot/system/object.hpp>
#include <dot/detail/object_iterator.hpp>

namespace dot
{
    class IObjectEnumerableImpl; using IObjectEnumerable = ptr<IObjectEnumerableImpl>;
    class TypeImpl; using Type = ptr<TypeImpl>;

    /// <summary>
    /// Supports a simple iteration over a non-generic collection.
    ///
    /// In C\#, this interface is called IEnumerable. Because in C++ template and non-template
    /// types cannot have the same name, here it is called IObjectEnumerable.
    /// </summary>
    class DOT_CLASS IObjectEnumerableImpl : public virtual object_impl
    {
        typedef IObjectEnumerableImpl self;

    public:

        /// <summary>Returns forward begin object iterator.</summary>
        virtual detail::std_object_iterator_wrapper object_begin() = 0;

        /// <summary>Returns forward end object iterator.</summary>
        virtual detail::std_object_iterator_wrapper object_end() = 0;

    public: // REFLECTION

        virtual Type GetType();
        static Type typeof();
    };
}

namespace dot
{
    /// <summary>Implements begin() used by STL and similar algorithms.</summary>
    inline dot::detail::std_object_iterator_wrapper begin(dot::ptr<dot::IObjectEnumerableImpl> & obj)
    {
        return obj->object_begin();
    }

    /// <summary>Implements end() used by STL and similar algorithms.</summary>
    inline dot::detail::std_object_iterator_wrapper end(dot::ptr<dot::IObjectEnumerableImpl> & obj)
    {
        return obj->object_end();
    }
}