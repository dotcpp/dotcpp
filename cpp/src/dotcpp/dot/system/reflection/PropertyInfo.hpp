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
    class PropertyInfoImpl; using PropertyInfo = ptr<PropertyInfoImpl>;
    template <class PropType, class Class> class PropertyInfoDataImpl; template <class PropType, class Class> using PropertyInfoData = ptr<PropertyInfoDataImpl<PropType, Class>>;

    /// <summary>Data for PropertyInfo.</summary>
    template <class PropType, class Class>
    class DOT_CLASS PropertyInfoDataImpl final : public MemberInfoDataImpl
    {
        typedef PropertyInfoDataImpl self;

    public: // PROPERTIES

        /// <summary>type_t of this property.</summary>
        DOT_AUTO_PROP(type_t, PropertyType)

        /// <summary>Property pointer.</summary>
        DOT_AUTO_PROP(PropType Class::*, PropertyPointer)

    private: // CONSTRUCTORS

        /// <summary>
        /// Create an empty instance of PropertyInfoData.
        ///
        /// This constructor is private. Use make_type_builder() function instead.
        /// </summary>
        PropertyInfoDataImpl() = default;
    };

    /// <summary>
    /// Create an empty instance of PropertyInfoData.
    /// </summary>
    template <class PropType, class Class>
    PropertyInfoData<PropType, Class> new_PropertyInfoData() { return new PropertyInfoDataImpl<PropType, Class>(); }

    /// <summary>
    /// Discovers the attributes of a property and provides access to property metadata.
    /// </summary>
    class PropertyInfoImpl : public MemberInfoImpl
    {
        typedef PropertyInfoImpl self;

    public: // METHODS

        /// <summary>Gets the type of this property.</summary>
        type_t PropertyType; // TODO - convert to method

        /// <summary>A string representing the name of the current type.</summary>
        virtual string to_string() override { return "PropertyInfo"; }

        /// <summary>Returns the property value of a specified object.</summary>
        virtual object GetValue(object obj) = 0;

        /// <summary>Sets the property value of a specified object.</summary>
        virtual void SetValue(object obj, object value) = 0;

    protected: // CONSTRUCTORS

        /// <summary>
        /// Create from field name, declaring type, property type,
        /// and base class for the pointer to property.
        ///
        /// This constructor is protected. It is used by derived classes only.
        /// </summary>
        PropertyInfoImpl(string name, type_t declaringType, type_t propertyType)
            : MemberInfoImpl(name, declaringType)
        {
            PropertyType = propertyType;
        }
    };

    /// <summary>
    /// Implementation of PropertyInfo for property defined as a field (member variable).
    /// </summary>
    template <class PropType, class Class>
    class PropertyInfoFieldImpl : public PropertyInfoImpl
    {
        typedef PropType Class::* property_ptr_type;

        template <class PropType1, class Class1>
        friend PropertyInfo new_PropertyInfo(string, type_t, type_t, PropType1 Class1::*
            , typename std::enable_if<!std::is_base_of<detail::decl_get, PropType>::value>::type *);

    private: // FIELDS

        /// <summary>Pointer to property defined as a field.</summary>
        property_ptr_type prop_;

    private: // CONSTRUCTORS

        /// <summary>
        /// Create from field name, declaring type, property type,
        /// and pointer to property defined as a field (member variable).
        ///
        /// This constructor is private. Use new_PropertyInfo(...)
        /// function with matching signature instead.
        /// </summary>
        PropertyInfoFieldImpl(string name, type_t declaringType, type_t propertyType, property_ptr_type prop)
            : PropertyInfoImpl(name, declaringType, propertyType)
            , prop_(prop)
        {}

    private: // METHODS

        /// <summary>Returns the property value of a specified object.</summary>
        virtual object GetValue(object obj) override
        {
            return (*ptr<Class>(obj)).*prop_;
        }

        /// <summary>Sets the property value of a specified object.</summary>
        virtual void SetValue(object obj, object value) override
        {
            (*ptr<Class>(obj)).*prop_ = (PropType)value;
        }
    };

    /// <summary>
    /// Create from field name, declaring type, property type,
    /// and pointer to property defined as a field (member variable).
    /// </summary>
    template <class PropType, class Class>
    PropertyInfo new_PropertyInfo(string name, type_t declaringType, type_t propertyType, PropType Class::* prop
        , typename std::enable_if<!std::is_base_of<detail::decl_get, PropType>::value>::type * p = 0)
    {
        return new PropertyInfoFieldImpl<PropType, Class>(name, declaringType, propertyType, prop);
    }

    class TypeBuilderImpl;

    /// <summary>
    /// Implementation of PropertyInfo for a property defined using a macro.
    /// </summary>
    template <class PropType, class Class>
    class PropertyInfoPropertyImpl : public PropertyInfoImpl
    {
        typedef PropType Class::* property_ptr_type;

        template <class PropType1, class Class1>
        friend PropertyInfo new_PropertyInfo(string, type_t, type_t, PropType1 Class1::*
            , typename std::enable_if<std::is_base_of<detail::decl_get, PropType>::value>::type *);
        friend TypeBuilderImpl;

    public: // FIELDS //! TODO make private

        /// <summary>Pointer to property defined using a macro.</summary>
        property_ptr_type prop_;

    private: // CONSTRUCTORS

        /// <summary>
        /// Create from field name, declaring type, property type,
        /// and pointer to property defined using a macro.
        ///
        /// This constructor is private. Use new_PropertyInfo(...)
        /// function with matching signature instead.
        /// </summary>
        PropertyInfoPropertyImpl(string name, type_t declaringType, type_t propertyType, property_ptr_type prop)
            : PropertyInfoImpl(name, declaringType, propertyType)
            , prop_(prop)
        {}

        /// <summary>Returns the property value of a specified object.</summary>
        virtual object GetValue(object obj) override
        {
            return (typename PropType::value_type)((*ptr<Class>(obj)).*prop_);
        }

        // Prop has operator =
        void SetValue_impl(object obj, object value, std::true_type)
        {
            (*ptr<Class>(obj)).*prop_ = (typename PropType::value_type)(value);
        }

        // Prop does not have operator =
        void SetValue_impl(object obj, object value, std::false_type)
        {
            throw new_Exception("Attempting to use SetValue on read-only property.");
        }

        // Property might be read-only (operator =(value) = delete; )
        // SetValue throws exception in case of setting read-only DOT_PROP
        virtual void SetValue(object obj, object value) override
        {
            SetValue_impl(obj, value, typename std::is_base_of<detail::decl_prop, PropType>::type());
        }
    };

    /// <summary>
    /// Create from field name, declaring type, property type,
    /// and pointer to property defined using a macro.
    /// </summary>
    template <class PropType, class Class>
    PropertyInfo new_PropertyInfo(string name, type_t declaringType, type_t propertyType, PropType Class::* prop
        , typename std::enable_if<std::is_base_of<detail::decl_get, PropType>::value>::type * p = 0)
    {
        return new PropertyInfoPropertyImpl<PropType, Class>(name, declaringType, propertyType, prop);
    }
}
