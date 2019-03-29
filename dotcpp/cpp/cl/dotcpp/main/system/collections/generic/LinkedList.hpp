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

#include <deque>

#include <cl/dotcpp/main/system/collections/generic/ICollection.hpp>
#include <cl/dotcpp/main/system/collections/generic/IEnumerable.hpp>
#include <cl/dotcpp/main/system/collections/generic/IEnumerator.hpp>

namespace cl
{
    ///!!! Not finished
    template <class T>
    class LinkedListNode
    {
    private:

    public:
        LinkedListNode(T Value);
    };

    ///!!! Not finished
    template <class T>
    class LinkedList : public detail::std_accessor_<cl::IEnumerable<T>
        , std::deque<T> >
    {
    public:
        typedef detail::std_accessor_<cl::IEnumerable<T>
            , std::deque<T> > base;
        typedef cl::IEnumerable<T> cl_enumerator_type;
        typedef std::deque<T> std_base;
        typedef T& reference_type;

        LinkedList() : base()
        {}

        inline int get_Count() const
        {
            return this->get().size();
        }
    };
}
