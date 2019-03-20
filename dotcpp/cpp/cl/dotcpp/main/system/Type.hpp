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

#include <cl/dotcpp/main/system/Object.hpp>
#include <cl/dotcpp/main/system/String.hpp>

namespace cl
{
    class StringImpl; class String;
    class TypeImpl; using Type = Ptr<TypeImpl>;
    class TypeDataImpl; using TypeData = Ptr<TypeDataImpl>;
    class StringImpl; class String;
    class MethodInfoImpl; using MethodInfo = Ptr<MethodInfoImpl>;
    class PropertyInfoImpl; using PropertyInfo = Ptr<PropertyInfoImpl>;
    template <class T> class ListImpl; template <class T> using List = Ptr<ListImpl<T>>;
    template <class T> class Array1DImpl; template <class T> using Array1D = Ptr<Array1DImpl<T>>;

    /// <summary>Builder for Type.</summary>
    class CL_DOTCPP_MAIN TypeDataImpl final : public virtual ObjectImpl
    {
        friend TypeData new_TypeData();
        friend class TypeImpl;

    private:
        String name_;
        String namespace_;
        List<PropertyInfo> properties_;
        List<MethodInfo> methods_;

    public: // METHODS

        /// <summary>Set the name of the current type, excluding namespace.</summary>
        TypeData WithName(const String& name);

        /// <summary>Set the namespace of the Type.</summary>
        TypeData WithNamespace(const String& ns);

    public: // METHODS

        /// <summary>Add public property of the current Type.</summary>
        TypeData WithProperty();

        /// <summary>Add public method of the current Type.</summary>
        TypeData WithMethod();

        /// <summary>Built Type from the current object.</summary>
        Type Build();

    private: // CONSTRUCTORS

        /// <summary>
        /// Create an empty instance of TypeData.
        ///
        /// This constructor is private. Use new_TypeData() function instead.
        /// </summary>
        TypeDataImpl() = default;
    };

    /// <summary>
    /// Create an empty instance of TypeData.
    /// </summary>
    inline TypeData new_TypeData() { return new TypeDataImpl(); }

    /// <summary>
    /// Represents type declarations: class types, interface types, array types, value types, enumeration types,
    /// type parameters, generic type definitions, and open or closed constructed generic types.
    ///
    /// Type is the root of the System.Reflection functionality and is the primary way to access metadata.
    /// Use the members of Type to get information about a type declaration, about the members of a type
    /// (such as the constructors, methods, fields, properties, and events of a class), as well as the module
    /// and the assembly in which the class is deployed.
    ///
    /// The Type object associated with a particular type can be obtained in the following ways:
    ///
    /// \begin{itemize}
    ///
    /// \item The instance Object.GetType method returns a Type object that represents the type of an instance.
    /// Because all managed types derive from Object, the GetType method can be called on an instance of any type.
    ///
    /// \item The typeof method obtains the Type object for the argument type.
    ///
    /// \end{itemize}
    /// </summary>
    class CL_DOTCPP_MAIN TypeImpl final : public virtual ObjectImpl
    {
        friend class TypeDataImpl;

    private: // FIELDS

        Array1D<PropertyInfo> properties_;
        Array1D<MethodInfo> methods_;

    public: // PROPERTIES

        /// <summary>Gets the name of the current type, excluding namespace.</summary>
        DOT_AUTO_GET(TypeImpl, String, Name);

        /// <summary>Gets the fully qualified name of the type, including its namespace but not its assembly.</summary>
        DOT_AUTO_GET(TypeImpl, String, Namespace);

    public: // METHODS

        /// <summary>Returns all the public properties of the current Type.</summary>
        virtual Array1D<PropertyInfo> GetProperties() { return properties_; }

        /// <summary>Returns methods of the current type.</summary>
        virtual Array1D<MethodInfo> GetMethods() { return methods_; }

        /// <summary>A string representing the name of the current type.</summary>
        virtual String ToString() const { return "Type"; } // TODO - return name

    private: // CONSTRUCTORS

        /// <summary>
        /// Create from builder.
        ///
        /// This constructor is private. Use TypeBuilder->Build() method instead.
        /// </summary>
        TypeImpl(const TypeData& data)
            : Name(data->name_)
            , Namespace(data->namespace_)
        {}
    };

    /// <summary>Get Type object for the argument.</summary>
    template <class T>
    Type typeof() { return T::typeof(); }

    /// <summary>
    /// Initializes a new instance of the Type class for untyped instance of Object.
    /// </summary>
    inline Type ObjectImpl::GetType()
    {
        return new_TypeData()->WithName("Object")->WithNamespace("System")->Build();
    }

    template <>
    inline Type typeof<String>() { return new_TypeData()->WithName("String")->WithNamespace("System")->Build(); }

    template <>
    inline Type typeof<double>() { return new_TypeData()->WithName("Double")->WithNamespace("System")->Build(); }

    template <>
    inline Type typeof<int64_t>() { return new_TypeData()->WithName("Int64")->WithNamespace("System")->Build(); }

    template <>
    inline Type typeof<int>() { return new_TypeData()->WithName("Int32")->WithNamespace("System")->Build(); }
}
