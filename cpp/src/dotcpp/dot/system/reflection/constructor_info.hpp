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
#include <dot/system/reflection/parameter_info.hpp>
#include <dot/system/exception.hpp>

namespace dot
{
    class constructor_info_impl; using constructor_info = ptr<constructor_info_impl>;
    class type_impl; using type_t = ptr<type_impl>;

    /// Obtains information about the attributes of a constructor and provides access to constructor metadata.
    class constructor_info_impl : public member_info_impl
    {
        friend class type_builder_impl;

    public: // METHODS

        /// A string representing the name of the current type.
        virtual string to_string() override { return "ConstructorInfo"; }

        /// Gets the parameters of this constructor.
        virtual list<parameter_info> get_parameters()
        {
            return parameters;
        }

        /// Invokes specified constructor with given parameters.
        virtual object invoke(list<object>) = 0;

    protected: // CONSTRUCTORS

        list<parameter_info> parameters;

        /// Create from declaring type
        ///
        /// This constructor is protected. It is used by derived classes only.
        constructor_info_impl(type_t declaring_type)
            : member_info_impl(".ctor", declaring_type)
        {}
    };

    /// Obtains information about the attributes of a constructor and provides access to constructor metadata.
    template <class class_, class ... args>
    class member_constructor_info_impl : public constructor_info_impl
    {

        friend class type_builder_impl;
        typedef class_(*ctor_type)(args...);

    private: // FIELDS

        ctor_type ptr_;

    public: // METHODS

        /// A string representing the name of the current type.
        virtual string to_string() override { return "MemberConstructorInfo"; }

        /// Invokes the constructor reflected by this ConstructorInfo instance.
        template <int ... I>
        object invoke_impl(list<object> params, detail::index_sequence<I...>)
        {
            return (*ptr_)(params[I]...);
        }

        /// Invokes the constructor reflected by this ConstructorInfo instance.
        virtual object invoke(list<object> params)
        {
            if ((params.is_empty() && parameters->count() != 0) || (!params.is_empty() && (params->count() != parameters->count())))
                throw exception("Wrong number of parameters for constructor " + this->declaring_type->name + "." + this->name);

            return invoke_impl(params, typename detail::make_index_sequence<sizeof...(args)>::index_type());
        }

    private: // CONSTRUCTORS

        /// Create from declaring type, and pointer to constructor.
        ///
        /// This constructor is private. Use make_ConstructorInfo(...)
        /// function with matching signature instead.
        member_constructor_info_impl(type_t declaring_type, ctor_type p)
            : constructor_info_impl(declaring_type)
            , ptr_(p)
        {}
    };
}