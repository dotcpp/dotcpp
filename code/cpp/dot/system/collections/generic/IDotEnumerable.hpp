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

#ifndef __dot_system_collections_generic_IDotEnumerable_hpp__
#define __dot_system_collections_generic_IDotEnumerable_hpp__

#include <dot/system/declare.hpp>

namespace dot
{
    template <class T> class IDotEnumerator;

    /// <summary>Exposes the enumerator, which supports a simple
    /// iteration over a collection of a specified type.</summary>
    template <class T>
    class IDotEnumerable
    {
    public: // METHODS

        /// <summary>(IDotEnumerable) Returns an enumerator that iterates through the collection.</summary>
        virtual IDotEnumerator<T> GetEnumerator() = 0;
    };
}

#endif  // __dot_system_collections_generic_IDotEnumerable_hpp__
