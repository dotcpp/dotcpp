/*
Copyright (C) 2015-present The DotCpp Authors.

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

#include <dot/system/reflection/member_info.hpp>

namespace dot
{
    class parameter_info_impl; using parameter_info = ptr<parameter_info_impl>;

    /// Discovers the attributes of a parameter and provides access to parameter metadata.
    class parameter_info_impl : public virtual object_impl
    {
        friend parameter_info make_parameter_info(string , type, int);

        typedef parameter_info_impl self;

    public: // METHODS

        /// Gets the type of this parameter.
        type parameter_type; // TODO - convert to method

        /// Gets the name of this parameter.
        string name;  // TODO - convert to method

        /// Gets the zero-based position of the parameter in the formal parameter list.
        int position;  // TODO - convert to method

    private: // CONSTRUCTORS

        /// Create from parameter name, parameter type, and parameter position.
        ///
        /// This constructor is private. Use make_ParameterInfo(...)
        /// function with matching signature instead.
        parameter_info_impl(string name, type parameter_type, int position)
        {
            this->parameter_type = parameter_type;
            this->name = name;
            this->position = position;
        }
    };

    /// Create from parameter name, parameter type, and parameter position.
    inline parameter_info make_parameter_info(string name, type parameter_type, int position)
    {
        return new parameter_info_impl(name, parameter_type, position);
    }
}