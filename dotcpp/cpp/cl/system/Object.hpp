/*
Copyright (C) 2003-2015 CompatibL

This file is part of CompatibL .C++ (DotCpp), an open source
implementation of selected .NET class library APIs in native C++
with optional support for adjoint algorithmic differentiation (AAD),
available from

    http://github.com/compatibl/dotcpp (source)
    http://compatibl.com/dotcpp (documentation)

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

#ifndef __cl_system_Object_hpp__
#define __cl_system_Object_hpp__

#include <cl/system/declare.hpp>
#include <cl/system/FreezeState.hpp>
#include <cl/system/Exception.hpp>

namespace cl
{
    class String;

    /// <summary>This is the ultimate base class of all classes with reference semantics.
    /// It works with Ptr to provide an emulation of reference semantics in C++.\\
    /// For performance reasons, classes with value semantics are not derived from this type.</summary>
    class CL_SYSTEM Object
    {
    protected: // CONSTRUCTORS

        /// <summary>This constructor is called by constructors in derived classes.</summary>
        Object() {}

    protected: // DESTRUCTOR

        /// <summary>Virtual destructor to ensure that destructor
        /// of the derived type is called by Ptr.</summary>
        virtual ~Object() = default;

    public: // METHODS

        /// <summary>Returns a string that represents the current object.</summary>
        virtual String toString() const = 0;

    protected:
        Object() = default;
    public:
        static Ptr<Object> create() { throw ClEx("Attempting to create an instance of abstract type."); }
    };
}

#endif  // __cl_system_Object_hpp__
