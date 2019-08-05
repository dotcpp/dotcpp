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

#include <dot/system/Exception.hpp>
#include <dot/system/reflection/MemberInfo.hpp>

namespace dot
{
    class field_info_base_impl; using field_info = ptr<field_info_base_impl>;

    /// <summary>
    /// Discovers the attributes of a field and provides access to field metadata.
    /// </summary>
    class field_info_base_impl : public member_info_impl
    {
        typedef field_info_base_impl self;

    public: // METHODS

        /// <summary>Gets the type of this field.</summary>
        type_t field_type;

        /// <summary>A string representing the name of the current type.</summary>
        virtual string to_string() override { return "field_info"; }

        /// <summary>Returns the field value of a specified object.</summary>
        virtual object get_value(object obj) = 0;

        /// <summary>Sets the field value of a specified object.</summary>
        virtual void set_value(object obj, object value) = 0;

    protected: // CONSTRUCTORS

        /// <summary>
        /// Create from field name, declaring type, field type,
        /// and base class for the pointer to field.
        ///
        /// This constructor is protected. It is used by derived classes only.
        /// </summary>
        field_info_base_impl(string name, type_t declaring_type, type_t field_type)
            : member_info_impl(name, declaring_type)
        {
            this->field_type = field_type;
        }
    };

    /// <summary>
    /// Implementation of field_info for field defined as a field (member variable).
    /// </summary>
    template <class field_type_t, class class_>
    class field_info_impl : public field_info_base_impl
    {
        typedef field_type_t class_::* field_ptr_type;

        template <class field_type_, class class__>
        friend field_info make_field_info(string, type_t, type_t, field_type_ class__::*);

    public: // FIELDS

        /// <summary>Pointer to field defined as a field.</summary>
        field_ptr_type field_;

    private: // CONSTRUCTORS

        /// <summary>
        /// Create from field name, declaring type, field type,
        /// and pointer to field defined as a field (member variable).
        ///
        /// This constructor is private. Use make_field_info(...)
        /// function with matching signature instead.
        /// </summary>
        field_info_impl(string name, type_t declaring_type, type_t field_type, field_ptr_type field)
            : field_info_base_impl(name, declaring_type, field_type)
            , field_(field)
        {}

    private: // METHODS

        /// <summary>Returns the field value of a specified object.</summary>
        virtual object get_value(object obj) override
        {
            return (*ptr<class_>(obj)).*field_;
        }

        /// <summary>Sets the field value of a specified object.</summary>
        virtual void set_value(object obj, object value) override
        {
            (*ptr<class_>(obj)).*field_ = (field_type_t)value;
        }
    };

    /// <summary>
    /// Create from field name, declaring type, field type,
    /// and pointer to field defined as a field (member variable).
    /// </summary>
    template <class field_type_t, class class_>
    field_info make_field_info(string name, type_t declaring_type, type_t field_type, field_type_t class_::* field)
    {
        return new field_info_impl<field_type_t, class_>(name, declaring_type, field_type, field);
    }

    class type_builder_impl;

}