/*
Copyright (C) 2003-2015 CompatibL

This file is part of .C++ project, an open source implementation of
selected .NET class library APIs in native C++ with optional support
for adjoint algorithmic differentiation (AAD), available from

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

#ifndef __cl_system_collections_generic_ICppCollection_hpp__
#define __cl_system_collections_generic_ICppCollection_hpp__

#include <cl/system/declare.hpp>
#include <cl/system/collections/generic/ICppEnumerable.hpp>

namespace cl
{
    template <class T> class CppArray;

    /// Generic collection interface.
    template <class T>
    class ICppCollection : public ICppEnumerable<T>
    {
    public: // METHODS

        /// (ICppCollection) Number of elements contained in the collection.
        virtual int count() = 0;

        /// (ICppCollection) Copies the elements of the ICollection(T)
        /// to a CppArray, starting at the specified CppArray index.
        virtual void copyTo(CppArray<T> array, int arrayIndex) = 0;

    protected:
        ICppCollection() = default;
    public:
        //static CppPtr<ICppCollection<T>> create() { throw ClEx("Attempting to create an instance of abstract type."); }
    };
}

#endif  // __cl_system_collections_generic_ICppCollection_hpp__
