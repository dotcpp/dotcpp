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

#include <dot/system/collections/generic/ICollection.hpp>

namespace dot
{
    template <class T> class ISetImpl;
    template <class T> using ISet = Ptr<ISetImpl<T>>;

    /// <summary>Provides the base interface for the abstraction of sets.</summary>
    template <class T>
    class ISetImpl : public ICollectionImpl<T>
    {
        typedef ISetImpl<T> self;

    public: // METHODS

        /// <summary>Adds an element to the current set and returns a
        /// value to indicate if the element was successfully added.</summary>
        //virtual bool Add(const T& item) = 0;

        /// <summary>Removes all elements in the specified collection from the current set.</summary>
        virtual void ExceptWith(IEnumerable<T> other) = 0;

        /// <summary>Modifies the current set so that it contains only
        /// elements that are also in a specified collection.</summary>
        virtual void IntersectWith(IEnumerable<T> other) = 0;

        /// <summary>Determines whether the current set is a proper (strict)
        /// subset of a specified collection.</summary>
        //virtual bool IsProperSubsetOf(IEnumerable<T> other) = 0;

        /// <summary>Determines whether the current set is a proper (strict)
        /// superset of a specified collection.</summary>
        //virtual bool IsProperSupersetOf(IEnumerable<T> other) = 0;

        /// <summary>Determines whether a set is a subset of a specified collection.</summary>
        //virtual bool IsSubsetOf(IEnumerable<T> other) = 0;

        /// <summary>Determines whether the current set is a superset of a specified collection.</summary>
        //virtual bool IsSupersetOf(IEnumerable<T> other) = 0;

        /// <summary>Determines whether the current set overlaps with the specified collection.</summary>
        //virtual bool Overlaps(IEnumerable<T> other) = 0;

        /// <summary>Determines whether the current set and the
        /// specified collection contain the same elements.</summary>
        //virtual bool SetEquals(IEnumerable<T> other) = 0;

        /// <summary>Modifies the current set so that it contains only
        /// elements that are present either in the current set or in
        /// the specified collection, but not both.</summary>
        //virtual void SymmetricExceptWith(IEnumerable<T> other) = 0;

        /// <summary>Modifies the current set so that it contains all
        /// elements that are present in the current set, in
        /// the specified collection, or in both.</summary>
        //virtual void UnionWith(IEnumerable<T> other) = 0;
    };
}
