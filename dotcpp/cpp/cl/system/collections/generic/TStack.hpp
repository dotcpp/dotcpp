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

#ifndef __cl_system_collections_generic_TStack_hpp__
#define __cl_system_collections_generic_TStack_hpp__

#include <deque>

#include <cl/system/collections/generic/ITCollection.hpp>
#include <cl/system/collections/generic/ITEnumerable.hpp>
#include <cl/system/collections/generic/ITEnumerator.hpp>

namespace cl
{
    template <class T> class TArray;

    ///!!! Provide .NET description Adapter class from STL deque to .NET Stack. srd::deque used as container to make possible Conataints(T item) and GetEnumerator() implementation
    template <typename T>
    class TStack : public detail::std_accessor_< cl::ITEnumerable<T>, std::deque<T> >
    {
    public:

        typedef detail::std_accessor_< cl::ITEnumerable<T>, std::deque<T> > base;
        typedef cl::ITEnumerable<T> cl_enumerator_type;
        typedef std::deque<T> std_base;

    public:

        /// <summary>Creates new empty instance of Stack.</summary>
        TStack() : base()
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

        /// <summary>Copies TStack elements to array starting at specified index.</summary>
        inline void copyTo(TArray<T>& arr, int arrIndex) const;

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
        inline TArray<T> toArray() const;

        /// <summary>Sets the capacity to the actual number of elements
        /// in the Stack, if that number is less than a threshold value.</summary>
        inline void trimExcess();
    };
}

#endif // __cl_system_collections_generic_TStack_hpp__