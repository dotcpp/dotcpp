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

#include <dot/declare.hpp>
#include <dot/system/Type.hpp>

namespace cl
{
    /// <summary>
    /// Contains methods to create types of objects locally or remotely, or obtain 
    /// references to existing remote objects. This class cannot be inherited.
    /// </summary>
    class CL_DOTCPP_MAIN Activator final
    {
    private: // CONSTRUCTORS

        Activator() = delete;
        Activator(const Activator&) = delete;
        Activator operator=(const Activator&) = delete;

    public: // METHODS

        /// <summary>Creates an instance of the specified type using that type's default constructor.</summary>
        static Object CreateInstance(Type type);

        /// <summary>Creates an instance of the specified type using the constructor that best matches the specified parameters.</summary>
        static Object CreateInstance(Type type, Array1D<Object> params);

        /// <summary>Creates an instance of the type whose name is specified, using the named assembly and default constructor.</summary>
        static Object CreateInstance(String assemblyName, String typeName);

        /// <summary>Creates an instance of the type whose name is specified, using the named assembly and default constructor.</summary>
        static Object CreateInstance(String assemblyName, String typeName, Array1D<Object> params);
    };
}
