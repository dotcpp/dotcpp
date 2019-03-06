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

#include <cl/dotcpp/main/system/Ptr.hpp>

namespace cl
{
    template <class T> class IEnumeratorImpl; template <class T> using IEnumerator = Ptr<IEnumeratorImpl<T>>;

    /// <summary>
    /// Supports a simple iteration over a generic collection.
    /// </summary>
    template <typename T>
    class IEnumeratorImpl
    {
    public: // METHODS

        /// <summary>
        /// Gets the element in the collection at the current position of the enumerator (const version).</summary>
        virtual const T& getCurrent() const = 0;

        /// <summary>
        /// Gets the element in the collection at the current position of the enumerator (non-const version).
        /// </summary>
        virtual T& getCurrent() = 0;

        /// <summary>
        /// Advances the enumerator to the next element of the collection.
        ///
        /// Returns true if the enumerator was successfully advanced to the next element;
        /// false if the enumerator has passed the end of the collection.
        /// </summary>
        virtual bool MoveNext() = 0;

        /// <summary>
        /// Sets the enumerator to its initial position, which is
        /// before the first element in the collection.
        /// </summary>
        virtual void Reset() = 0;
    };
}
