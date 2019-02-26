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

#ifndef cl_dotcpp_main_Queue_hpp
#define cl_dotcpp_main_Queue_hpp

#include <deque>

#include <cl/dotcpp/main/system/collections/generic/ICollection.hpp>
#include <cl/dotcpp/main/system/collections/generic/IEnumerable.hpp>
#include <cl/dotcpp/main/system/collections/generic/IEnumerator.hpp>

namespace cl
{
    ///!! Provide description Adapter class from STL deque to .NET Queue. std::deque used as container to make possible Conataints(T item) and GetEnumerator() implementation
    template <typename T>
    class TQueue : public detail::std_accessor_<cl::ITEnumerable<T>, std::deque<T> >
    {
    public:

        typedef detail::std_accessor_<cl::ITEnumerable<T>, std::deque<T> > base;
        typedef cl::ITEnumerable<T> cl_enumerator_type;

    public:

        /// <summary>Queue constructor that create new empty instance of Queue.</summary>
        TQueue() : base()
        {
        }

        /// <summary>Gets number of elements in collection.</summary>
        inline int getCount() const
        {
            return this->get().size();
        }

        /// <summary>Erase all elements from Queue.</summary>
        inline void clear()
        {
            get().clear();
        }

        /// <summary>Searches for an element in Queue.</summary>
        inline bool contains(const T& item) const;

        /// <summary>Copies Queue elements to array starting at specified index.</summary>
        inline void copyTo(TArray<T>& arr, int arrIndex) const;

        /// <summary>Removes and returns the object at the beginning of the Queue.</summary>
        inline T dequeue()
        {
            T returnItem = get().front();
            get().pop_front();
            return returnItem;
        }

        /// <summary>Adds an object to the end of the Queue.</summary>
        inline void enqueue(T item)
        {
            get().push_back(item);
        }

        /// <summary>Returns the object at the beginning of the Queue without removing it.</summary>
        inline T peek() const
        {
            return get().front();
        }

        /// <summary>Copies the elements of the Queue to a new array.</summary>
        inline TArray<T> toArray() const;

        /// <summary>Sets the capacity to the actual number of elements in the Queue, if that number is less than a threshold value.</summary>
        inline void trimExcess();
    };
}

#endif // cl_dotcpp_main_Queue_hpp