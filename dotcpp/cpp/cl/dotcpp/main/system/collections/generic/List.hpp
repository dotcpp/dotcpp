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

#include <cl/dotcpp/main/system/collections/generic/ListBase.hpp>

namespace cl
{
    template <class T> class ListImpl; template <class T> using List = Ptr<ListImpl<T>>;

    /// <summary>
    /// Represents a strongly typed list of objects that can be accessed by index.
    /// Provides methods to search, sort, and manipulate lists.
    /// </summary>
    template <class T>
    class ListImpl : public ListBaseImpl<T>
    {
        typedef std::vector<T> base;

        template <class T>
        friend List<T> new_List();

    private: // CONSTRUCTORS

        /// <summary>
        /// Initializes a new instance of the list that is empty and has the default initial capacity.
        ///
        /// This constructor is private. Use new_List() function instead.
        /// </summary>
        ListImpl() {}

    public: // METHODS

        /// <summary>Adds the elements of the specified collection to the end of the list.</summary>
        // TODO void AddRange(const IEnumerable<T>& collection);
    };

    /// <summary>
    /// Initializes a new instance of the list that is empty and has the default initial capacity.
    /// </summary>
    template <class T>
    List<T> new_List() { return new ListImpl<T>(); }
}
