/*
Copyright (C) 2015-present The DotCpp Authors.

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

#include <dot/declare.hpp>
#include <dot/system/ptr.hpp>
#include <dot/system/collections/IObjectEnumerable.hpp>

namespace dot
{
    class IObjectCollectionImpl; using IObjectCollection = ptr<IObjectCollectionImpl>;
    class TypeImpl; using Type = ptr<TypeImpl>;

    /// <summary>
    /// Supports a collection API over a non-generic collection.
    ///
    /// In C\#, this interface is called ICollection. Because in C++ template
    /// and non-template types cannot have the same name, here it is
    /// called IObjectCollection.
    /// </summary>
    class DOT_CLASS IObjectCollectionImpl : public IObjectEnumerableImpl
    {
        typedef IObjectCollectionImpl self;

    public: // METHODS

        /// <summary>
        /// Adds an item to the end of the collection.
        ///
        /// In C\#, the non-generic method is implemented for the interface
        /// but not for the class to avoid ambiguous conversions. Because
        /// in C++ this cannot be done, here this method has Object prefix.
        /// </summary>
        virtual void ObjectAdd(Object item) = 0;

    public: // REFLECTION

        virtual Type GetType();
        static Type typeof();
    };
}
