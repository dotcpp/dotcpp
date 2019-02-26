/*
Copyright (C) 2003-2015 CompatibL

This file is part of .C++, a native C++ implementation of
selected .NET class library APIs with built-in support for
algorithmic differentiation (AD), available from

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

#ifndef cl_dotcpp_main_LinkedList_hpp
#define cl_dotcpp_main_LinkedList_hpp

#include <deque>

#include <cl/system/api/collections/generic/ITCollection.hpp>
#include <cl/system/api/collections/generic/ITEnumerable.hpp>
#include <cl/system/api/collections/generic/ITEnumerator.hpp>

namespace cl
{
    ///!!! Not finished
    template <typename T>
    class TLinkedListNode
    {
    private:

    public:
        TLinkedListNode(T Value);
    };

    ///!!! Not finished
    template <typename T>
    class TLinkedList : public detail::std_accessor_<cl::ITEnumerable<T>
        , std::deque<T> >
    {
    public:
        typedef detail::std_accessor_<cl::ITEnumerable<T>
            , std::deque<T> > base;
        typedef cl::ITEnumerable<T> cl_enumerator_type;
        typedef std::deque<T> std_base;
        typedef T& reference_type;

        TLinkedList() : base()
        {}

        inline int get_Count() const
        {
            return this->get().size();
        }
    };
}

#endif // cl_dotcpp_main_LinkedList_hpp