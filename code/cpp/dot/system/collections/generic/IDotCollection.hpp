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

#ifndef __dot_system_collections_generic_IDotCollection_hpp__
#define __dot_system_collections_generic_IDotCollection_hpp__

#include <dot/system/declare.hpp>
#include <dot/system/collections/generic/IDotEnumerable.hpp>

namespace dot
{
    template <class T> class DotArray;

    /// <summary>Generic collection interface.</summary>
    template <class T>
    class IDotCollection : public IDotEnumerable
    {
    public: // METHODS

        /// <summary>(IDotCollection) Number of elements contained in the collection.</summary>
        virtual int count() = 0;

        /// <summary>(IDotCollection) Copies the elements of the ICollection(T)
        /// to a DotArray, starting at the specified DotArray index.</summary>
        virtual void copyTo(DotArray<T> array, int arrayIndex) = 0;
    };
}

#endif  // __dot_system_collections_generic_IDotCollection_hpp__
