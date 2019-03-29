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

#include <cl/dotcpp/main/system/collections/generic/ICollection.hpp>

namespace cl
{
    template <class TKey, class TValue> class IDictionaryImpl;
    template <class TKey, class TValue> using IDictionary = Ptr<IDictionaryImpl<TKey, TValue>>;

    /// <summary>Represents a generic collection of key/value pairs.</summary>
    template <class TKey, class TValue>
    class IDictionaryImpl : public ICollectionImpl<std::pair<TKey, TValue>>
    {
    public: // PROPERTIES

        /// <summary>Gets an ICollection containing the keys of the IDictionary.</summary>
        DOT_DECL_GET(IDictionaryImpl, ICollection<TKey>, Keys)

        /// <summary>Gets an ICollection containing the values in the IDictionary.</summary>
        DOT_DECL_GET(IDictionaryImpl, ICollection<TValue>, Values)

    public: // METHODS

        /// <summary>Adds an element with the provided key and value to the IDictionary.</summary>
        void Add(const TKey& key, const TValue& value) = 0;

        /// <summary>Determines whether the IDictionary contains an element with the specified key.</summary>
        bool ContainsKey(const TKey& key) = 0;

        /// <summary>Removes the element with the specified key from the IDictionary.</summary>
        bool Remove(TKey key) = 0;

        /// <summary>Gets the value associated with the specified key.</summary>
        bool TryGetValue(const TKey& key, TValue& value) = 0;

    public: // OPERATORS

        /// <summary>Gets or sets the element with the specified key (const version).</summary>
        virtual const TValue& operator[](const TKey& key) const = 0;

        /// <summary>Gets or sets the element with the specified key (non-const version).</summary>
        virtual TValue& operator[](const TKey& key) = 0;
    };
}
