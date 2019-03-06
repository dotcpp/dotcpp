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

#ifndef cl_dotcpp_main_Stack_hpp
#define cl_dotcpp_main_Stack_hpp

#include <deque>

#include <cl/dotcpp/main/system/collections/generic/ICollection.hpp>
#include <cl/dotcpp/main/system/collections/generic/IEnumerable.hpp>
#include <cl/dotcpp/main/system/collections/generic/IEnumerator.hpp>

namespace cl
{
    template <class T> class Array;

    ///!!! Provide .NET description Adapter class from STL deque to .NET Stack. srd::deque used as container to make possible Conataints(T item) and GetEnumerator() implementation
    template <typename T>
    class Stack : public detail::std_accessor_< cl::IEnumerable<T>, std::deque<T> >
    {
    public:

        typedef detail::std_accessor_< cl::IEnumerable<T>, std::deque<T> > base;
        typedef cl::IEnumerable<T> cl_enumerator_type;
        typedef std::deque<T> std_base;

    public:

        /// <summary>Creates new empty instance of Stack.</summary>
        Stack() : base()
        {
        }

        /// <summary>Gets number of elements in Stack.</summary>
        inline int count() const
        {
            return this->get().size();
        }

        /// <summary>Erase all elements from Stack.</summary>
        inline void clear()
        {
            get().clear();
        }

        /// <summary>Searches element in Stack.</summary>
        inline bool contains(T item) const;

        /// <summary>Copies Stack elements to array starting at specified index.</summary>
        inline void copyTo(Array<T>& arr, int arrIndex) const;

        /// <summary>Returns the object at the top of the Stack without removing it.</summary>
        inline T peek() const
        {
            return get().back();
        }

        /// <summary>Removes and returns the object at the top of the Stack.</summary>
        inline T pop()
        {
            T returnItem = get().top();
            get().pop_back();
            return returnItem;
        }

        /// <summary>Adds an object to the top of the Stack.</summary>
        inline void push(T item)
        {
            get().push_back(item);
        }

        /// <summary>Copies the elements of the Stack to a new array.</summary>
        inline Array<T> toArray() const;

        /// <summary>Sets the capacity to the actual number of elements
        /// in the Stack, if that number is less than a threshold value.</summary>
        inline void trimExcess();
    };
}

#endif // cl_dotcpp_main_Stack_hpp