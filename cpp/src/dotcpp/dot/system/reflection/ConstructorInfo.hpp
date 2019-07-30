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
    class ConstructorInfoImpl; using ConstructorInfo = ptr<ConstructorInfoImpl>;
    class type_impl; using type_t = ptr<type_impl>;

    /// <summary>
    /// Obtains information about the attributes of a constructor and provides access to constructor metadata.
    /// </summary>
    class ConstructorInfoImpl : public MemberInfoImpl
    {
        friend class TypeBuilderImpl;

    public: // METHODS

        /// <summary>A string representing the name of the current type.</summary>
        virtual string to_string() override { return "ConstructorInfo"; }

        /// <summary>Gets the parameters of this constructor.</summary>
        virtual Array1D<ParameterInfo> GetParameters()
        {
            return Parameters;
        }

        /// <summary>Invokes specified constructor with given parameters.</summary>
        virtual object Invoke(Array1D<object>) = 0;

    protected: // CONSTRUCTORS

        Array1D<ParameterInfo> Parameters;

        /// <summary>
        /// Create from declaring type
        ///
        /// This constructor is protected. It is used by derived classes only.
        /// </summary>
        ConstructorInfoImpl(type_t declaringType)
            : MemberInfoImpl(".ctor", declaringType)
        {}
    };

    /// <summary>
    /// Obtains information about the attributes of a constructor and provides access to constructor metadata.
    /// </summary>
    template <class Class, class ... Args>
    class MemberConstructorInfoImpl : public ConstructorInfoImpl
    {

        friend class TypeBuilderImpl;
        typedef Class(*ctor_type)(Args...);

    private: // FIELDS

        ctor_type ptr_;

    public: // METHODS

        /// <summary>A string representing the name of the current type.</summary>
        virtual string to_string() override { return "MemberConstructorInfo"; }

        /// <summary>Invokes the constructor reflected by this ConstructorInfo instance.</summary>
        template <int ... I>
        object Invoke_impl(Array1D<object> params, detail::index_sequence<I...>)
        {
            return (*ptr_)(params[I]...);
        }

        /// <summary>Invokes the constructor reflected by this ConstructorInfo instance.</summary>
        virtual object Invoke(Array1D<object> params)
        {
            if ((params.IsEmpty() && Parameters->count() != 0) || (!params.IsEmpty() && (params->count() != Parameters->count())))
                throw new_Exception("Wrong number of parameters for constructor " + this->DeclaringType->Name + "." + this->Name);

            return Invoke_impl(params, typename detail::make_index_sequence<sizeof...(Args)>::type());
        }

    private: // CONSTRUCTORS

        /// <summary>
        /// Create from declaring type, and pointer to constructor.
        ///
        /// This constructor is private. Use new_ConstructorInfo(...)
        /// function with matching signature instead.
        /// </summary>
        MemberConstructorInfoImpl(type_t declaringType, ctor_type p)
            : ConstructorInfoImpl(declaringType)
            , ptr_(p)
        {}
    };
}