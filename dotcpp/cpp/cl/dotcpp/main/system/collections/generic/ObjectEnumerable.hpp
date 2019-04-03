/*
Copyright (C) 2003-present CompatibL

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

#include <cl/dotcpp/main/declare.hpp>
#include <cl/dotcpp/main/system/Ptr.hpp>
#include <cl/dotcpp/main/system/Object.hpp>
#include <cl/dotcpp/main/detail/object_iterator.hpp>

namespace cl
{

    class ObjectEnumerableImpl; using ObjectEnumerable = Ptr<ObjectEnumerableImpl>;

    class ObjectEnumerableImpl : public virtual ObjectImpl
    {
    public:

        /// <summary>Returns forward begin object iterator.</summary>
        virtual detail::std_object_iterator_wrapper obj_begin() = 0;

        /// <summary>Returns forward end object iterator.</summary>
        virtual detail::std_object_iterator_wrapper obj_end() = 0;

    };

}

namespace std
{
    /// <summary>Implements begin() used by STL and similar algorithms.</summary>
    inline auto begin(cl::ObjectEnumerable & obj)
    {
        return obj->obj_begin();
    }

    /// <summary>Implements end() used by STL and similar algorithms.</summary>
    inline auto end(cl::ObjectEnumerable & obj)
    {
        return obj->obj_end();
    }
}