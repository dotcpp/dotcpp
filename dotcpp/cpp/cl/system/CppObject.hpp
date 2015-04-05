/*
Copyright (C) 2003-2015 CompatibL

This file is part of .C++, an open source implementation of TapeScript
in native C++ using .NET class library conventions, available from

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

#ifndef __cl_system_CppObject_hpp__
#define __cl_system_CppObject_hpp__

#include <cl/system/declare.hpp>
#include <cl/system/CppException.hpp>

namespace cl
{
    class CppString;

    /// <summary>This is the ultimate base class of all classes with reference semantics.
    /// It works with CppPtr to provide an emulation of reference semantics in C++.\\
    /// For performance reasons, classes with value semantics are not derived from this type.</summary>
    class CL_SYSTEM CppObject
    {
    protected: // DESTRUCTOR

        /// <summary>Virtual destructor to ensure that destructor
        /// of the derived type is called by CppPtr.</summary>
        virtual ~CppObject() = default;

    public: // METHODS

        /// <summary>Returns a string that represents the current object.</summary>
        virtual CppString toString() const = 0;

    protected:
        CppObject() = default;
    };
}

#endif  // __cl_system_CppObject_hpp__
