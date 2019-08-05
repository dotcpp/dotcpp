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

#include <dot/system/reflection/MemberInfo.hpp>
#include <dot/system/reflection/ParameterInfo.hpp>
#include <dot/system/Exception.hpp>

namespace dot
{
    class constructor_info_impl; using constructor_info = ptr<constructor_info_impl>;
    class type_impl; using type_t = ptr<type_impl>;

    /// <summary>
    /// Obtains information about the attributes of a constructor and provides access to constructor metadata.
    /// </summary>
    class constructor_info_impl : public member_info_impl
    {
        friend class type_builder_impl;

    public: // METHODS

        /// <summary>A string representing the name of the current type.</summary>
        virtual string to_string() override { return "ConstructorInfo"; }

        /// <summary>Gets the parameters of this constructor.</summary>
        virtual array<parameter_info> get_parameters()
        {
            return parameters;
        }

        /// <summary>Invokes specified constructor with given parameters.</summary>
        virtual object invoke(array<object>) = 0;

    protected: // CONSTRUCTORS

        array<parameter_info> parameters;

        /// <summary>
        /// Create from declaring type
        ///
        /// This constructor is protected. It is used by derived classes only.
        /// </summary>
        constructor_info_impl(type_t declaring_type)
            : member_info_impl(".ctor", declaring_type)
        {}
    };

    /// <summary>
    /// Obtains information about the attributes of a constructor and provides access to constructor metadata.
    /// </summary>
    template <class class_, class ... args>
    class member_constructor_info_impl : public constructor_info_impl
    {

        friend class type_builder_impl;
        typedef class_(*ctor_type)(args...);

    private: // FIELDS

        ctor_type ptr_;

    public: // METHODS

        /// <summary>A string representing the name of the current type.</summary>
        virtual string to_string() override { return "MemberConstructorInfo"; }

        /// <summary>Invokes the constructor reflected by this ConstructorInfo instance.</summary>
        template <int ... I>
        object invoke_impl(array<object> params, detail::index_sequence<I...>)
        {
            return (*ptr_)(params[I]...);
        }

        /// <summary>Invokes the constructor reflected by this ConstructorInfo instance.</summary>
        virtual object invoke(array<object> params)
        {
            if ((params.IsEmpty() && parameters->count() != 0) || (!params.IsEmpty() && (params->count() != parameters->count())))
                throw exception("Wrong number of parameters for constructor " + this->declaring_type->name + "." + this->name);

            return invoke_impl(params, typename detail::make_index_sequence<sizeof...(args)>::type());
        }

    private: // CONSTRUCTORS

        /// <summary>
        /// Create from declaring type, and pointer to constructor.
        ///
        /// This constructor is private. Use new_ConstructorInfo(...)
        /// function with matching signature instead.
        /// </summary>
        member_constructor_info_impl(type_t declaring_type, ctor_type p)
            : constructor_info_impl(declaring_type)
            , ptr_(p)
        {}
    };
}