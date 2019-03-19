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

#include <cl/dotcpp/main/declare.hpp>
#include <cl/dotcpp/main/system/Ptr.hpp>

namespace cl
{
    class Object;
    class StringImpl; using String = Ptr<StringImpl>;
    class TypeImpl; using Type = Ptr<TypeImpl>;

    /// <summary>
    /// All classes with reference semantics should derive from this type.
    /// It works with Ptr to provide an emulation of reference semantics in C++.
    /// </summary>
    class ObjectImpl
    {
    public: // DESTRUCTOR

        /// <summary>
        /// Virtual destructor to ensure that destructor
        /// of the derived type is called by Ptr.
        /// </summary>
        virtual ~ObjectImpl() = default;

    public: // METHODS

        /// <summary>Gets the Type of the current instance.</summary>
        virtual Type GetType();

        /// <summary>
        /// String that represents the current object.
        ///
        /// Default implementation returns full name of the class.
        /// </summary>
        virtual String ToString() const;

    protected:
        ObjectImpl() = default;
    };
}
