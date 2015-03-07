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

#ifndef __dot_system_DotObject_hpp__
#define __dot_system_DotObject_hpp__

#include <dot/system/declare.hpp>
#include <dot/system/DotFreezeState.hpp>
#include <dot/system/DotEx.hpp>

namespace dot
{
    class DotString;

    /// <summary>This is the ultimate base class of all classes with reference semantics.
    /// It works with DotPtr to provide an emulation of reference semantics in C++.\\
    /// For performance reasons, classes with value semantics are not derived from this type.</summary>
    class DOT_SYSTEM DotObject
    {
    protected: // CONSTRUCTORS

        /// <summary>This constructor is called by constructors in derived classes.</summary>
        DotObject() {}

    protected: // DESTRUCTOR

        /// <summary>Virtual destructor to ensure that destructor
        /// of the derived type is called by DotPtr.</summary>
        virtual ~DotObject() = default;

    public: // METHODS

        /// <summary>Returns a string that represents the current object.</summary>
        virtual DotString toString() const = 0;
    };
}

#endif  // __dot_system_DotObject_hpp__
