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

#include <cl/dotcpp/main/system/reflection/MemberInfo.hpp>

namespace cl
{
    class ParameterInfoImpl; using ParameterInfo = Ptr<ParameterInfoImpl>;

    /// <summary>
    /// Discovers the attributes of a parameter and provides access to parameter metadata.
    /// </summary>
    class ParameterInfoImpl : public virtual ObjectImpl
    {
        friend ParameterInfo new_ParameterInfo(String , Type, int);

    public: // METHODS

        /// <summary>Gets the type of this parameter.</summary>
        DOT_AUTO_GET(Type, ParameterType)

        /// <summary>Gets the name of this parameter.</summary>
        DOT_AUTO_GET(String, Name)

        /// <summary>Gets the zero-based position of the parameter in the formal parameter list.</summary>
        DOT_AUTO_GET(int, Position)

    private: // CONSTRUCTORS

        /// <summary>
        /// Create from parameter name, parameter type, and parameter position.
        ///
        /// This constructor is private. Use new_ParameterInfo(...)
        /// function with matching signature instead.
        /// </summary>
        ParameterInfoImpl(String name, Type parameterType, int position)
            : ParameterType(parameterType)
            , Name(name)
            , Position(position)
        {}
    };

    /// <summary>
    /// Create from parameter name, parameter type, and parameter position.
    /// </summary>
    inline ParameterInfo new_ParameterInfo(String name, Type parameterType, int position)
    {
        return new ParameterInfoImpl(name, parameterType, position);
    }
}