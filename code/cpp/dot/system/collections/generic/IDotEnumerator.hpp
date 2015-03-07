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

#ifndef __dot_system_collections_generic_IDotEnumerator_hpp__
#define __dot_system_collections_generic_IDotEnumerator_hpp__

#include <dot/system/declare.hpp>

namespace dot
{
    class DotBool;

    /// <summary>Supports a simple iteration over a generic collection.</summary>
    template <class T>
    class IDotEnumerator
    {
    public: // METHODS

        /// <summary>Gets the element in the collection at the current position of the enumerator.</summary>
        virtual T current() = 0;

        /// <summary>Advances the enumerator to the next element of the collection.\\
        /// Returns true if the enumerator was successfully advanced to the next element;
        /// false if the enumerator has passed the end of the collection.</summary>
        virtual DotBool moveNext() = 0;

        /// <summary>Sets the enumerator to its initial position, which is before the first element in the collection.</summary>
        virtual void reset() = 0;
        
    protected:
        IDotEnumerator() = default;
    public:
        static DotPtr<IDotEnumerator<T>> create() { throw ClEx("Attempting to create an instance of abstract type."); }
    };
}

#endif  // __dot_system_collections_generic_IDotEnumerator_hpp__
