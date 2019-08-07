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
#include <dot/detail/traits.hpp>

namespace dot
{
    class method_info_impl; using method_info = ptr<method_info_impl>;
    class type_impl; using type_t = ptr<type_impl>;

    /// Obtains information about the attributes of a method and provides access to method metadata.
    class method_info_impl : public member_info_impl
    {
        friend class type_builder_impl;

        typedef method_info_impl self;

    public: // METHODS

        /// A string representing the name of the current type.
        virtual string to_string() override { return "MethodInfo"; }

        /// Gets the parameters of this method.
        virtual list<parameter_info> GetParameters()
        {
            return parameters;
        }

        /// Invokes specified method with given parameters.
        virtual object invoke(object, list<object>) = 0;

        /// Gets the return type of this method.
        type_t return_type; // TODO - convert to method

    protected: // FIELDS

        list<parameter_info> parameters;

    protected: // CONSTRUCTORS

        /// Create from method name, declaring type, return type.
        ///
        /// This constructor is protected. It is used by derived classes only.
        method_info_impl(const string& name, type_t declaring_type, type_t return_type)
            : member_info_impl(name, declaring_type)
        {
            this->return_type = return_type;
        }
    };

    /// Obtains information about the attributes of a non-static method and provides access to method metadata.
    template <class class_, class return_t, class ... args>
    class member_method_info_impl : public method_info_impl
    {
        friend class type_builder_impl;
        typedef return_t (class_::*method_type)(args...);

    private: // FIELDS

        /// C++ function pointer type for the method.
        method_type ptr_;

    public: // METHODS

        /// A string representing the name of the current type.
        virtual string to_string() override { return "MemberMethodInfo"; }

        /// Invokes the method reflected by this method_info instance.
        template <int ... I>
        object invoke_impl(object obj, list<object> params, detail::index_sequence<I...>, std::false_type)
        {
            return ((*ptr<class_>(obj)).*ptr_)(params[I]...);
        }

        /// Invokes the method reflected by this method_info instance.
        template <int ... I>
        object invoke_impl(object obj, list<object> params, detail::index_sequence<I...>, std::true_type)
        {
            ((*ptr<class_>(obj)).*ptr_)(params[I]...);
            return object();
        }

        /// Invokes the method reflected by this MethodInfo instance.
        virtual object invoke(object obj, list<object> params)
        {
            if (params->count() != parameters->count())
                throw exception("Wrong number of parameters for method " + this->declaring_type->name + "." + this->name);

            return invoke_impl(obj, params, typename detail::make_index_sequence<sizeof...(args)>::type(), typename std::is_same<return_t, void>::type());
        }

    private: // CONSTRUCTORS

        /// Create from method name, declaring type, return type, and pointer to method.
        ///
        /// This constructor is private. Use make_MethodInfo(...)
        /// function with matching signature instead.
        member_method_info_impl(const string& name, type_t declaring_type, type_t return_type, method_type p)
            : method_info_impl(name, declaring_type, return_type)
            , ptr_(p)
        {}
    };

    /// Obtains information about the attributes of a static method and provides access to method metadata.
    template <class return_t, class ... args>
    class static_method_info_impl : public method_info_impl
    {
        friend class type_builder_impl;
        typedef return_t (*method_type)(args...);

    private: // FIELDS

        method_type ptr_;

    public: // METHODS

        /// A string representing the name of the current type.
        virtual string to_string() override { return "StaticMethodInfo"; }

        /// Invokes the method reflected by this MethodInfo instance.
        template <int ... I>
        object invoke_impl(object obj, list<object> params, detail::index_sequence<I...>, std::false_type)
        {
            return (*ptr_)(params[I]...);
        }

        /// Invokes the method reflected by this MethodInfo instance.
        template <int ... I>
        object invoke_impl(object obj, list<object> params, detail::index_sequence<I...>, std::true_type)
        {
            (*ptr_)(params[I]...);
            return object();
        }

        /// Invokes the method reflected by this MethodInfo instance.
        virtual object invoke(object obj, list<object> params)
        {
            if (params->count() != parameters->count())
                throw exception("Wrong number of parameters for method " + this->declaring_type->name + "." + this->name);

            return invoke_impl(obj, params, typename detail::make_index_sequence<sizeof...(args)>::type(), typename std::is_same<return_t, void>::type());
        }

    private: // CONSTRUCTORS

        /// Create from method name, declaring type, return type, and pointer to method.
        ///
        /// This constructor is private. Use make_MethodInfo(...)
        /// function with matching signature instead.
        static_method_info_impl(const string& name, type_t declaring_type, type_t return_type, method_type p)
            : method_info_impl(name, declaring_type, return_type)
            , ptr_(p)
        {}
    };
}
