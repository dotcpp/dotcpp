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

namespace cl
{
    class TypeImpl; using Type = Ptr<TypeImpl>;
    class StringImpl; using String = Ptr<StringImpl>;
    class PropertyInfoImpl; using PropertyInfo = Ptr<PropertyInfoImpl>;
    template <class T> class Array1DImpl; template <class T> using Array1D = Ptr<Array1DImpl<T>>;

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
    class TypeImpl : public virtual ObjectImpl
    {
        friend Type new_Type(String, String); // TODO Swtich to Builder pattern

    public: // PROPERTIES

        /// <summary>Gets the name of the current type, excluding namespace.</summary>
        DOT_AUTO_GET(TypeImpl, String, Name)

        /// <summary>Gets the fully qualified name of the type, including its namespace but not its assembly.</summary>
        DOT_AUTO_GET(TypeImpl, String, FullName)

    public: // METHODS

        Array1D<PropertyInfo> Properties; // TODO Make private

        /// <summary>Returns properties of the current type.</summary>
        virtual Array1D<PropertyInfo> GetProperties()
        {
            return Properties;
        }

        Array1D<MethodInfo> Methods; // TODO Make private

        /// <summary>Returns methods of the current type.</summary>
        virtual Array1D<MethodInfo> GetMethods()
        {
            return Methods;
        }

        /// <summary>A string representing the name of the current type.</summary>
        virtual String ToString() const { return "Type"; } // TODO - return name

    private: // CONSTRUCTORS

        /// <summary>
        /// Initializes a new instance of the Type class.
        ///
        /// This constructor is private. Use new_Type(...) function instead.
        /// </summary>
        TypeImpl(String name, String fullName)
            : Name(name)
            , FullName(fullName)
        {
        }
    };

    /// <summary>
    /// Initializes a new instance of the Type class.
    ///
    /// This constructor is private. Use new_Type(...) function instead.
    /// </summary>
    Type new_Type(String name, String fullName)
    {
        // TODO replace by type builder
        return new TypeImpl(name, fullName);
    }

    /// <summary>Returns type of class Type.</summary>
    template <class T>
    Type typeof() { return T::typeof(); }

    /// <summary>
    /// Initializes a new instance of the Type class for untyped instance of Object.
    /// </summary>
    Type ObjectImpl::GetType()
    {
        return new_Type("Object", "System.Object");
    }
}
