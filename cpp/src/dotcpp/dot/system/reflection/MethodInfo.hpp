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
#include <dot/detail/traits.hpp>

namespace dot
{
    class MethodInfoImpl; using MethodInfo = ptr<MethodInfoImpl>;
    class type_impl; using type_t = ptr<type_impl>;

    /// <summary>
    /// Obtains information about the attributes of a method and provides access to method metadata.
    /// </summary>
    class MethodInfoImpl : public MemberInfoImpl
    {
        friend class TypeBuilderImpl;

        typedef MethodInfoImpl self;

    public: // METHODS

        /// <summary>A string representing the name of the current type.</summary>
        virtual string to_string() override { return "MethodInfo"; }

        /// <summary>Gets the parameters of this method.</summary>
        virtual Array1D<ParameterInfo> GetParameters()
        {
            return Parameters;
        }

        /// <summary>Invokes specified method with given parameters.</summary>
        virtual object Invoke(object, Array1D<object>) = 0;

        /// <summary>Gets the return type of this method.</summary>
        type_t ReturnType; // TODO - convert to method

    protected: // FIELDS

        Array1D<ParameterInfo> Parameters;

    protected: // CONSTRUCTORS

        /// <summary>
        /// Create from method name, declaring type, return type.
        ///
        /// This constructor is protected. It is used by derived classes only.
        /// </summary>
        MethodInfoImpl(const string& name, type_t declaringType, type_t returnType)
            : MemberInfoImpl(name, declaringType)
        {
            ReturnType = returnType;
        }
    };

    /// <summary>
    /// Obtains information about the attributes of a non-static method and provides access to method metadata.
    /// </summary>
    template <class Class, class Return, class ... Args>
    class MemberMethodInfoImpl : public MethodInfoImpl
    {
        friend class TypeBuilderImpl;
        typedef Return (Class::*method_type)(Args...);

    private: // FIELDS

        /// <summary>C++ function pointer type for the method.</summary>
        method_type ptr_;

    public: // METHODS

        /// <summary>A string representing the name of the current type.</summary>
        virtual string to_string() override { return "MemberMethodInfo"; }

        /// <summary>Invokes the method reflected by this MethodInfo instance.</summary>
        template <int ... I>
        object Invoke_impl(object obj, Array1D<object> params, detail::index_sequence<I...>, std::false_type)
        {
            return ((*ptr<Class>(obj)).*ptr_)(params[I]...);
        }

        /// <summary>Invokes the method reflected by this MethodInfo instance.</summary>
        template <int ... I>
        object Invoke_impl(object obj, Array1D<object> params, detail::index_sequence<I...>, std::true_type)
        {
            ((*ptr<Class>(obj)).*ptr_)(params[I]...);
            return object();
        }

        /// <summary>Invokes the method reflected by this MethodInfo instance.</summary>
        virtual object Invoke(object obj, Array1D<object> params)
        {
            if (params->count() != Parameters->count())
                throw new_Exception("Wrong number of parameters for method " + this->DeclaringType->Name + "." + this->Name);

            return Invoke_impl(obj, params, typename detail::make_index_sequence<sizeof...(Args)>::type(), typename std::is_same<Return, void>::type());
        }

    private: // CONSTRUCTORS

        /// <summary>
        /// Create from method name, declaring type, return type, and pointer to method.
        ///
        /// This constructor is private. Use new_MethodInfo(...)
        /// function with matching signature instead.
        /// </summary>
        MemberMethodInfoImpl(const string& name, type_t declaringType, type_t returnType, method_type p)
            : MethodInfoImpl(name, declaringType, returnType)
            , ptr_(p)
        {}
    };

    /// <summary>
    /// Obtains information about the attributes of a static method and provides access to method metadata.
    /// </summary>
    template <class Return, class ... Args>
    class StaticMethodInfoImpl : public MethodInfoImpl
    {
        friend class TypeBuilderImpl;
        typedef Return (*method_type)(Args...);

    private: // FIELDS

        method_type ptr_;

    public: // METHODS

        /// <summary>A string representing the name of the current type.</summary>
        virtual string to_string() override { return "StaticMethodInfo"; }

        /// <summary>Invokes the method reflected by this MethodInfo instance.</summary>
        template <int ... I>
        object Invoke_impl(object obj, Array1D<object> params, detail::index_sequence<I...>, std::false_type)
        {
            return (*ptr_)(params[I]...);
        }

        /// <summary>Invokes the method reflected by this MethodInfo instance.</summary>
        template <int ... I>
        object Invoke_impl(object obj, Array1D<object> params, detail::index_sequence<I...>, std::true_type)
        {
            (*ptr_)(params[I]...);
            return object();
        }

        /// <summary>Invokes the method reflected by this MethodInfo instance.</summary>
        virtual object Invoke(object obj, Array1D<object> params)
        {
            if (params->count() != Parameters->count())
                throw new_Exception("Wrong number of parameters for method " + this->DeclaringType->Name + "." + this->Name);

            return Invoke_impl(obj, params, typename detail::make_index_sequence<sizeof...(Args)>::type(), typename std::is_same<Return, void>::type());
        }

    private: // CONSTRUCTORS

        /// <summary>
        /// Create from method name, declaring type, return type, and pointer to method.
        ///
        /// This constructor is private. Use new_MethodInfo(...)
        /// function with matching signature instead.
        /// </summary>
        StaticMethodInfoImpl(const string& name, type_t declaringType, type_t returnType, method_type p)
            : MethodInfoImpl(name, declaringType, returnType)
            , ptr_(p)
        {}
    };
}
