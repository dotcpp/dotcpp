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

#include <cl/dotcpp/main/system/Object.hpp>

namespace cl
{
    class TypeImpl; using Type = Ptr<TypeImpl>;
    class String;
    class PropertyInfoImpl; using PropertyInfo = Ptr<PropertyInfoImpl>;
    template <typename T> class Array1DImpl; template <typename T> using Array1D = Ptr<Array1DImpl<T>>;

    /// <summary>
    /// Provides reflection functionality.
    /// </summary>
    class CL_DOTCPP_MAIN TypeImpl : public virtual ObjectImpl
    {
    public: // PROPERTIES

        /// <summary>Gets the name of the current type, excluding namespace.</summary>
        DOT_DECL_PROP_GET(TypeImpl, String, Name)

        /// <summary>Gets the fully qualified name of the type, including its namespace but not its assembly.</summary>
        DOT_DECL_PROP_GET(TypeImpl, String, FullName)

    public: // METHODS

        /// <summary>Returns all the public properties of the current type.</summary>
        virtual Array1D<PropertyInfo> GetProperties();

        /// <summary>A string representing the name of the current type.</summary>
        virtual String ToString() const { return "Type"; } // TODO - return name

    protected:
        TypeImpl() = default;
    };
}
