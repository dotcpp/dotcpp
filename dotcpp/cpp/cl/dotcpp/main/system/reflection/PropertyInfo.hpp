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
    class PropertyInfoImpl; using PropertyInfo = Ptr<PropertyInfoImpl>;

    /// <summary>
    /// Discovers the attributes of a property and provides access to property metadata.
    /// </summary>
    class PropertyInfoImpl : public MemberInfoImpl
    {
    public: // METHODS

        /// <summary>Gets the type of this property.</summary>
        DOT_AUTO_GET(PropertyInfoImpl, Type, PropertyType)

        /// <summary>A string representing the name of the current type.</summary>
        virtual String ToString() const { return "PropertyInfo"; }

        /// <summary>Returns the property value of a specified object.</summary>
        virtual Object GetValue(Object obj) = 0;

        /// <summary>Sets the property value of a specified object.</summary>
        virtual void SetValue(Object obj, Object value) = 0;

    protected: // CONSTRUCTORS

        /// <summary>
        /// Create from field name, declaring type, property type,
        /// and base class for the pointer to property.
        ///
        /// This constructor is protected. It is used by derived classes only.
        /// </summary>
        PropertyInfoImpl(String name, Type declaringType, Type propertyType)
            : MemberInfoImpl(name, declaringType)
            , PropertyType(propertyType)
        {}
    };

    /// <summary>
    /// Implementation of PropertyInfo for property defined as a field (member variable).
    /// </summary>
    template <class PropType, class Class>
    class PropertyInfoFieldImpl : public PropertyInfoImpl
    {
        typedef PropType Class::* property_ptr_type;

        template <class PropType, class Class>
        friend PropertyInfo new_PropertyInfo(String , Type , Type , PropType Class::*
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
        PropertyInfoFieldImpl(String name, Type declaringType, Type propertyType, property_ptr_type prop)
            : PropertyInfoImpl(name, declaringType, propertyType)
            , prop_(prop)
        {}

    private: // METHODS

        /// <summary>Returns the property value of a specified object.</summary>
        virtual Object GetValue(Object obj) override
        {
            return (*Ptr<Class>(obj)).*prop_;
        }

        /// <summary>Sets the property value of a specified object.</summary>
        virtual void SetValue(Object obj, Object value) override
        {
            (*Ptr<Class>(obj)).*prop_ = (PropType)value;
        }
    };

    /// <summary>
    /// Create from field name, declaring type, property type,
    /// and pointer to property defined as a field (member variable).
    /// </summary>
    template <class PropType, class Class>
    PropertyInfo new_PropertyInfo(String name, Type declaringType, Type propertyType, PropType Class::* prop
        , typename std::enable_if<!std::is_base_of<detail::decl_get, PropType>::value>::type * p = 0)
    {
        return new PropertyInfoFieldImpl<PropType, Class>(name, declaringType, propertyType, prop);
    }

    /// <summary>
    /// Implementation of PropertyInfo for a property defined using a macro.
    /// </summary>
    template <class PropType, class Class>
    class PropertyInfoPropertyImpl : public PropertyInfoImpl
    {
        typedef PropType Class::* property_ptr_type;

        template <class PropType, class Class>
        friend PropertyInfo new_PropertyInfo(String, Type, Type, PropType Class::*
            , typename std::enable_if<std::is_base_of<detail::decl_get, PropType>::value>::type *);

    private: // FIELDS

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
        PropertyInfoPropertyImpl(String name, Type declaringType, Type propertyType, property_ptr_type prop)
            : PropertyInfoImpl(name, declaringType, propertyType)
            , prop_(prop)
        {}

        /// <summary>Returns the property value of a specified object.</summary>
        virtual Object GetValue(Object obj) override
        {
            return (PropType::value_type)((*obj.cast<Ptr<Class>>()).*prop_);
        }

        // Prop has operator =
        void SetValue_impl(Object obj, Object value, std::true_type)
        {
            (*obj.cast<Ptr<Class>>()).*prop_ = (PropType::value_type)value;
        }

        // Prop does not have operator =
        void SetValue_impl(Object obj, Object value, std::false_type)
        {
            throw Exception("Attempting to use SetValue on read-only property.");
        }

        // Property might be read-only (operator =(value) = delete; )
        // SetValue throws exception in case of setting read-only DOT_PROP
        virtual void SetValue(Object obj, Object value) override
        {
            SetValue_impl(obj, value, std::is_base_of<detail::decl_prop, PropType>::type());
        }
    };

    /// <summary>
    /// Create from field name, declaring type, property type,
    /// and pointer to property defined using a macro.
    /// </summary>
    template <class PropType, class Class>
    PropertyInfo new_PropertyInfo(String name, Type declaringType, Type propertyType, PropType Class::* prop
        , typename std::enable_if<std::is_base_of<detail::decl_get, PropType>::value>::type * p = 0)
    {
        return new PropertyInfoPropertyImpl<PropType, Class>(name, declaringType, propertyType, prop);
    }
}
