/*
Copyright (C) 2003-2015 CompatibL

This file is part of .C++, a native C++ implementation of
selected .NET class library APIs with built-in support for
algorithmic differentiation (AD), available from

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

#ifndef __cl_system_TObject_hpp__
#define __cl_system_TObject_hpp__

#include <cl/system/declare.hpp>
#include <cl/system/detail/ref_counter.hpp>
#include <cl/system/TException.hpp>


namespace cl
{
    class TString;

    /// <summary>This is the ultimate base class of all classes with reference semantics.
    /// It works with TPtr to provide an emulation of reference semantics in C++.\\
    /// For performance reasons, classes with value semantics are not derived from this type.</summary>
    class CL_SYSTEM TObject : public RefCounter
    {
    public:

        /// <summary>Virtual destructor to ensure that destructor
        /// of the derived type is called by TPtr.</summary>
        virtual ~TObject() = default;

    public: // METHODS

        /// <summary>Returns a string that represents the current object.</summary>
        virtual TString toString() const = 0;

    protected:
        TObject() = default;
    };
}

#endif  // __cl_system_TObject_hpp__
